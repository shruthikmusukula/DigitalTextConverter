cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_COMPILER /usr/bin/g++)
project(digital-text-converter)

# This tells the compiler to not aggressively optimize and
# to include debugging information so that the debugger
# can properly read what's going on.
set(CMAKE_BUILD_TYPE Debug)

# Let's ensure -std=c++xx instead of -std=g++xx
set(CMAKE_CXX_EXTENSIONS OFF)

# Let's nicely support folders in IDE's
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Warning flags
if (MSVC)
    # warning level 3 and all warnings as errors
    add_compile_options(/W3 /WX)
else ()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wpedantic -Werror)
endif ()

# FetchContent added in CMake 3.11, downloads during the configure step
include(FetchContent)

# FetchContent_MakeAvailable was not added until CMake 3.14
if (${CMAKE_VERSION} VERSION_LESS 3.14)
    include(cmake/add_FetchContent_MakeAvailable.cmake)
endif ()

FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.x
)

# Adds Catch2 testing library
FetchContent_GetProperties(catch2)
if (NOT catch2_POPULATED)
    FetchContent_Populate(catch2)
    add_library(catch2 INTERFACE)
    target_include_directories(catch2 INTERFACE ${catch2_SOURCE_DIR}/single_include)
endif ()

get_filename_component(CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../" ABSOLUTE)
get_filename_component(APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/" ABSOLUTE)

include("${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake")

list(APPEND CORE_SOURCE_FILES src/core/image_processor.cc
        src/core/text_converter.cc)

list(APPEND APP_FILES ${CORE_SOURCE_FILES}
        src/visualizer/ocr_app.cc
        src/visualizer/sketchpad.cc
        src/visualizer/text_box_component.cc)

list(APPEND TEST_FILES tests/sketchpad_tests.cc
        tests/text_box_component_tests.cc)

# Setting OpenCV Installation
find_package(OpenCV REQUIRED)
if (OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
endif ()

# Setting Boost Installation
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_ROOT /usr/local/Cellar/boost/1.73.0)
find_package(Boost 1.73.0 COMPONENTS program_options)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif ()

add_executable(input-image apps/input_image_main.cc
        src/cli/command_line_input_parser.cc)
target_link_libraries(input-image LINK_PUBLIC ${OpenCV_LIBS} ${Boost_LIBRARIES})
target_include_directories(input-image PRIVATE include)

ci_make_app(
        APP_NAME ocr-app
        CINDER_PATH ${CINDER_PATH}
        SOURCES apps/cinder_app_main.cc ${APP_FILES}
        INCLUDES include
        LIBRARIES ${OpenCV_LIBS}
)

ci_make_app(
        APP_NAME        ocr-app-test
        CINDER_PATH     ${CINDER_PATH}
        SOURCES         tests/test_main.cc ${APP_FILES} ${TEST_FILES}
        INCLUDES        include
        LIBRARIES       catch2 ${OpenCV_LIBS}
)

if(MSVC)
    set_property(TARGET ocr-app-test APPEND_STRING PROPERTY LINK_FLAGS " /SUBSYSTEM:CONSOLE")
endif()

# Digital Text Conversion in C++ Using OpenCV & Tesseract
 * Overview 
 * Dependencies
 * Additional Info
 * Citations

## Overview 
A Cinder application that allows you to write text and convert it to standard, digital text. It also provides the user with the option to send their converted output to a file of their choice.

## Dependencies

- [g++/gcc 4.8](https://gcc.gnu.org) and above, [clang 3.4](https://clang.llvm.org) and above
- [cmake](https://cmake.org)
- [OpenCV 4.5.0](https://opencv.org/opencv-4-5-0/)
- [Tesseract 4.1.1](https://github.com/tesseract-ocr/tesseract)

### Ubuntu

```console
$ sudo apt-get install gcc cmake opencv tesseract
```
- Can be built using CLion

### MacOS

```console
$ brew install gcc cmake opencv tesseract
```
- Can be built using CLion

### Windows & Other Environments

- Check out the links above for more info on how to install dependencies for your system. You will need MSVC-2015 or higher to build this project on Windows.

### Installation
- After obtaining the necessary dependencies, clone the repository with ```git clone https://github.com/shruthikmusukula/DigitalTextConverter.git``` on your local machine.

## Code Style
This codebase was written in accordance with the Google C++ Style Guide (https://google.github.io/styleguide/cppguide.html). Code from the OpenCV and Tesseract frameworks may not adhere to these guidelines.

## Demo
Below is a full demo of the application and its major features.

### 1) Live Character Recognition
![Failed to load gif](https://i.imgur.com/kG5XxnU.gif)

### 2) Colorful User Input
![Failed to load gif](https://i.imgur.com/0fNGNAF.gif)

#### 3) Write To A File
![Failed to load gif](https://i.imgur.com/z0cRO7N.gif)

#### 4) Boost CLI Integration for Image to Text Conversion
By passing in appropriate image input paths and textfile output paths, a user can translate the text in an image of their choice to digital text.

## Additional Info
Here are some additional resources if you are looking to build upon this codebase or encounter any errors:

#### A Common Error
```console
Failed loading language 'eng'
Tesseract couldn't load any languages!
Could not initialize tesseract.
```
Please refer to [this](https://github.com/tesseract-ocr/tesseract/issues/1309) Github Issue. You need to add [this](https://github.com/tesseract-ocr/tessdata/blob/master/eng.traineddata) training data file to your tesseract installation.
On Ubuntu, download and place this file at ```/usr/share/tesseract-ocr/4.1.1/tessdata/eng.traineddata```.
On MacOS, download and place this file at ```/usr/local/Cellar/tesseract/4.1.1/tessdata/eng.traineddata```.

#### Improving the Quality of the Tesseract Engine
Excerpt from Tesseract Docs:
> Tesseract does various image processing operations internally (using the Leptonica library) before doing the actual OCR. It generally does a very good job of this, but there will inevitably be cases where it isn’t good enough, which can result in a significant reduction in accuracy.

Please look [here](https://tesseract-ocr.github.io/tessdoc/ImproveQuality.html) for additional information.

## Citations
All necessary citations are listed wherever applied in the codebase.

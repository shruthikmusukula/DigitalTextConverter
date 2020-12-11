# Final Project Proposal

### General Project Idea
For my final project, I would like to build an Optical Character Recognition (OCR)
Application. More specifically, I would like to build a Cinder application for 
converting handwritten text into a digital text format that can be displayed to the user.
The focus is to work on processing unstructured data (aka arbitrarily shaped text input).
The application should be entirely executable through Cinder (output/input 
should be displayed/received from the application window). The platform should be able to identify 
single characters, individual words, and short phrases (approximately 2-7 words in length).

The applications of a project are pretty widespread but the main inspiration behind
it is simply to build on the learning from naive-bayes and move a step beyond simple
image classification. I believe it would be a great project to dive deeper into Machine
Learning. Some background knowledge required is knowing how to work with the Tesseract OCR Library
and basic text recognition algorithms (listed below).

### Project Components
1) Cinder application for obtaining handwritten text input
2) "Frame/Image" Preprocessing
3) Text Classification
4) Text Recognition

### Timeline
**Week One**
- Days 1-3 &#8594; Research text detection algorithm
    - Some options include: Sliding Windows Technique, EAST (Efficient 
      accurate scene text detector)
- Days 4-6 &#8594; Research text recognition algorithm, Build simple Cinder input box
    - ML Algorithm using Tesseract OCR Library
- Day 7 &#8594; Begin building test dataset from the following three options:
    - SVHN dataset
    - Scene Text dataset

**Week Two**
- Days 8-9 &#8594; Begin building test dataset from the following options:
  - SVHN dataset
  - Scene Text dataset
- Days 10 - 14
    - Finish image preprocessing step

**Week Three: Thanksgiving**
- Days 15 - 18
    - Implement Text Detection Algorithm
    - Add digital text display to Cinder application
- Days 19 - 21
    - Work on Text Recognition Algorithm

**Week Four**
- Days 22 - 25
    - Work on Text Recognition Algorithm
    - Clean other major features
- Days 25 - 28
    - Testing & Project Wrap-Up
    - Maybe work on stretch goals

### Stretch Goals
- Allowing the user to select a certain output filepath to write the written text to
    - Would be great to have the output filepath user input obtained within the application
        rather than elsewhere
- Allowing for full sentence (and maybe) paragraph recognition

### Resources
- [Intro to OCR](https://nanonets.com/blog/deep-learning-ocr/)
- [ML Algorithms for HTR](https://www.mygreatlearning.com/blog/how-to-recognise-handwriting-with-machine-learning/)
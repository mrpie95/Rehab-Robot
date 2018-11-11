# Rehab-Robot
Rehab Robot Kinect is a module of a final year project at Swinburne to improve the functionality of a rehabilitation robot used to treat patients suffering from cerebral palsy. This repository will is used to store all file related to the project and currently consists of various modules

***

## Simon Says Module
This module deals with implementing the Kinect module to detect patient's movement, useful for giving feedback and improve engagement between the robot and patient. Currently, this module is to detect gesture, we are working with the Motion and Gesture class. As of now, module is an extension a Kinect SDK toolkit sample that detects skeleton.

***
## Story Telling Module
This module is used for children's entertainment. The Nao robot is used to tell 4 stories that strive to keep chlidren engadged as their visits at hospital.

## Server
The a Django web server is used as the user interface between physio and the different created modules. Using buttons on the website the server call the different modules as precompiled DLL's  
***

## Tablet Interface
The tablet interface is in the form of a website, as pure HTML and CSS. No logic is computed on the client side all logical is server side and is covered by the Django web server.

***

## Voice Recognition
The voice recognition is a partial implementation of voice recognition using the Google voice API.
***

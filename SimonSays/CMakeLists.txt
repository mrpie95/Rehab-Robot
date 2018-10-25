cmake_minimum_required(VERSION 2.8)
project(robot)

find_package(qibuild)

# Create a executable named robot
# with the source file: main.cpp

set(_src
Gesture.h
INIHandler.cpp
INIHandler.h
HandsOutFront.cpp
HandsOutFront.h
HandsOnHead.cpp
HandsOnHead.h
HandsOnHips.cpp
HandsOnHips.h
HandsOnShoulders.cpp
HandsOnShoulders.h
SquatGesture.cpp
SquatGesture.h
GestureRecEngine.cpp
GestureRecEngine.h
User.cpp
User.h
KInectStream.cpp
KInectStream.h
SimonSays.cpp
SimonSays.h
StandOnOneLeg.cpp
StandOnOneLeg.h
WaveGesture.cpp
WaveGesture.h
Window.cpp
Window.h
Robot.cpp
Robot.h
main.cpp)

qi_create_bin(robot ${_src})

qi_use_lib(robot ALCOMMON ALPROXIES)
# Add a simple test:

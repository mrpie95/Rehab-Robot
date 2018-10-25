TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
#    kinectmic.cpp \
    kinectrecord.cpp \
    timer.cpp \
    speechrecogwrapper.cpp
#    SpeechRecognitionThread.cpp

HEADERS += \
#    kinectmic.h \
    kinectrecord.h \
    timer.h \
    speechrecogwrapper.h
#    SpeechRecognitionThread.h


#unix:!macx: LIBS += -L$$PWD/../../grpc/libs/opt/ -lgrpc++

#INCLUDEPATH += $$PWD/../../grpc/include
#DEPENDPATH += $$PWD/../../grpc/include

#unix:!macx: PRE_TARGETDEPS += $$PWD/../../grpc/libs/opt/libgrpc++.a

#GOOGLEAPIS_GENS_PATH = /home/nao/Test/googleapis/gens
#GOOGLEAPIS_API_CCS = $(shell find $$GOOGLEAPIS_GENS_PATH)/google/api \
#        -name '*.pb.cc')
#GOOGLEAPIS_RPC_CCS = $(shell find $$GOOGLEAPIS_GENS_PATH)/google/rpc \
#        -name '*.pb.cc')
#GOOGLEAPIS_SPEECH_CCS = $(shell find \
#        $$GOOGLEAPIS_GENS_PATH/google/cloud/speech -name '*.pb.cc')
#GOOGLEAPIS_LONGRUNNING_CCS = $(shell find \
#        $$GOOGLEAPIS_GENS_PATH/google/longrunning -name '*.pb.cc')
#GOOGLEAPIS_CCS = $$GOOGLEAPIS_API_CCS $$GOOGLEAPIS_RPC_CCS \
#$$GOOGLEAPIS_LONGRUNNING_CCS $$GOOGLEAPIS_SPEECH_CCS


#INCLUDEPATH += $$PWD/../../Dependencies/googleapis/gens
#DEPENDPATH += $$PWD/../../Dependencies/googleapis/gens

unix:!macx: LIBS += -L$$PWD/../../Dependencies/libfreenect/build/lib/ -lfreenect -pthread

INCLUDEPATH += $$PWD/../../Dependencies/libfreenect
DEPENDPATH += $$PWD/../../Dependencies/libfreenect

unix:!macx: PRE_TARGETDEPS += $$PWD/../../Dependencies/libfreenect/build/lib/libfreenect.a

#unix:!macx: LIBS += -L/home/nao/Python-2.7.13/ -lpython2.7 -ldl -lutil

unix:!macx: LIBS += -L/usr/lib/python2.7/config-x86_64-linux-gnu -lpthread -ldl -lutil -lm -lpython2.7 -Xlinker -export-dynamic

#INCLUDEPATH += /home/nao/Python-2.7.13/Include/
#DEPENDPATH += /home/nao/Python-2.7.13/Include/

INCLUDEPATH += /usr/include/python2.7
DEPENDPATH += /usr/include/python2.7

unix:!macx: PRE_TARGETDEPS += /home/nao/Python-2.7.13/libpython2.7.a
#unix:!macx: PRE_TARGETDEPS += /home/nao/Python-2.7.13/Modules/posixmodule.o

#$PYTHONPATH = $$PWD

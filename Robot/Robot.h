#pragma once
#include <iostream>
#include <stdlib.h>
#include <future>
#include <mutex>
#include <alerror/alerror.h>
#include <alproxies/almotionproxy.h>
#include <alproxies/altexttospeechproxy.h>
#include <alproxies/alrobotpostureproxy.h>
#include <alproxies/alspeechrecognitionproxy.h>
#include <alproxies/almemoryproxy.h>
#include <alproxies/albehaviormanagerproxy.h>
class Robot
{
private:
	AL::ALMotionProxy motionProxy;;
	AL::ALTextToSpeechProxy speakProxy;
	AL::ALRobotPostureProxy postureProxy;
	AL::ALSpeechRecognitionProxy speechRecProxy;
	AL::ALMemoryProxy memoryProxy;
	AL::ALBehaviorManagerProxy behaviorProxy;

	std::mutex speech_mtx;
	std::mutex move_mtx;


public:
	Robot(const char*);
	Robot(const Robot&);
	~Robot();

	//delay_millseconds, move function, audio functions, const char* for speak function
	//negative delay flips functions delay around
	//void async_speak_move_call(int, void (Robot::*)(), void (Robot::*)(const char*), const char*);
	void say(const char* text);
	void shutDown();
	void wakeup();
	void stand();
	void handsOutFront();
	void handsOnHead();
	void handsOnHips();
	void handsOnShoulders();
	void squat();
	void waveLeftHand();
	void waveRightHand();
	void standOnOneLeg();
	void dance();
	

};


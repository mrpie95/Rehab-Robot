#pragma once
#include <iostream>
#include <stdlib.h>
#include <future>
#include <mutex>
#include <alerror/alerror.h>
#include <alproxies/almotionproxy.h>
#include <alproxies/altexttospeechproxy.h>
#include <alproxies/alrobotpostureproxy.h>

class Robot
{
private:
	AL::ALMotionProxy motionProxy;;
	AL::ALTextToSpeechProxy speakProxy;
	AL::ALRobotPostureProxy postureProxy;

	std::mutex speech_mtx;
	std::mutex move_mtx;

	std::future<void> moveThread;
	std::future<void> speakThread;

	Robot(const Robot&);
public:
	Robot(const char*);
	
	~Robot();

	void say(const char* text);
	void shutDown();
	void wakeup();
	void stand();
	void handsOutFront();
};


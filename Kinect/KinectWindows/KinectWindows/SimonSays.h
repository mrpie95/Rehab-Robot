#pragma once
#include "Window.h"
#include <iostream>
#include <OpenNI.h>
#include "KInectStream.h"
#include "HandsOnHead.h"
#include "HandsOnHips.h"
#include "HandsOnShoulders.h"
#include <vector>
#include <ctime>
#include <string>
#include <chrono>
#include "User.h"
#include "Robot.h"
#define log(x) std::cout << x << std::endl;

#define SIMON_NOT_SAY_CHANCE 0.2f

class SimonSays
{
private:
	KinectStream* kinectStream;
	User user;

	int getRandomNumber(int max);
	bool roll();

	Gesture* gestureSelected;
	Robot nao;
public:
	SimonSays();
	SimonSays(const char*);
	~SimonSays();

	void init();
	void run();
};


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

#define log(x) std::cout << x << std::endl;

#define SIMON_NOT_SAY_CHANCE 0.2f

class SimonSays
{
private:
	Window skeletonWindow;
	Window camera;

	KinectStream* kinectStream;
	openni::Device kinect;
	openni::VideoStream depth, color;
	nite::UserTracker tracker;
	nite::Skeleton* skeleton;

	std::vector<GestureInterface*> gestures;

	int getRandomNumber();

public:
	SimonSays();
	~SimonSays();

	void init();
	void run();
};


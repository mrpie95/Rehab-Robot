#pragma once
#include "gestureInterface.h"
#include <chrono>

#define CONSECTIVE_SEGMENTS_NEEDED 4
#define TIME_TO_COMPLETE_WAVE 5.0f
enum Hand
{
	leftHand,
	rightHand
};
class WaveGesture :public GestureInterface
{
private:
	
	std::chrono::high_resolution_clock::time_point start;
	std::chrono::duration<double> elapsed;

	bool lastLeftSegmentCorrect;
	bool lastRightSegmentCorrect;
	int correctSegmentCount;

	Hand hand;

	//right hand wave
	bool RightHandRightOfElbow();
	bool RightHandLeftOfElbow();

	//left hand wave
	bool LeftHandRightOfElbow();
	bool LeftHandLeftOfElbow();
public:
	WaveGesture(Hand hand);
	~WaveGesture();


	bool checkForGesture();
};


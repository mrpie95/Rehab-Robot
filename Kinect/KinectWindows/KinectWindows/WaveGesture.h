#pragma once
#include "Gesture.h"
#include <chrono>

enum Hand
{
	leftHand,
	rightHand
};
class WaveGesture :public Gesture
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
	bool checkForDoingGesture() override;
	std::string print() override;
};


#include "WaveGesture.h"
#include "INIHandler.h"

WaveGesture::WaveGesture(Hand hand): Gesture("Wave"), hand(hand)
{
	if (hand == Hand::leftHand)
		name = "Wave left hand";
	else
		name = "Wave right hand";

	lastLeftSegmentCorrect = false;
	lastRightSegmentCorrect = false;
	correctSegmentCount = 0;
}


WaveGesture::~WaveGesture()
{
}


bool WaveGesture::RightHandRightOfElbow()
{
	//hand above elobw
	if (this->getRightHandPos().y > this->getRightElbowPos().y)
	{
		//Hand right of elblow
		if (this->getRightHandPos().x > this->getRightElbowPos().x)
		{
			return true;
		}
	}
	return false;
}

bool WaveGesture::RightHandLeftOfElbow()
{
	//hand above elbow
	if (this->getRightHandPos().y > this->getRightElbowPos().y)
	{
		//hand left of elbow
		if (this->getRightHandPos().x < this->getRightElbowPos().x)
		{
			return true;
		}
	}
	return false;
}

bool WaveGesture::LeftHandRightOfElbow()
{
	//hand above elobw
	if (this->getLeftHandPos().y > this->getLeftElbowPos().y)
	{
		//Hand right of elblow
		if (this->getLeftHandPos().x < this->getLeftElbowPos().x)
		{
			return true;
		}
	}
	return false;
}

bool WaveGesture::LeftHandLeftOfElbow()
{
	//hand above elbow
	if (this->getLeftHandPos().y > this->getLeftElbowPos().y)
	{
		//hand left of elbow
		if (this->getLeftHandPos().x > this->getLeftElbowPos().x)
		{
			return true;
		}
	}
	return false;

}

bool WaveGesture::checkForGesture()
{
	bool left = false;
	bool right = false;
	float timeToCompleteWaves = INIHandler::getInstance().getValue<float>("fTimeToCompleteWave");
	int numberOfConsectiveChecks = INIHandler::getInstance().getValue<int>("iNumberOfConsectiveLeftRightChecksForWave");
	if (hand == Hand::rightHand)
	{
		left = this->RightHandLeftOfElbow();
		right = this->RightHandRightOfElbow();
	}
	else if (hand == Hand::leftHand)
	{
		left = this->LeftHandLeftOfElbow();
		right = this->LeftHandRightOfElbow();
	}

	if ((left || right) && correctSegmentCount == 0)
	{
		//start clock
		start = std::chrono::high_resolution_clock::now();

		if (left)
			lastLeftSegmentCorrect = true;
		else if (right)
			lastRightSegmentCorrect = true;
		correctSegmentCount = 1;
		return false;
	}

	elapsed = std::chrono::high_resolution_clock::now() - start;
	if (lastLeftSegmentCorrect)
	{
		if (right)
		{
			lastRightSegmentCorrect = true;
			lastLeftSegmentCorrect = false;
			correctSegmentCount++;
		}
	}

	if (lastRightSegmentCorrect)
	{
		if (left)
		{
			lastLeftSegmentCorrect = true;
			lastRightSegmentCorrect = false;
			correctSegmentCount++;
		}
	}

	if (correctSegmentCount == numberOfConsectiveChecks)
	{
		lastLeftSegmentCorrect = false;
		lastRightSegmentCorrect = false;
		correctSegmentCount = 0;
		return true;
	}

	//reset if it cant find gesture in time
	if (elapsed.count() > timeToCompleteWaves)
	{
		correctSegmentCount = 0;
		lastLeftSegmentCorrect = false;
		lastRightSegmentCorrect = false;
	}
	
	return false;

}

bool WaveGesture::checkForDoingGesture() 
{
	return correctSegmentCount > 0;
}

std::string WaveGesture::print()
{
	int numberOfConsectiveChecks = INIHandler::getInstance().getValue<int>("iNumberOfConsectiveLeftRightChecksForWave");
	return std::string(std::to_string(correctSegmentCount) + "/" + std::to_string(numberOfConsectiveChecks) + " Correct Segments");
}

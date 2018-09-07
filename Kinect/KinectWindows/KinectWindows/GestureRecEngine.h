#pragma once
#include <vector>
#include "gestureInterface.h"

class GestureRecEngine
{
private:
	std::vector<GestureInterface*> gestures;
public:
	GestureRecEngine();
	~GestureRecEngine();

	//Adds a gesture to the engine
	void addGesture(GestureInterface*);

	//Loops through all gestures that have been added and checks for the condition checkForGesture has been meet 
	GestureInterface* checkForGesture(nite::Skeleton);
	//loops through all gestures thats beeen added and checks for the condition checkForDoingGesture has been met and returns all the gestures return true
	std::vector<GestureInterface*> checkForDoingGestures(nite::Skeleton);
};


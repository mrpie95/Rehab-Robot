#pragma once
#include <vector>
#include "Gesture.h"

class GestureRecEngine
{
private:
	std::vector<Gesture*> gestures;
public:
	GestureRecEngine();
	~GestureRecEngine();

	//Adds a gesture to the engine
	void addGesture(Gesture*);

	//Loops through all gestures that have been added and checks for the condition checkForGesture has been meet 
	Gesture* checkForGesture(nite::Skeleton);
	//loops through all gestures thats beeen added and checks for the condition checkForDoingGesture has been met and returns all the gestures return true
	std::vector<Gesture*> checkForDoingGestures(nite::Skeleton);

	std::vector<Gesture*> getGestures() { return gestures; }
};


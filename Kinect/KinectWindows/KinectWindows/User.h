#pragma once
#include <NiTE.h>
#include "Gesture.h"
#include "GestureRecEngine.h"
#include <string>

class User
{
private:
	nite::Skeleton skeleton;
	GestureRecEngine gestureChecker;

	//given in mm
	int height;
	int distanceFromKinect;
	
	Gesture* lastGesture;
	std::vector<Gesture*> activeGestures;
	
public:
	User();
	~User();

	//Updates the user varibles per loop and checks for gestures.
	void initGestureChecker();

	void update(nite::Skeleton);
	std::string print();

	Gesture* getLastGesture() { return lastGesture; }
	std::vector<Gesture*> getGestures() { return gestureChecker.getGestures(); }

protected:
	float euclidDistance3D(nite::Point3f a, nite::Point3f b);
	//x,y
	float euclidDistance2D(nite::Point3f a, nite::Point3f b);
		

	// TODO: catch exceptions, what happens if there is no skelton or it cant find joint
	//head
	nite::Point3f getHeadPos();

	//neck
	nite::Point3f getNeckPos();

	//torso
	nite::Point3f getTorsoPos();

	//shoulder
	nite::Point3f getLeftShoulderPos();
	nite::Point3f getRightShoulderPos();

	//elbow
	nite::Point3f getLeftElbowPos();
	nite::Point3f getRightElbowPos();

	//Hands
	nite::Point3f getLeftHandPos();
	nite::Point3f getRightHandPos();

	//hip
	nite::Point3f getLeftHipPos();
	nite::Point3f getRightHipPos();

	//knee
	nite::Point3f getLeftKneePos();
	nite::Point3f getRightKneePos();

	//feet
	nite::Point3f getLeftFootPos();
	nite::Point3f getRightFootPos();
};


#include "User.h"
#include <math.h>
#include "HandsOnhead.h"
#include "HandsOnHips.h"
#include "HandsOnShoulders.h"
#include "WaveGesture.h"
#include "StandOnOneLeg.h"
#include "HandsOutFront.h"
#include "SquatGesture.h"


User::User(): lastGesture(nullptr)
{
}


User::~User()
{
}


void User::initGestureChecker()
{
	gestureChecker.addGesture(new HandsOnHead());
	gestureChecker.addGesture(new HandsOnHips());
	gestureChecker.addGesture(new HandsOnShoulders());
	gestureChecker.addGesture(new WaveGesture(Hand::rightHand));
	gestureChecker.addGesture(new WaveGesture(Hand::leftHand));
	gestureChecker.addGesture(new StandOnOneLeg());
	gestureChecker.addGesture(new SquatGesture());
	gestureChecker.addGesture(new HandsOutFront());
}



void User::update(nite::Skeleton skeleton)
{
	this->skeleton = skeleton;

	height = euclidDistance3D(this->getHeadPos(), this->getLeftShoulderPos())
		+ euclidDistance3D(this->getLeftShoulderPos(), this->getLeftHipPos()) + euclidDistance3D(this->getLeftHipPos(), this->getLeftKneePos())
		+ euclidDistance3D(this->getLeftKneePos(), this->getLeftFootPos());

	distanceFromKinect = this->getTorsoPos().z;

	Gesture* temp = gestureChecker.checkForGesture(skeleton);
	activeGestures = gestureChecker.checkForDoingGestures(skeleton);

	if (temp)
		lastGesture = temp;
}

std::string User::print()
{
	std::string temp("Last Gesture: ");
	if (lastGesture)
		temp.append(lastGesture->getName());
	temp.append("\n");
	temp.append("User Height: " + std::to_string(height / 1000.0f) + "m\n");
	temp.append("Distance From Kinect: " + std::to_string(distanceFromKinect/1000.0f) + "m\n");
	for (auto g: activeGestures)
	{
		temp.append(g->getName() + std::string(" ") +g->print() + "\n");
	}


	return temp;
}

//todo:: move this to another class
float User::euclidDistance3D(nite::Point3f a, nite::Point3f b) { return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2)); }
//x,y
float User::euclidDistance2D(nite::Point3f a, nite::Point3f b) { return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)); }


//head
nite::Point3f User::getHeadPos() { return skeleton.getJoint(nite::JOINT_HEAD).getPosition(); }
			 
//neck		  
nite::Point3f User::getNeckPos() { return skeleton.getJoint(nite::JOINT_NECK).getPosition(); }
			  
//torso		  
nite::Point3f User::getTorsoPos() { return skeleton.getJoint(nite::JOINT_TORSO).getPosition(); }
			  
//shoulder	  
nite::Point3f User::getLeftShoulderPos() { return skeleton.getJoint(nite::JOINT_LEFT_SHOULDER).getPosition(); }
nite::Point3f User::getRightShoulderPos() { return skeleton.getJoint(nite::JOINT_RIGHT_SHOULDER).getPosition(); }
			  
//elbow		  
nite::Point3f User::getLeftElbowPos() { return skeleton.getJoint(nite::JOINT_LEFT_ELBOW).getPosition(); }
nite::Point3f User::getRightElbowPos() { return skeleton.getJoint(nite::JOINT_RIGHT_ELBOW).getPosition(); }
			  
//Hands		  
nite::Point3f User::getLeftHandPos() { return skeleton.getJoint(nite::JOINT_LEFT_HAND).getPosition(); }
nite::Point3f User::getRightHandPos() { return skeleton.getJoint(nite::JOINT_RIGHT_HAND).getPosition(); }
			
//hip		  
nite::Point3f User::getLeftHipPos() { return skeleton.getJoint(nite::JOINT_LEFT_HIP).getPosition(); }
nite::Point3f User::getRightHipPos() { return skeleton.getJoint(nite::JOINT_RIGHT_HIP).getPosition(); }
			  
//knee		  
nite::Point3f User::getLeftKneePos() { return skeleton.getJoint(nite::JOINT_LEFT_KNEE).getPosition(); }
nite::Point3f User::getRightKneePos() { return skeleton.getJoint(nite::JOINT_RIGHT_KNEE).getPosition(); }
			  
//feet		  
nite::Point3f User::getLeftFootPos() { return skeleton.getJoint(nite::JOINT_LEFT_FOOT).getPosition(); }
nite::Point3f User::getRightFootPos() { return skeleton.getJoint(nite::JOINT_RIGHT_FOOT).getPosition(); }
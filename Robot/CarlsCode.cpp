/*
 * Copyright (c) 2012-2018 SoftBank Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.al
 */
#include <iostream>
#include <alerror/alerror.h>
#include <alproxies/almotionproxy.h>
#include <alproxies/altexttospeechproxy.h>
#include <thread>
#include <SDL2/SDL.h>
#include <OpenNI.h>
#include "Linux-x86/OniPlatformLinux-x86.h"
#include <FTGL/ftgl.h>
#include <FTGL/FTPoint.h>
#include <Include/NiTE.h>
#include <GL/glew.h>


int handsOnHead(AL::ALMotionProxy motion)
{
	AL::ALValue jointName = AL::ALValue::array("LElbowYaw", "RElbowYaw","LElbowRoll", "RElbowRoll", "LShoulderRoll","LShoulderPitch", "RShoulderRoll","RShoulderPitch", "LWristYaw","RWristYaw");
    /** Target stiffness. */
    AL::ALValue stiffness = 1.0f;
    /** Time (in seconds) to reach the target. */
    AL::ALValue time = 1.0f;
    /** Call the stiffness interpolation method. */
    motion.stiffnessInterpolation(jointName, stiffness, time);
    /** Hands on head */
    /** Set the target angle list, in radians. */
    AL::ALValue targetAngles;
    targetAngles.arraySetSize(10);
    //
    targetAngles[0] = AL::ALValue::array(0.0f,0.3f,0.0f); //left elbowyaw
    targetAngles[1] = AL::ALValue::array(0.0f,-0.3f,0.0f); // right elbow yaw
    targetAngles[2] = AL::ALValue::array(0.0f,-1.2f,0.0f); //left elbow roll
    targetAngles[3] = AL::ALValue::array(0.0f,1.2f,0.0f); // right elbow roll
    targetAngles[4] = AL::ALValue::array(0.0f,-1.0f,0.0f); // left shoulder roll
    targetAngles[5] = AL::ALValue::array(0.0f,-1.7f,1.5f); // left sholder pitch
    targetAngles[6] = AL::ALValue::array(0.0f,1.0f,0.0f); // right shoulder roll
    targetAngles[7] = AL::ALValue::array(0.0f,-1.7f,1.5f); // right shoulder pitch
    targetAngles[8] = AL::ALValue::array(0.0f,-1.5f,-0.7f); // Left wrist yaw
    targetAngles[9] = AL::ALValue::array(0.0f,1.5f,0.7f); // Right wrist yaw

    /** Set the corresponding time lists, in seconds. */
    AL::ALValue targetTimes;
    targetTimes.arraySetSize(10);
    targetTimes[0] = AL::ALValue::array(1.0f,3.0f,4.0f);
    targetTimes[1] = AL::ALValue::array(1.0f,3.0f,4.0f);
    targetTimes[2] = AL::ALValue::array(1.0f,3.0f,4.0f);
    targetTimes[3] = AL::ALValue::array(1.0f,3.0f,4.0f);
    targetTimes[4] = AL::ALValue::array(1.0f,3.0f,4.0f);
    targetTimes[5] = AL::ALValue::array(1.0f,3.0f,6.0f);
    targetTimes[6] = AL::ALValue::array(1.0f,3.0f,4.0f);
    targetTimes[7] = AL::ALValue::array(1.0f,3.0f,6.0f);
    targetTimes[8] = AL::ALValue::array(1.0f,3.0f,4.0f);
    targetTimes[9] = AL::ALValue::array(1.0f,3.0f,4.0f);
    /** Specify that the desired angles are absolute. */
    bool isAbsolute = true;

    /** Call the angle interpolation method. The joint will reach the
    * desired angles at the desired times.
    */
    motion.angleInterpolation(jointName, targetAngles, targetTimes, isAbsolute);

	return 0;
}

int handsInFront(AL::ALMotionProxy motion)
{
	AL::ALValue jointName = AL::ALValue::array("LElbowYaw", "RElbowYaw","LElbowRoll", "RElbowRoll", "LShoulderRoll","LShoulderPitch", "RShoulderRoll","RShoulderPitch", "LWristYaw","RWristYaw");
    /** Target stiffness. */
    AL::ALValue stiffness = 1.0f;
    /** Time (in seconds) to reach the target. */
    AL::ALValue time = 1.0f;
    /** Call the stiffness interpolation method. */
    motion.stiffnessInterpolation(jointName, stiffness, time);
    /** Hands on head */
    /** Set the target angle list, in radians. */
    AL::ALValue targetAngles;
    targetAngles.arraySetSize(10);
    targetAngles[0] = AL::ALValue::array(0.0f,0.0f); //left elbowyaw
    targetAngles[1] = AL::ALValue::array(0.0f,0.0f); // right elbow yaw
    targetAngles[2] = AL::ALValue::array(0.0f,0.0f); //left elbow roll
    targetAngles[3] = AL::ALValue::array(0.0f,0.0f); // right elbow roll
    targetAngles[4] = AL::ALValue::array(0.0f,0.0f); // left shoulder roll
    targetAngles[5] = AL::ALValue::array(0.0f,1.5f); // left sholder pitch
    targetAngles[6] = AL::ALValue::array(0.0f,0.0f); // right shoulder roll
    targetAngles[7] = AL::ALValue::array(0.0f,1.5f); // right shoulder pitch
    targetAngles[8] = AL::ALValue::array(0.0f,0.0f); // Left wrist yaw
    targetAngles[9] = AL::ALValue::array(0.0f,0.0f); // Right wrist yaw

    /** Set the corresponding time lists, in seconds. */
    AL::ALValue targetTimes;
    targetTimes.arraySetSize(10);
    targetTimes[0] = AL::ALValue::array(3.0f,6.0f);
    targetTimes[1] = AL::ALValue::array(3.0f,6.0f);
    targetTimes[2] = AL::ALValue::array(3.0f,6.0f);
    targetTimes[3] = AL::ALValue::array(3.0f,6.0f);
    targetTimes[4] = AL::ALValue::array(3.0f,6.0f);
    targetTimes[5] = AL::ALValue::array(3.0f,6.0f);
    targetTimes[6] = AL::ALValue::array(3.0f,6.0f);
    targetTimes[7] = AL::ALValue::array(3.0f,6.0f);
    targetTimes[8] = AL::ALValue::array(3.0f,6.0f);
    targetTimes[9] = AL::ALValue::array(3.0f,6.0f);
    /** Specify that the desired angles are absolute. */
    bool isAbsolute = true;

    /** Call the angle interpolation method. The joint will reach the
    * desired angles at the desired times.
    */
    motion.angleInterpolation(jointName, targetAngles, targetTimes, isAbsolute);

	return 0;
}

int handsOnHips(AL::ALMotionProxy motion)
{
	AL::ALValue jointName = AL::ALValue::array("LElbowYaw", "RElbowYaw","LElbowRoll", "RElbowRoll", "LShoulderRoll","LShoulderPitch", "RShoulderRoll","RShoulderPitch", "LWristYaw","RWristYaw");
    /** Target stiffness. */
    AL::ALValue stiffness = 1.0f;
    /** Time (in seconds) to reach the target. */
    AL::ALValue time = 1.0f;
    /** Call the stiffness interpolation method. */
    motion.stiffnessInterpolation(jointName, stiffness, time);
	/*Hands on hips*/
    AL::ALValue targetAngles;
    targetAngles.arraySetSize(10);
    targetAngles[0] = AL::ALValue::array(0.0f,0.3f,0.0f); //left elbowyaw
    targetAngles[1] = AL::ALValue::array(0.0f,-0.3f,0.0f); // right elbow yaw
    targetAngles[2] = AL::ALValue::array(0.0f,-1.3f,0.0f); //left elbow roll
    targetAngles[3] = AL::ALValue::array(0.0f,1.3f,0.0f); // right elbow roll
    targetAngles[4] = AL::ALValue::array(0.0f,0.95f,0.0f); // left shoulder roll
    targetAngles[5] = AL::ALValue::array(0.0f,1.3f,1.5f); // left sholder pitch
    targetAngles[6] = AL::ALValue::array(0.0f,-0.95f,0.0f); // right shoulder roll
    targetAngles[7] = AL::ALValue::array(0.0f,1.3f,1.5f); // right shoulder pitch
    targetAngles[8] = AL::ALValue::array(0.0f,-1.5f,0.0f); // Left wrist yaw
    targetAngles[9] = AL::ALValue::array(0.0f,1.5f,0.0f); // Right wrist yaw

    /** Set the corresponding time lists, in seconds. */
    AL::ALValue targetTimes;
    targetTimes.arraySetSize(10);
    targetTimes[0] = AL::ALValue::array(1.0f,4.0f,6.0f);
    targetTimes[1] = AL::ALValue::array(1.0f,4.0f,6.0f);
    targetTimes[2] = AL::ALValue::array(1.0f,4.0f,6.0f);
    targetTimes[3] = AL::ALValue::array(1.0f,4.0f,6.0f);
    targetTimes[4] = AL::ALValue::array(1.0f,4.0f,6.0f);
    targetTimes[5] = AL::ALValue::array(1.0f,4.0f,6.0f);
    targetTimes[6] = AL::ALValue::array(1.0f,4.0f,6.0f);
    targetTimes[7] = AL::ALValue::array(1.0f,4.0f,6.0f);
    targetTimes[8] = AL::ALValue::array(1.0f,4.0f,6.0f);
    targetTimes[9] = AL::ALValue::array(1.0f,4.0f,6.0f);
    /** Specify that the desired angles are absolute. */
    bool isAbsolute = true;

    /** Call the angle interpolation method. The joint will reach the
    * desired angles at the desired times.
    */
    motion.angleInterpolation(jointName, targetAngles, targetTimes, isAbsolute);
	return 0;
}

int handsOnShoulders(AL::ALMotionProxy motion)
{
	AL::ALValue jointName = AL::ALValue::array("LElbowYaw", "RElbowYaw","LElbowRoll", "RElbowRoll", "LShoulderRoll","LShoulderPitch", "RShoulderRoll","RShoulderPitch", "LWristYaw","RWristYaw");
    /** Target stiffness. */
    AL::ALValue stiffness = 1.0f;
    /** Time (in seconds) to reach the target. */
    AL::ALValue time = 1.0f;
    /** Call the stiffness interpolation method. */
    motion.stiffnessInterpolation(jointName, stiffness, time);
    /** Hands on head */
    /** Set the target angle list, in radians. */
    AL::ALValue targetAngles;
    targetAngles.arraySetSize(10);
    targetAngles[0] = AL::ALValue::array(0.0f,0.0f,0.0f); //left elbow yaw
    targetAngles[1] = AL::ALValue::array(0.0f,0.0f,0.0f); // right elbow yaw
    targetAngles[2] = AL::ALValue::array(0.0f,-2.0f,0.0f); //left elbow roll
    targetAngles[3] = AL::ALValue::array(0.0f,2.0f,0.0f); // right elbow roll
    targetAngles[4] = AL::ALValue::array(0.0f,0.2f,0.0f); // left shoulder roll
    targetAngles[5] = AL::ALValue::array(0.0f,0.0f,1.5f); // left sholder pitch
    targetAngles[6] = AL::ALValue::array(0.0f,-0.2f,0.0f); // right shoulder roll
    targetAngles[7] = AL::ALValue::array(0.0f,0.0f,1.5f); // right shoulder pitch
    targetAngles[8] = AL::ALValue::array(0.0f,0.5f,0.0f); // Left wrist yaw
    targetAngles[9] = AL::ALValue::array(0.0f,0.5f,0.0f); // Right wrist yaw

    /** Set the corresponding time lists, in seconds. */
    AL::ALValue targetTimes;
    targetTimes.arraySetSize(10);
    targetTimes[0] = AL::ALValue::array(2.5f,6.0f,9.0f);
    targetTimes[1] = AL::ALValue::array(2.5f,6.0f,9.0f);
    targetTimes[2] = AL::ALValue::array(2.5f,6.0f,9.0f);
    targetTimes[3] = AL::ALValue::array(2.5f,6.0f,9.0f);
    targetTimes[4] = AL::ALValue::array(2.5f,6.0f,9.0f);
    targetTimes[5] = AL::ALValue::array(2.5f,6.0f,9.0f);
    targetTimes[6] = AL::ALValue::array(2.5f,6.0f,9.0f);
    targetTimes[7] = AL::ALValue::array(2.5f,6.0f,9.0f);
    targetTimes[8] = AL::ALValue::array(2.5f,6.0f,9.0f);
    targetTimes[9] = AL::ALValue::array(2.5f,6.0f,9.0f);
    /** Specify that the desired angles are absolute. */
    bool isAbsolute = true;

    /** Call the angle interpolation method. The joint will reach the
    * desired angles at the desired times.
    */
    motion.angleInterpolation(jointName, targetAngles, targetTimes, isAbsolute);

	return 0;
}

int squat(AL::ALMotionProxy motion)
{
	AL::ALValue jointName = AL::ALValue::array("RHipPitch", "LHipPitch","RKneePitch", "LKneePitch","LAnklePitch","LAnkleRoll","RAnklePitch","RAnkleRoll","LShoulderPitch","RShoulderPitch");
    /** Target stiffness. */
    AL::ALValue stiffness = 1.0f;
    /** Time (in seconds) to reach the target. */
    AL::ALValue time = 1.0f;
    /** Call the stiffness interpolation method. */
    motion.stiffnessInterpolation(jointName, stiffness, time);
    /** Squat */
    /** Set the target angle list, in radians. */
    AL::ALValue targetAngles;
    targetAngles.arraySetSize(10);
    targetAngles[0] = AL::ALValue::array(0.0f,-1.0f,0.0f); //Right Hip Pitch
    targetAngles[1] = AL::ALValue::array(0.0f,-1.0f,0.0f); //Left Hip Pitch
    targetAngles[2] = AL::ALValue::array(0.0f,1.5f,0.0f);  //Right Knee Pitch
    targetAngles[3] = AL::ALValue::array(0.0f,1.5f,0.0f);  //Left Knee Pitch
    targetAngles[4] = AL::ALValue::array(0.0f,-0.5f,0.0f); //Left Ankle Pitch
    targetAngles[5] = AL::ALValue::array(0.0f,0.0f,0.0f);  //Left Ankle Roll
    targetAngles[6] = AL::ALValue::array(0.0f,-0.5f,0.0f); //Right Ankle Pitch
    targetAngles[7] = AL::ALValue::array(0.0f,0.0f,0.0f); //Right Ankle Roll
 	targetAngles[8] = AL::ALValue::array(0.0f,0.0f,1.5f);    //Left Shoulder Pitch
 	targetAngles[9] = AL::ALValue::array(0.0f,0.0f,1.5f);    //Right Shoulder Pitch




    /** Set the corresponding time lists, in seconds. */
    AL::ALValue targetTimes;
    targetTimes.arraySetSize(10);
    targetTimes[0] = AL::ALValue::array(2.0f,5.0f,8.0f);
    targetTimes[1] = AL::ALValue::array(2.0f,5.0f,8.0f);
    targetTimes[2] = AL::ALValue::array(2.0f,5.0f,8.0f);
    targetTimes[3] = AL::ALValue::array(2.0f,5.0f,8.0f);
    targetTimes[4] = AL::ALValue::array(2.0f,5.0f,8.0f);
    targetTimes[5] = AL::ALValue::array(2.0f,5.0f,8.0f);
    targetTimes[6] = AL::ALValue::array(2.0f,5.0f,8.0f);
    targetTimes[7] = AL::ALValue::array(2.0f,5.0f,8.0f);
    targetTimes[8] = AL::ALValue::array(2.0f,5.0f,8.0f);
    targetTimes[9] = AL::ALValue::array(2.0f,5.0f,8.0f);

    /** Specify that the desired angles are absolute. */
    bool isAbsolute = true;

    /** Call the angle interpolation method. The joint will reach the
    * desired angles at the desired times.
    */
    motion.angleInterpolation(jointName, targetAngles, targetTimes, isAbsolute);

	return 0;
}

int leftWave(AL::ALMotionProxy motion)
{
	AL::ALValue jointName = AL::ALValue::array("LElbowYaw","LElbowRoll", "LWristYaw", "LShoulderRoll","LShoulderPitch");
    /** Target stiffness. */
    AL::ALValue stiffness = 1.0f;
    /** Time (in seconds) to reach the target. */
    AL::ALValue time = 1.0f;
    /** Call the stiffness interpolation method. */
    motion.stiffnessInterpolation(jointName, stiffness, time);
    /** Squat */
    /** Set the target angle list, in radians. */
    AL::ALValue targetAngles;
    targetAngles.arraySetSize(5);
    targetAngles[0] = AL::ALValue::array(-6.0f,-1.0f, -6.0f, 0.0f); //Left Elbow Yaw
    targetAngles[1] = AL::ALValue::array(-3.0f,-3.0f, -3.0f,0.0f);  //Left Elbow Roll
    targetAngles[2] = AL::ALValue::array(1.0f,1.0f,1.0f,0.0f); 		//Left Wrist Yaw
    targetAngles[3] = AL::ALValue::array(0.0f,0.0f,0.0f,0.0f);      //Left Shoulder Roll
    targetAngles[4] = AL::ALValue::array(0.0f,0.0f,0.0f,1.5f);      //Left Shoulder Pitch



    /** Set the corresponding time lists, in seconds. */
    AL::ALValue targetTimes;
    targetTimes.arraySetSize(6);
    targetTimes[0] = AL::ALValue::array(3.0f,4.0f,5.0f,6.0f);
    targetTimes[1] = AL::ALValue::array(3.0f,4.0f,5.0f,6.0f);
    targetTimes[2] = AL::ALValue::array(3.0f,4.0f,5.0f,6.0f);
    targetTimes[3] = AL::ALValue::array(3.0f,4.0f,5.0f,6.0f);
    targetTimes[4] = AL::ALValue::array(3.0f,4.0f,5.0f,6.0f);
    /** Specify that the desired angles are absolute. */
    bool isAbsolute = true;

    /** Call the angle interpolation method. The joint will reach the
    * desired angles at the desired times.
    */
    motion.angleInterpolation(jointName, targetAngles, targetTimes, isAbsolute);

	return 0;
}

int rightWave(AL::ALMotionProxy motion)
{
	AL::ALValue jointName = AL::ALValue::array("RElbowYaw","RElbowRoll", "RWristYaw", "RShoulderRoll","RShoulderPitch");
    /** Target stiffness. */
    AL::ALValue stiffness = 1.0f;
    /** Time (in seconds) to reach the target. */
    AL::ALValue time = 1.0f;
    /** Call the stiffness interpolation method. */
    motion.stiffnessInterpolation(jointName, stiffness, time);
    /** Squat */
    /** Set the target angle list, in radians. */
    AL::ALValue targetAngles;
    targetAngles.arraySetSize(5);
    targetAngles[0] = AL::ALValue::array(6.0f,1.0f, 6.0f,0.0f);   //Right Elbow Yaw
    targetAngles[1] = AL::ALValue::array(3.0f,3.0f, 3.0f,0.0f);   //Right Elbow Yaw
    targetAngles[2] = AL::ALValue::array(-1.0f,-1.0f,-1.0f,0.0f); //Right Wrist Yaw
    targetAngles[3] = AL::ALValue::array(0.0f,0.0f,0.0f,0.0f);    //Right Shoulder Roll
    targetAngles[4] = AL::ALValue::array(0.0f,0.0f,0.0f,1.5f);    //Right Shoulder Pitch


    /** Set the corresponding time lists, in seconds. */
    AL::ALValue targetTimes;
    targetTimes.arraySetSize(5);
    targetTimes[0] = AL::ALValue::array(3.0f,4.0f,5.0f,6.0f);
    targetTimes[1] = AL::ALValue::array(3.0f,4.0f,5.0f,6.0f);
    targetTimes[2] = AL::ALValue::array(3.0f,4.0f,5.0f,6.0f);
    targetTimes[3] = AL::ALValue::array(3.0f,4.0f,5.0f,6.0f);
    targetTimes[4] = AL::ALValue::array(3.0f,4.0f,5.0f,6.0f);

    /** Specify that the desired angles are absolute. */
    bool isAbsolute = true;

    /** Call the angle interpolation method. The joint will reach the
    * desired angles at the desired times.
    */
    motion.angleInterpolation(jointName, targetAngles, targetTimes, isAbsolute);

	return 0;
}

int raiseOneLeg(AL::ALMotionProxy motion)
{
	AL::ALValue jointName = AL::ALValue::array("RHipPitch","RKneePitch", "LAnklePitch","LAnkleRoll", "RAnklePitch","RAnkleRoll","LHipPitch","LHipRoll","LKneePitch");
    /** Target stiffness. */
    AL::ALValue stiffness = 1.0f;
    /** Time (in seconds) to reach the target. */
    AL::ALValue time = 1.0f;
    /** Call the stiffness interpolation method. */
    motion.stiffnessInterpolation(jointName, stiffness, time);
    /** Squat */
    /** Set the target angle list, in radians. */
    AL::ALValue targetAngles;
    targetAngles.arraySetSize(9);
    targetAngles[0] = AL::ALValue::array(0.0f,-1.0f,0.0f); //Right Hip Pitch
    targetAngles[1] = AL::ALValue::array(0.0f,1.0f,0.0f); // Right Knee Pitch
    targetAngles[2] = AL::ALValue::array(0.0f,0.0f,0.0f); // Left Ankle Pitch
    targetAngles[3] = AL::ALValue::array(0.0f,0.2f,0.0f); // Left Ankle Roll
	targetAngles[4] = AL::ALValue::array(0.0f,0.0f,0.0f); // Right Ankle Pitch
    targetAngles[5] = AL::ALValue::array(0.0f,0.0f,0.0f); // Right Ankle Roll
    targetAngles[6] = AL::ALValue::array(0.0f,0.0f,0.0f); // Left Hip Pitch
    targetAngles[7] = AL::ALValue::array(0.0f,0.2f,0.0f); // Left Hip Roll
    targetAngles[8] = AL::ALValue::array(0.0f,0.0f,0.0f); // Left Knee Pitch



    /** Set the corresponding time lists, in seconds. */
    AL::ALValue targetTimes;
    targetTimes.arraySetSize(9);
    targetTimes[0] = AL::ALValue::array(1.0f,3.0f,4.0f);
    targetTimes[1] = AL::ALValue::array(1.0f,3.0f,4.0f);
    targetTimes[2] = AL::ALValue::array(1.0f,3.0f,4.0f);
    targetTimes[3] = AL::ALValue::array(1.0f,3.0f,4.0f);
    targetTimes[4] = AL::ALValue::array(1.0f,3.0f,4.0f);
    targetTimes[5] = AL::ALValue::array(1.0f,3.0f,4.0f);
    targetTimes[6] = AL::ALValue::array(1.0f,3.0f,4.0f);
    targetTimes[7] = AL::ALValue::array(1.0f,3.0f,4.0f);
    targetTimes[8] = AL::ALValue::array(1.0f,3.0f,4.0f);


    /** Specify that the desired angles are absolute. */
    bool isAbsolute = true;

    /** Call the angle interpolation method. The joint will reach the
    * desired angles at the desired times.
    */
    motion.angleInterpolation(jointName, targetAngles, targetTimes, isAbsolute);

	return 0;
}

int shutDown(AL::ALMotionProxy motion){
	AL::ALValue jointName = AL::ALValue::array("LElbowYaw", "RElbowYaw","LElbowRoll", "RElbowRoll", "LShoulderRoll","LShoulderPitch", "RShoulderRoll","RShoulderPitch", "LWristYaw","RWristYaw");
	/** Target stiffness. */
	AL::ALValue stiffness = 1.0f;
	/** Time (in seconds) to reach the target. */
	AL::ALValue time = 1.0f;
	/** Remove the stiffness on the arms. */
	stiffness = 0.0f;
	time = 1.0f;
	motion.stiffnessInterpolation(jointName, stiffness, time);
}

int instructions(AL::ALTextToSpeechProxy talk, AL::ALMotionProxy motion)
{
	//How to play simon says
	talk.say("These are the instructions for Simon Says");

	talk.say("I will call out different instructions for example, simon says Hands on head. But make sure you hear simon says before you perform the action.");
	handsOnHead(motion);
}
int main(int argc, char** argv) {

 SDL_Init(SDL_INIT_EVERYTHING);
 SDL_Window* window = SDL_CreateWindow("Test",0,0,800,600,SDL_WINDOW_SHOWN);
 SDL_Event e;

nite::NiTE::initialize();
for(;;)
{
	SDL_PollEvent(&e);


}
  if(argc != 2)
  {
    std::cerr << "Wrong number of arguments!" << std::endl;
    exit(2);
  }

  char key;


  int input;

  try
  {
  	AL::ALMotionProxy motion(argv[1], 9559);
  	//create object talk
	AL::ALTextToSpeechProxy talk(argv[1],9559);
  	motion.wakeUp();
    while(true){
    	std::cout << "1 : Hands on hip" << std::endl;
    	std::cout << "2 : Hands on head" << std::endl;
    	std::cout << "3 : Hands out in front"<< std::endl;
    	std::cout << "4 : Hands on shoulder"<< std::endl;
    	std::cout << "5 : Squat"<< std::endl;
    	std::cout << "6 : Wave left"<< std::endl;
    	std::cout << "7 : Wave right"<< std::endl;
    	std::cout << "8 : Stand on one leg"<< std::endl;
    	std::cout << "9 : Exit"<< std::endl;
    	std::cout << ":";

	    std::cin >> input;
	    if(input == 1){
/*
	    	std::thread tempThread(&AL::ALTextToSpeechProxy::say, &talk, "Simon says, hands on hips");
				tempThread.detach();
	    	std::thread tempThread2(handsOnHips,motion);
				tempThread2.detach();*/

	    }
		else if(input == 2){
			talk.say("Simon says, hands on head");
			handsOnHead(motion);

		}
		else if(input == 3){
			talk.say("Simon Says, hands out in front");
			handsInFront(motion);
		}
		else if(input == 4){
			talk.say("Simon says, hands on shoulders");
			handsOnShoulders(motion);
		}
		else if(input ==5){
			talk.say("Simon says, Squat");
			squat(motion);
		}
		else if(input == 6){
			talk.say("Simon says, wave with your left hand");
			leftWave(motion);
		}
		else if(input== 7){
			talk.say("Simon says, wave with your right hand");
			rightWave(motion);
		}
		else if(input == 8){
			talk.say("Simon says, Stand on one leg");

			//raiseOneLeg(motion);
		}
		else if(input == 9)
		{
			talk.say("Going to sleep");
			motion.rest();
			break;

		}
    }


  }
  catch (const AL::ALError& e) {
    std::cerr << "Caught exception: " << e.what() << std::endl;
    exit(1);
  }
  exit(0);
}

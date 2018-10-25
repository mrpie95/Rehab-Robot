/*
 * Copyright (c) 2012-2018 SoftBank Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */
#include <iostream>
#include <alerror/alerror.h>
#include <alproxies/albehaviormanagerproxy.h>
#include <alproxies/almotionproxy.h>
#include <alproxies/alrobotpostureproxy.h>
#include <thread>

using namespace std;

class Gesture {
	
	public:
    
	static void elephantHeadAnimation(AL::ALMotionProxy motion)
	{
  	AL::ALValue jointName = AL::ALValue::array("HeadPitch","HeadYaw");
  	// Target stiffness.
  	AL::ALValue stiffness = 1.0f;
  	// Time (in seconds) to reach the target.
  	AL::ALValue time = 1.0f;
  	 // Call the stiffness interpolation method.
  	motion.stiffnessInterpolation(jointName, stiffness, time);
   	// Hands on head


	  // Set the target angle list, in radians.
	  AL::ALValue targetAngles;
	  targetAngles.arraySetSize(2);
	  //
	  targetAngles[0] = AL::ALValue::array(-0.2129f,0.5149f,0.149f,0.5149f,0.149f,0.5149f,0.2745f, -0.1963);
	  targetAngles[1] = AL::ALValue::array(-0.0454f,-0.3735f, -0.3708f, -0.3735f, -0.3708f, -0.3735, 0.03677f, -0.0214f);



  // Set the corresponding time lists, in seconds.
  AL::ALValue targetTimes;
  targetTimes.arraySetSize(2);
  targetTimes[0] = AL::ALValue::array(0.24f, 0.44f, 0.98f, 1.68f, 2.22f, 2.88f, 3.14f, 3.40f);
  targetTimes[1] = AL::ALValue::array(0.24f, 0.44f, 0.98f, 1.68f, 2.22f, 2.88f, 3.14f, 3.40f);


   // Specify that the desired angles are absolute.
  bool isAbsolute = true;


  motion.angleInterpolation(jointName, targetAngles, targetTimes, isAbsolute);

}

	static void elephantArmAnimation(AL::ALMotionProxy motion)
	{
	  AL::ALValue jointName = AL::ALValue::array("LElbowRoll","LElbowYaw","LHand", "LShoulderPitch", "LShoulderRoll",
		                                     "LWristYaw", "RElbowRoll", "RElbowYaw","RHand", "RShoulderPitch");
	  // Target stiffness.
	  AL::ALValue stiffness = 1.0f;
	  // Time (in seconds) to reach the target.
	  AL::ALValue time = 1.0f;
	   // Call the stiffness interpolation method.
	  motion.stiffnessInterpolation(jointName, stiffness, time);
	   // Hands on head


	  // Set the target angle list, in radians.
	  AL::ALValue targetAngles;
	  targetAngles.arraySetSize(10);
	  //
	  targetAngles[0] = AL::ALValue::array(-0.849f, -1.54f, -1.54f, -1.54f, -1.54f, -1.54f, -1.22f, -0.419f);
	  targetAngles[1] = AL::ALValue::array(0.0014f, 0.105f,0.105f,0.105f,0.105f,0.105f,0.0017f,0.005f);
	  targetAngles[2] = AL::ALValue::array(0.001f, 0.011f, 0.011f,0.011f,0.011f,0.011f,0.0017f, 0.0054f);
	  targetAngles[3] = AL::ALValue::array(0.1954f, -0.4031f, -0.6543f, -0.403f, 0.6543f, -0.403f, 1.53f, 1.53f);
	  targetAngles[4] = AL::ALValue::array(0.0f,0.027f, 0.0f,0.027f, 0.0f, -1.3439,-1.186f);
	  targetAngles[5] = AL::ALValue::array(-0.766f, 0.0f, 0.0f, 0.0f,0.0f,0.0f,-0.3021f,0.0889f);
	  targetAngles[6] = AL::ALValue::array(1.248f, 0.534f, 0.034f, 0.88f, 0.534f,0.034f, 0.88f, 0.534f, 1.29f, 0.41f);
	  targetAngles[7] = AL::ALValue::array(1.42f, 1.24f, 1.24f, 1.24f, 1.24f, 1.24f, 1.396f, 1.18f);
	  targetAngles[8] = AL::ALValue::array(0.0115f, 0.011f, 0.017f, 0.011f, 0.017f, 0.0017f, 0.005f);
	  targetAngles[9] = AL::ALValue::array(0.796f, 0.531f, -0.523f, 0.531f, -0.523f, 0.531f, 1.59f, 1.53f);






	  // Set the corresponding time lists, in seconds.
	  AL::ALValue targetTimes;
	  targetTimes.arraySetSize(10);
	  targetTimes[0] = AL::ALValue::array(0.28f, 0.48f, 1.02f, 1.72f, 2.26f, 2.92f, 3.18f, 3.44f);
	  targetTimes[1] = AL::ALValue::array(0.28f, 0.48f, 1.02f, 1.72f, 2.26f, 2.92f, 3.18f, 3.44f);
	  targetTimes[2] = AL::ALValue::array(0.28f, 0.48f, 1.02f, 1.72f, 2.26f, 2.92f, 3.18f, 3.44f);
	  targetTimes[3] = AL::ALValue::array(0.28f, 0.48f, 1.02f, 1.72f, 2.26f, 2.92f, 3.18f, 3.44f);
	  targetTimes[4] = AL::ALValue::array(0.48f, 1.02f, 1.72f, 2.26f, 2.92f, 3.18f, 3.44f);
	  targetTimes[5] = AL::ALValue::array(0.28f, 0.48f, 1.02f, 1.72f, 2.26f, 2.92f, 3.18f, 3.44f);
	  targetTimes[6] = AL::ALValue::array(0.24f, 0.44f, 0.72f, 1.24f, 1.68f, 1.96f, 2.28f, 2.88f, 3.14f, 3.4f);
	  targetTimes[7] = AL::ALValue::array(0.24f, 0.44f, 0.98f, 1.68f, 2.22f, 2.88f, 3.14f, 3.4f);
	  targetTimes[8] = AL::ALValue::array(0.24f, 0.70f, 1.24f, 1.94f, 2.48f, 3.14f, 3.4f);
	  targetTimes[9] = AL::ALValue::array(0.24f, 0.44f, 0.98f, 1.68f, 2.22f, 2.88f, 3.14f, 3.4f);


	  // Specify that the desired angles are absolute.
	  bool isAbsolute = true;


	  motion.angleInterpolation(jointName, targetAngles, targetTimes, isAbsolute);

	}

	int elephantShoulderLeftLegAnimation(AL::ALMotionProxy motion)
	{
	  AL::ALValue jointName = AL::ALValue::array("RShoulderRoll", "RWristYaw"
		                                      /*"LAnklePitch", "LAnkleRoll",
		                                      "LHipPitch", "LHipRoll", "LHipYawPitch",
		                                      "LKneePitch"*/ );
	  // Target stiffness.
	  AL::ALValue stiffness = 1.0f;
	  // Time (in seconds) to reach the target.
	  AL::ALValue time = 1.0f;
	   // Call the stiffness interpolation method.
	  motion.stiffnessInterpolation(jointName, stiffness, time);
	   // Hands on head


	  // Set the target angle list, in radians.
	  AL::ALValue targetAngles;
	  targetAngles.arraySetSize(2);
	  targetAngles[0] = AL::ALValue::array(  0.22f,   0.188f, 0.22f, 0.188f, 0.22f, 0.21f, -0.12f);
	  targetAngles[1] = AL::ALValue::array( 0.494f,   -1.27f, -1.26f, -1.27f, -1.26f, -1.27f, 0.883f, 0.086f);
	  /*targetAngles[2] = AL::ALValue::array( -0.03f,  -0.122f, -0.148f, -0.122f, -0.148f, 0.0857f);
	  targetAngles[3] = AL::ALValue::array(-0.144f,  -0.147f, -0.139f, -0.147f, -0.139f, -0.132f);
	  targetAngles[4] = AL::ALValue::array(-0.423f,    0.12f, -0.69f, 0.12f, -0.69f, 0.133f);
	  targetAngles[5] = AL::ALValue::array( 0.101f,   0.150f, 0.087f, 0.150f, 0.087f, 0.095f);
	  targetAngles[6] = AL::ALValue::array( -0.29f,  -0.183f, -0.25f, -0.183f, -0.25f, -0.156f);
	  targetAngles[7] = AL::ALValue::array( 0.486f,   0.271f, 0.764f, 0.271f, 0.764f, -0.092f);

	*/




	  // Set the corresponding time lists, in seconds.
	  AL::ALValue targetTimes;
	  targetTimes.arraySetSize(2);
	  targetTimes[0] = AL::ALValue::array(0.44f, 0.98f, 1.68f, 2.22f, 2.88f, 3.14f, 3.4f);
	  targetTimes[1] = AL::ALValue::array(0.24f, 0.44f, 0.98f, 1.68f, 2.22f, 2.88f, 3.14f, 3.4f);
	/*
	  targetTimes[2] = AL::ALValue::array(0.44f, 0.92f, 1.62f, 2.16f, 2.82f, 3.34f);
	  targetTimes[3] = AL::ALValue::array(0.44f, 0.92f, 1.62f, 2.16f, 2.82f, 3.34f);
	  targetTimes[4] = AL::ALValue::array(0.44f, 0.92f, 1.62f, 2.16f, 2.82f, 3.34f);
	  targetTimes[5] = AL::ALValue::array(0.44f, 0.92f, 1.62f, 2.16f, 2.82f, 3.34f);
	  targetTimes[6] = AL::ALValue::array(0.44f, 0.92f, 1.62f, 2.16f, 2.82f, 3.34f);
	  targetTimes[7] = AL::ALValue::array(0.44f, 0.92f, 1.62f, 2.16f, 2.82f, 3.34f);
	*/

	  // Specify that the desired angles are absolute.
	  bool isAbsolute = true;


	  motion.angleInterpolation(jointName, targetAngles, targetTimes, isAbsolute);
	}

	int elephantRightLegAnimation(AL::ALMotionProxy motion)
	{
	  AL::ALValue jointName = AL::ALValue::array("RAnklePitch", "RAnkleRoll",
		                                      "RHipPitch", "RHipRoll", "RHipYawPitch",
		                                      "RKneePitch");
	  // Target stiffness.
	  AL::ALValue stiffness = 1.0f;
	  // Time (in seconds) to reach the target.
	  AL::ALValue time = 1.0f;
	   // Call the stiffness interpolation method.
	  motion.stiffnessInterpolation(jointName, stiffness, time);
	   // Hands on head


	  // Set the target angle list, in radians.
	  AL::ALValue targetAngles;
	  targetAngles.arraySetSize(6);
	  targetAngles[0] = AL::ALValue::array(-0.038f, -0.08f, -0.211f, -0.08f, -0.21f, 0.1f);
	  targetAngles[1] = AL::ALValue::array(0.179f, 0.216f, 0.12f, 0.216f, 0.12f, 0.13f);
	  targetAngles[2] = AL::ALValue::array(-0.40, 0.19f, -0.705f, 0.198f, -0.705, 0.123f);
	  targetAngles[3] = AL::ALValue::array(-0.124f, -0.21f, -0.064f, -0.21f, -0.064f, -0.09f);
	  targetAngles[4] = AL::ALValue::array(-0.288f, -0.184f, -0.253f, -0.184f, -0.253f, -0.156);
	  targetAngles[5] = AL::ALValue::array(0.466f, 0.131f, 0.815f, 0.131f, 0.815f, -0.083f);



	  // Set the corresponding time lists, in seconds.
	  AL::ALValue targetTimes;
	  targetTimes.arraySetSize(6);
	  targetTimes[0] = AL::ALValue::array(0.44f, 0.92f, 1.62f, 2.16f, 2.82f, 3.34f);
	  targetTimes[1] = AL::ALValue::array(0.44f, 0.92f, 1.62f, 2.16f, 2.82f, 3.34f);
	  targetTimes[2] = AL::ALValue::array(0.44f, 0.92f, 1.62f, 2.16f, 2.82f, 3.34f);
	  targetTimes[3] = AL::ALValue::array(0.44f, 0.92f, 1.62f, 2.16f, 2.82f, 3.34f);
	  targetTimes[4] = AL::ALValue::array(0.44f, 0.92f, 1.62f, 2.16f, 2.82f, 3.34f);
	  targetTimes[5] = AL::ALValue::array(0.44f, 0.92f, 1.62f, 2.16f, 2.82f, 3.34f);


	  // Specify that the desired angles are absolute.
	  bool isAbsolute = true;


	  motion.angleInterpolation(jointName, targetAngles, targetTimes, isAbsolute);
	}

};

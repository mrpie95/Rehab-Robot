#include <iostream>
#include <alcommon/alproxy.h>
#include <alcommon/almodule.h>
#include <alerror/alerror.h>

class monkeyGesture {

	public:

//contains gorillaHeadAnimation
//contains gorillaArmAnimtion

  //moves monkeys head sparatically
  static void monkeyHeadAnimation(AL::ALMotionProxy motion)
  {
    AL::ALValue jointName = AL::ALValue::array("HeadYaw", "HeadPitch");
    // Target stiffness.
    AL::ALValue stiffness = 1.0f;
     // Time (in seconds) to reach the target. */
    AL::ALValue time = 1.0f;
    // Call the stiffness interpolation method. */
    motion.stiffnessInterpolation(jointName, stiffness, time);
     // Hands on head


     // Set the target angle list, in radians.
    AL::ALValue targetAngles;
    targetAngles.arraySetSize(2);
    //
    targetAngles[0] = AL::ALValue::array(-0.5f,0.5f,-0.5f,0.5f,-0.5f,0.5f,-0.5f,-0.5f,0.5f,-0.5f); // Head Yaw
    targetAngles[1] = AL::ALValue::array(-0.5f,0.5f,0.5f,-0.5f,-0.5f,0.5f,0.5f,-0.5f,-0.5f,0.5f);   // Head Pitch



    // Set the corresponding time lists, in seconds.
    AL::ALValue targetTimes;
    targetTimes.arraySetSize(2);
    targetTimes[0] = AL::ALValue::array(1.0f,1.33f,1.66f,2.0f,2.33f,2.66f,3.0f,3.33f,3.66f,4.0f);
    targetTimes[1] = AL::ALValue::array(1.0f,1.33f,1.66f,2.0f,2.33f,2.66f,3.0f,3.33f,3.66f,4.0f);

    bool isAbsolute = true;


    motion.angleInterpolation(jointName, targetAngles, targetTimes, isAbsolute);
  }

  static void monkeyBodyAnimation(AL::ALMotionProxy motion)
  {
    AL::ALValue jointName = AL::ALValue::array("LElbowYaw","LElbowRoll", "LShoulderRoll","LShoulderPitch", "LWristYaw",
                                                "RElbowYaw", "RElbowRoll", "RShoulderRoll","RShoulderPitch", "RWristYaw");
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
    //left arm
    targetAngles[0] = AL::ALValue::array(0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f); // left elbow yaw
    targetAngles[1] = AL::ALValue::array(-1.5f,-0.5f,-1.5f,-0.5f,-1.5f,-0.5f,-1.5f); // left elbow roll (-88.5 - 2, 1.5446, 0.0349)
    targetAngles[2] = AL::ALValue::array(1.3f,1.0f,1.3f,1.0f,1.3f,1.0f,1.3f); // left shoulder roll
    targetAngles[3] = AL::ALValue::array(1.0f,1.3f,1.0f,1.3f,1.0f,1.3f,1.0f); // left shoulder pitch (-119.5,119.5 :: -2.0857, 2.0857)
    targetAngles[4] = AL::ALValue::array(0.2f,0.4f,0.2f,0.4f,0.2f,0.4f,0.2f); // left wrist yaw
    //right arm
    targetAngles[5] = AL::ALValue::array(0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f); // right elbowyaw (-119.5,119.5 :: -2.0857, 2.0857)
    targetAngles[6] = AL::ALValue::array(1.5f,0.5f,1.5f,0.5f,1.5f,0.5f,1.5f); // right elbow roll
    targetAngles[7] = AL::ALValue::array(-1.3f,-1.0f,-1.3f,-1.0f,-1.3f,-1.0f,-1.3f); // right shoulder roll
    targetAngles[8] = AL::ALValue::array(1.0f,1.3f,1.0f,1.3f,1.0f,1.3f,1.0f); // right shoulder pitch
    targetAngles[9] = AL::ALValue::array(0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f); // right wrist yaw



    // Set the corresponding time lists, in seconds.
    AL::ALValue targetTimes;
    targetTimes.arraySetSize(10);
    //left arm times
    targetTimes[0] = AL::ALValue::array(2.0f,2.33f,2.66f,3.0f,3.3f,3.6f,4.0f);
    targetTimes[1] = AL::ALValue::array(2.0f,2.33f,2.66f,3.0f,3.3f,3.6f,4.0f);
    targetTimes[2] = AL::ALValue::array(2.0f,2.33f,2.66f,3.0f,3.3f,3.6f,4.0f);
    targetTimes[3] = AL::ALValue::array(2.0f,2.33f,2.66f,3.0f,3.3f,3.6f,4.0f);
    targetTimes[4] = AL::ALValue::array(2.0f,2.33f,2.66f,3.0f,3.3f,3.6f,4.0f);
    //right srm times
    targetTimes[5] = AL::ALValue::array(2.0f,2.33f,2.66f,3.0f,3.3f,3.6f,4.0f);
    targetTimes[6] = AL::ALValue::array(2.0f,2.33f,2.66f,3.0f,3.3f,3.6f,4.0f);
    targetTimes[7] = AL::ALValue::array(2.0f,2.33f,2.66f,3.0f,3.3f,3.6f,4.0f);
    targetTimes[8] = AL::ALValue::array(2.0f,2.33f,2.66f,3.0f,3.3f,3.6f,4.0f);
    targetTimes[9] = AL::ALValue::array(2.0f,2.33f,2.66f,3.0f,3.3f,3.6f,4.0f);
     // Specify that the desired angles are absolute.
    bool isAbsolute = true;


    motion.angleInterpolation(jointName, targetAngles, targetTimes, isAbsolute);
  }


  static void monkeyLegAnimation(AL::ALMotionProxy motion)
  {
    AL::ALValue jointName = AL::ALValue::array("RHipRoll", "LHipRoll", "RAnkleRoll", "LAnkleRoll",
                                              "RKneePitch","LKneePitch", "RHipYawPitch", "LHipYawPitch",
                                              "RHipPitch", "LHipPitch");
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
    targetAngles[0] = AL::ALValue::array(0.05f,0.10f,-0.15f,-0.4f,-0.4f,-0.4f,-0.4f);    // right hip roll
    targetAngles[1] = AL::ALValue::array(-0.05f,-0.10f,-0.15f,-0.2f,-0.2f,-0.2f,-0.2f);  // left hip roll
    targetAngles[2] = AL::ALValue::array(0.1f,0.15f,0.2f,0.2f,0.2f,0.2f,0.2f);           // right ankle roll
    targetAngles[3] = AL::ALValue::array(0.05f,0.1f,0.15f,0.15f,0.15f,0.15f,0.15f);           //LEFT ANKLE ROLL
    targetAngles[4] = AL::ALValue::array(0.0f,0.5f,1.0f,1.2f,1.0f,0.5f,0.3f);            // right Knee Pitch
    targetAngles[5] = AL::ALValue::array(0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f);            //LEFT knee pitch
    targetAngles[6] = AL::ALValue::array(0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f);            // right hip yaw pitch
    targetAngles[7] = AL::ALValue::array(-0.4f,-0.4f,-0.4f,-0.4f,-0.4f,-0.4f,-0.4);     //LEFT hip yaw pitch
    targetAngles[8] = AL::ALValue::array(0.1f,0.5f,1.0f,0.0f,0.0f,0.0f,0.0f);            // right hip pitch
    targetAngles[9] = AL::ALValue::array(0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f);             //LEFT hip pitch


    // targetAngles[4] = AL::ALValue::array(0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f);



    // Set the corresponding time lists, in seconds.
    AL::ALValue targetTimes;
    targetTimes.arraySetSize(10);
    targetTimes[0] = AL::ALValue::array(1.0f,2.0f,3.0f,4.0f,4.5f, 5.0f, 5.2f);
    targetTimes[1] = AL::ALValue::array(1.0f,2.0f,3.0f,4.0f,4.5f, 5.0f, 5.2f);
    targetTimes[2] = AL::ALValue::array(1.0f,2.0f,3.0f,4.0f,4.5f,5.0f, 5.2f);
    targetTimes[3] = AL::ALValue::array(1.0f,2.0f,3.0f,4.0f,4.5f, 5.0f, 5.2f);
    targetTimes[4] = AL::ALValue::array(1.0f,2.0f,3.0f,4.0f,4.5f,5.0f, 5.2f);
    targetTimes[5] = AL::ALValue::array(1.0f,2.0f,3.0f,4.0f, 4.5f,5.0f, 5.2f);
    targetTimes[6] = AL::ALValue::array(1.0f,2.0f,3.0f,4.0f,4.5f,5.0f, 5.2f);
    targetTimes[7] = AL::ALValue::array(1.0f,2.0f,3.0f,4.0f, 4.5f,5.0f, 5.2f);
    targetTimes[8] = AL::ALValue::array(1.0f,2.0f,3.0f,4.0f,4.5f,5.0f, 5.2f);
    targetTimes[9] = AL::ALValue::array(1.0f,2.0f,3.0f,4.0f, 4.5f,5.0f, 5.2f);
    // targetTimes[4] = AL::ALValue::array(2.0f,2.33f,2.66f,3.0f,3.3f,3.6f,4.0f);

     // Specify that the desired angles are absolute.
    bool isAbsolute = true;


    motion.angleInterpolation(jointName, targetAngles, targetTimes, isAbsolute);
  }




};

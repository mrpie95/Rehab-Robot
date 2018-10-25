#include <iostream>
#include <alcommon/alproxy.h>
#include <alcommon/almodule.h>
#include <alproxies/alrobotpostureproxy.h>
#include <alproxies/alanimatedspeechproxy.h>
#include <alproxies/alautonomousmovesproxy.h>
#include <alerror/alerror.h>

class gorillaGesture {

	public:

//contains gorillaHeadAnimation
//contains gorillaArmAnimtion

  static void gorillaHeadAnimation(AL::ALMotionProxy motion)
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
    targetAngles[1] = AL::ALValue::array(0.2f,0.4f,0.2f,0.4f,0.2f,0.4f,0.2f,0.4f,0.2f,0.4f);   // Head Pitch



    // Set the corresponding time lists, in seconds.
    AL::ALValue targetTimes;
    targetTimes.arraySetSize(2);
    targetTimes[0] = AL::ALValue::array(0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.50f, 4.0f, 4.5f, 5.0f);
    targetTimes[1] = AL::ALValue::array(0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.50f, 4.0f, 4.5f, 5.0f);

    bool isAbsolute = true;


    motion.angleInterpolation(jointName, targetAngles, targetTimes, isAbsolute);
}

static void gorillaArmAnimtion(AL::ALMotionProxy motion){
  AL::ALValue jointName = AL::ALValue::array("LShoulderPitch", "LElbowRoll",
                                              "LShoulderRoll", "LElbowYaw", "LWristYaw",
                                              "RShoulderPitch", "RElbowRoll",
                                              "RShoulderRoll", "RElbowYaw", "RWristYaw");
  // Target stiffness.
  AL::ALValue stiffness = 1.0f;
   // Time (in seconds) to reach the target. */
  AL::ALValue time = 1.0f;
  // Call the stiffness interpolation method. */
  motion.stiffnessInterpolation(jointName, stiffness, time);
   // Hands on head


   // Set the target angle list, in radians.
  AL::ALValue targetAngles;
  targetAngles.arraySetSize(10);
  //
  targetAngles[0] = AL::ALValue::array(0.3f,0.5f,0.3f,0.5f,0.3f,0.5f,0.3f,0.5f,0.3f,0.5f); // Left shoulder pitch
  targetAngles[1] = AL::ALValue::array(-1.5f,-1.0f,-1.5f,-1.0f,-1.5f,-1.0f,-1.5f,-1.0f,-1.5f,-1.0f);   // left elbow roll
  targetAngles[2] = AL::ALValue::array(-0.3f,0.5f,-0.3f,0.5f,-0.3f,0.5f,-0.3f,0.5f,-0.3f,0.5f);   // left shoulder roll
  targetAngles[3] = AL::ALValue::array(-0.5f,-0.4f,-0.5f,-0.4f,-0.5f,-0.4f,-0.5f,-0.4f,-0.5f,-0.4f);   // left elbow yaw
  targetAngles[4] = AL::ALValue::array(-0.4f,-0.4f,-0.8f,-0.8f,-0.4f,-0.4f,-0.8f,-0.8f,-1.2f,-1.4f);   // left wrist yaw
  targetAngles[5] = AL::ALValue::array(0.3f,0.5f,0.3f,0.5f,0.3f,0.5f,0.3f,0.5f,0.3f,0.5f); // right shoulder pitch
  targetAngles[6] = AL::ALValue::array(1.0f,1.5f,1.0f,1.5f,1.0f,1.5f,1.0f,1.5f,1.0f,1.5f);   // right elbow roll
  targetAngles[7] = AL::ALValue::array(-0.5f,0.3f,-0.5f,0.3f,-0.5f,0.3f,-0.5f,0.3f,-0.5f,0.3f);   // right shoulder roll
  targetAngles[8] = AL::ALValue::array(0.5f,0.4f,0.5f,0.4f,0.5f,0.4f,0.5f,0.4f,0.5f,0.4f);   // right elbow yaw
  targetAngles[9] = AL::ALValue::array(0.4f,0.4f,0.8f,0.8f,0.4f,0.4f,0.8f,0.8f,1.2f,1.4f);   // right wrist yaw



  // Set the corresponding time lists, in seconds.
  AL::ALValue targetTimes;
  targetTimes.arraySetSize(10);
  targetTimes[0] = AL::ALValue::array(0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.50f, 4.0f, 4.5f, 5.0f);
  targetTimes[1] = AL::ALValue::array(0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.50f, 4.0f, 4.5f, 5.0f);
  targetTimes[2] = AL::ALValue::array(0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.50f, 4.0f, 4.5f, 5.0f);
  targetTimes[3] = AL::ALValue::array(0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.50f, 4.0f, 4.5f, 5.0f);
  targetTimes[4] = AL::ALValue::array(0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.50f, 4.0f, 4.5f, 5.0f);
  targetTimes[5] = AL::ALValue::array(0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.50f, 4.0f, 4.5f, 5.0f);
  targetTimes[6] = AL::ALValue::array(0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.50f, 4.0f, 4.5f, 5.0f);
  targetTimes[7] = AL::ALValue::array(0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.50f, 4.0f, 4.5f, 5.0f);
  targetTimes[8] = AL::ALValue::array(0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.50f, 4.0f, 4.5f, 5.0f);
  targetTimes[9] = AL::ALValue::array(0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.50f, 4.0f, 4.5f, 5.0f);

  bool isAbsolute = true;


  motion.angleInterpolation(jointName, targetAngles, targetTimes, isAbsolute);
}


};

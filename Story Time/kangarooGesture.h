#include <iostream>
#include <alcommon/alproxy.h>
#include <alcommon/almodule.h>
#include <alproxies/alrobotpostureproxy.h>
#include <alproxies/alanimatedspeechproxy.h>
#include <alproxies/alautonomousmovesproxy.h>
#include <alerror/alerror.h>

class kangarooGesture {

	public:

  //contains gorillaHeadAnimation
  //contains gorillaArmAnimtion
  static void kangarooLegAnimation(AL::ALMotionProxy motion)
  {
  AL::ALValue jointName = AL::ALValue::array("RKneePitch","RAnklePitch", "LKneePitch","LAnklePitch", "LHipPitch", "RHipPitch");
  /** Target stiffness. */
  AL::ALValue stiffness = 1.0f;
  /** Time (in seconds) to reach the target. */
  AL::ALValue time = 1.0f;
  /** Call the stiffness interpolation method. */
  motion.stiffnessInterpolation(jointName, stiffness, time);
  /** Hands on head */


  /** Set the target angle list, in radians. */
  AL::ALValue targetAngles;
  targetAngles.arraySetSize(6);
  //
  targetAngles[0] = AL::ALValue::array(1.5f,1.5f,1.5f,1.5f,1.5f,1.5f,1.5f); // right knee pitch
  targetAngles[1] = AL::ALValue::array(-0.51f,-0.51f,-0.51f,-0.51f,-0.51f,-0.51f,-0.51); // right ankle pitch
  targetAngles[2] = AL::ALValue::array(1.5f,1.5f,1.5f,1.5f,1.5f,1.5f,1.5f); // left knee pitch
  targetAngles[3] = AL::ALValue::array(-0.51f,-0.51f,-0.51f,-0.51f,-0.51f,-0.51f,-0.51); // left ankle pitch
  targetAngles[4] = AL::ALValue::array(-1.2f,-1.2f,-1.2f,-1.2f,-1.2f,-1.2f,-1.2f); // left hip pitch
  targetAngles[5] = AL::ALValue::array(-1.2f,-1.2f,-1.2f,-1.2f,-1.2f,-1.2f,-1.2f); // right hip pitch



  /** Set the corresponding time lists, in seconds. */
  AL::ALValue targetTimes;
  targetTimes.arraySetSize(6);
  targetTimes[0] = AL::ALValue::array(2.0f,2.33f,2.66f,3.0f,3.3f,3.6f,4.0f);
  targetTimes[1] = AL::ALValue::array(2.0f,2.33f,2.66f,3.0f,3.3f,3.6f,4.0f);
  targetTimes[2] = AL::ALValue::array(2.0f,2.33f,2.66f,3.0f,3.3f,3.6f,4.0f);
  targetTimes[3] = AL::ALValue::array(2.0f,2.33f,2.66f,3.0f,3.3f,3.6f,4.0f);
  targetTimes[4] = AL::ALValue::array(2.0f,2.33f,2.66f,3.0f,3.3f,3.6f,4.0f);
  targetTimes[5] = AL::ALValue::array(2.0f,2.33f,2.66f,3.0f,3.3f,3.6f,4.0f);

  /** Specify that the desired angles are absolute. */
  bool isAbsolute = true;

  /** Call the angle interpolation method. The joint will reach the
  * desired angles at the desired times.
  */
  motion.angleInterpolation(jointName, targetAngles, targetTimes, isAbsolute);


  }

 static void kangarooBodyAnimation(AL::ALMotionProxy motion )
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


    /** Set the target angle list, in radians. */
    AL::ALValue targetAngles;
    targetAngles.arraySetSize(10);
    //
    targetAngles[0] = AL::ALValue::array(-1.5f,-1.5f,-1.5f,-1.5f,-1.5f,-1.5f,-1.5f); //left elbowyaw
    targetAngles[1] = AL::ALValue::array(-1.5f,-1.5f,-1.5f,-1.5f,-1.5f,-1.5f,-1.5f); //left elbow roll
    targetAngles[2] = AL::ALValue::array(-0.31f,-0.31f,-0.31f,-0.31f,-0.31f,-0.31f,-0.31); // left shoulder roll
    targetAngles[3] = AL::ALValue::array(1.1f,1.6f,0.8f,1.6f,0.8f,1.6f,0.8f); // left sholder pitch
    targetAngles[4] = AL::ALValue::array(1.2f,1.2f,1.2f,1.2f,1.2f,1.2f,1.2f); // Left wrist yaw
    targetAngles[5] = AL::ALValue::array(1.5f,1.5f,1.5f,1.5f,1.5f,1.5f,1.5f); //right elbowyaw
    targetAngles[6] = AL::ALValue::array(1.5f,1.5f,1.5f,1.5f,1.5f,1.5f,1.5f); //right elbow roll
    targetAngles[7] = AL::ALValue::array(0.31f,0.31f,0.31f,0.31f,0.31f,0.31f,0.31f); // right shoulder roll
    targetAngles[8] = AL::ALValue::array(1.1f,1.6f,0.8f,1.6f,0.8f,1.6f,0.8f); // right sholder pitch
    targetAngles[9] = AL::ALValue::array(-1.2f,-1.2f,-1.2f,-1.2f,-1.2f,-1.2f,-1.2f); // right wrist yaw




    // Set the corresponding time lists, in seconds.
    AL::ALValue targetTimes;
    targetTimes.arraySetSize(10);
    targetTimes[0] = AL::ALValue::array(2.0f,2.33f,2.66f,3.0f,3.3f,3.6f,4.0f);
    targetTimes[1] = AL::ALValue::array(2.0f,2.33f,2.66f,3.0f,3.3f,3.6f,4.0f);
    targetTimes[2] = AL::ALValue::array(2.0f,2.33f,2.66f,3.0f,3.3f,3.6f,4.0f);
    targetTimes[3] = AL::ALValue::array(2.0f,2.33f,2.66f,3.0f,3.3f,3.6f,4.0f);
    targetTimes[4] = AL::ALValue::array(2.0f,2.33f,2.66f,3.0f,3.3f,3.6f,4.0f);
    targetTimes[5] = AL::ALValue::array(2.0f,2.33f,2.66f,3.0f,3.3f,3.6f,4.0f);
    targetTimes[6] = AL::ALValue::array(2.0f,2.33f,2.66f,3.0f,3.3f,3.6f,4.0f);
    targetTimes[7] = AL::ALValue::array(2.0f,2.33f,2.66f,3.0f,3.3f,3.6f,4.0f);
    targetTimes[8] = AL::ALValue::array(2.0f,2.33f,2.66f,3.0f,3.3f,3.6f,4.0f);
    targetTimes[9] = AL::ALValue::array(2.0f,2.33f,2.66f,3.0f,3.3f,3.6f,4.0f);
    /** Specify that the desired angles are absolute. */
    bool isAbsolute = true;

    // Call the angle interpolation method. The joint will reach the
    // desired angles at the desired times.

    motion.angleInterpolation(jointName, targetAngles, targetTimes, isAbsolute);
  }


};

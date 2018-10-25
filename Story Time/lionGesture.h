#include <iostream>
#include <alcommon/alproxy.h>
#include <alcommon/almodule.h>
#include <alproxies/alrobotpostureproxy.h>
#include <alproxies/alanimatedspeechproxy.h>
#include <alproxies/alautonomousmovesproxy.h>
#include <alerror/alerror.h>
#include <thread>

class lionGesture {

	public:

//contains gorillaHeadAnimation
//contains gorillaArmAnimtion

static void lionHeadAnimation(AL::ALMotionProxy motion)
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
targetAngles[0] = AL::ALValue::array(-0.1f,-0.2f,-0.1f,0.05f,0.15f,0.25f,0.35f,0.5f,0.25f,0.05f); // Head Yaw
targetAngles[1] = AL::ALValue::array(0.2f,0.3f,0.5f,0.4f,0.2f,0.1f,-0.1f, -0.3f, -0.1f,0.0f);   // Head Pitch



// Set the corresponding time lists, in seconds.
AL::ALValue targetTimes;
targetTimes.arraySetSize(2);
targetTimes[0] = AL::ALValue::array(1.0f,1.33f,1.66f,2.0f,2.33f,2.66f,3.0f,3.33f,3.66f,4.0f);
targetTimes[1] = AL::ALValue::array(1.0f,1.33f,1.66f,2.0f,2.33f,2.66f,3.0f,3.33f,3.66f,4.0f);

bool isAbsolute = true;

motion.angleInterpolation(jointName, targetAngles, targetTimes, isAbsolute);
}


static void lionBodyAnimation(AL::ALMotionProxy motion)
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
targetAngles[0] = AL::ALValue::array(-1.5f,-1.5f,-1.5f); //left elbowyaw
targetAngles[1] = AL::ALValue::array(-1.5f,-1.1f,-0.75f); //left elbow roll
targetAngles[2] = AL::ALValue::array(-0.31f,0.05f,0.4f); // left shoulder roll d
targetAngles[3] = AL::ALValue::array(1.1f,0.25f,0.05f); // left sholder pitch d
targetAngles[4] = AL::ALValue::array(1.2f,1.2f,1.2f); // Left wrist yaw
targetAngles[5] = AL::ALValue::array(1.5f,1.5f,1.5f); //right elbowyaw
targetAngles[6] = AL::ALValue::array(1.5f,1.0f,0.8f); //right elbow roll
targetAngles[7] = AL::ALValue::array(0.31f,-0.15f,-0.31f); // right shoulder roll d
targetAngles[8] = AL::ALValue::array(1.1f,0.3f,-0.05f); // right sholder pitch d
targetAngles[9] = AL::ALValue::array(-1.2f,-1.2f,-1.2f); // right wrist yaw




// Set the corresponding time lists, in seconds.
AL::ALValue targetTimes;
targetTimes.arraySetSize(10);
targetTimes[0] = AL::ALValue::array(1.5f,2.5f,3.5f);
targetTimes[1] = AL::ALValue::array(1.5f,2.5f,3.5f);
targetTimes[2] = AL::ALValue::array(1.5f,2.5f,3.5f);
targetTimes[3] = AL::ALValue::array(1.5f,2.5f,3.5f);
targetTimes[4] = AL::ALValue::array(1.5f,2.5f,3.5f);
targetTimes[5] = AL::ALValue::array(1.5f,2.5f,3.5f);
targetTimes[6] = AL::ALValue::array(1.5f,2.5f,3.5f);
targetTimes[7] = AL::ALValue::array(1.5f,2.5f,3.5f);
targetTimes[8] = AL::ALValue::array(1.5f,2.5f,3.5f);
targetTimes[9] = AL::ALValue::array(1.5f,3.0f,3.5f);

/** Specify that the desired angles are absolute. */
bool isAbsolute = true;

motion.angleInterpolation(jointName, targetAngles, targetTimes, isAbsolute);
}


static void lionLegAnimation(AL::ALMotionProxy motion)
{
AL::ALValue jointName = AL::ALValue::array("RHipYawPitch","LHipYawPitch","RKneePitch","LKneePitch",
                                          "RAnklePitch","LAnklePitch","RHipPitch","LHipPitch");
// Target stiffness.
AL::ALValue stiffness = 1.0f;
// Time (in seconds) to reach the target.
AL::ALValue time = 1.0f;
 // Call the stiffness interpolation method.
motion.stiffnessInterpolation(jointName, stiffness, time);
 // Hands on head


// Set the target angle list, in radians.
AL::ALValue targetAngles;
targetAngles.arraySetSize(8);
//
targetAngles[0] = AL::ALValue::array(-0.05f,-0.2f,-0.3f,-0.5f,-0.3f,-0.2f,-0.05f);
targetAngles[1] = AL::ALValue::array(-0.05f,-0.2f,-0.3f,-0.5f,-0.3f,-0.2f,-0.05f);
targetAngles[2] = AL::ALValue::array(0.2f,0.7f,1.3f,1.8f, 1.3f,0.7f,0.2f);
targetAngles[3] = AL::ALValue::array(0.2f,0.7f,1.3f,1.8f,1.3f,0.7f,0.2f);
targetAngles[4] = AL::ALValue::array(-0.15f,-0.4f,-0.8f,-1.0f,-0.8f,-0.4f,-0.15f);
targetAngles[5] = AL::ALValue::array(-0.15f,-0.4f,-0.8f,-1.0f,-0.8f,-0.4f,-0.15f);
targetAngles[6] = AL::ALValue::array(-0.1f,-0.25f,-0.35f,-0.25f,-0.15f,0.05f,0.1f);
targetAngles[7] = AL::ALValue::array(-0.1f,-0.25f,-0.35f,-0.25f,-0.15f,0.05f,0.1f);



// Set the corresponding time lists, in seconds.
AL::ALValue targetTimes;
targetTimes.arraySetSize(8);
targetTimes[0] = AL::ALValue::array(0.75f,1.5f,2.25f,3.0f,3.75f,4.5f,5.25f);
targetTimes[1] = AL::ALValue::array(0.75f,1.5f,2.25f,3.0f,3.75f,4.5f,5.25f);
targetTimes[2] = AL::ALValue::array(0.75f,1.5f,2.25f,3.0f,3.75f,4.5f,5.25f);
targetTimes[3] = AL::ALValue::array(0.75f,1.5f,2.25f,3.0f,3.75f,4.5f,5.25f);
targetTimes[4] = AL::ALValue::array(0.75f,1.5f,2.25f,3.0f,3.75f,4.5f,5.25f);
targetTimes[5] = AL::ALValue::array(0.75f,1.5f,2.25f,3.0f,3.75f,4.5f,5.25f);
targetTimes[6] = AL::ALValue::array(0.75f,1.5f,2.25f,3.0f,3.75f,4.5f,5.25f);
targetTimes[7] = AL::ALValue::array(0.75f,1.5f,2.25f,3.0f,3.75f,4.5f,5.25f);


 // Specify that the desired angles are absolute.
bool isAbsolute = true;


motion.angleInterpolation(jointName, targetAngles, targetTimes, isAbsolute);
}

};

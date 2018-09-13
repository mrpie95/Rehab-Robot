#include "Robot.h"

Robot::Robot(const char * ip) : speakProxy(ip, 9559), motionProxy(ip, 9559), postureProxy(ip, 9559)
{
}

Robot::Robot(const Robot &)
{
	//actually does nothing just need a copy constructor to use mutex
}


Robot::~Robot()
{
}

void Robot::say(const char * text)
{
	std::lock_guard<std::mutex> lock(speech_mtx);
	speakProxy.say(text);
}

void Robot::shutDown()
{
	AL::ALValue jointName = AL::ALValue::array("LElbowYaw", "RElbowYaw", "LElbowRoll", "RElbowRoll", "LShoulderRoll", "LShoulderPitch", "RShoulderRoll", "RShoulderPitch", "LWristYaw", "RWristYaw");
	/** Target stiffness. */
	AL::ALValue stiffness = 1.0f;
	/** Time (in seconds) to reach the target. */
	AL::ALValue time = 1.0f;
	/** Remove the stiffness on the arms. */
	stiffness = 0.0f;
	time = 1.0f;
	motionProxy.stiffnessInterpolation(jointName, stiffness, time);
}

void Robot::wakeup()
{
	motionProxy.wakeUp();
}

void Robot::stand()
{
	std::lock_guard<std::mutex> lock(move_mtx);
	postureProxy.goToPosture("Stand", 1.0);
}

void Robot::handsOutFront()
{
	AL::ALValue jointName = AL::ALValue::array("LElbowYaw", "RElbowYaw", "LElbowRoll", "RElbowRoll", "LShoulderRoll", "LShoulderPitch", "RShoulderRoll", "RShoulderPitch", "LWristYaw", "RWristYaw");
	/** Target stiffness. */
	AL::ALValue stiffness = 1.0f;
	/** Time (in seconds) to reach the target. */
	AL::ALValue time = 1.0f;
	/** Call the stiffness interpolation method. */
	motionProxy.stiffnessInterpolation(jointName, stiffness, time);
	/** Hands on head */
	/** Set the target angle list, in radians. */
	AL::ALValue targetAngles;
	targetAngles.arraySetSize(10);
	targetAngles[0] = AL::ALValue::array(0.0f, 0.0f); //left elbowyaw
	targetAngles[1] = AL::ALValue::array(0.0f, 0.0f); // right elbow yaw
	targetAngles[2] = AL::ALValue::array(0.0f, 0.0f); //left elbow roll
	targetAngles[3] = AL::ALValue::array(0.0f, 0.0f); // right elbow roll
	targetAngles[4] = AL::ALValue::array(0.0f, 0.0f); // left shoulder roll
	targetAngles[5] = AL::ALValue::array(0.0f, 1.5f); // left sholder pitch
	targetAngles[6] = AL::ALValue::array(0.0f, 0.0f); // right shoulder roll
	targetAngles[7] = AL::ALValue::array(0.0f, 1.5f); // right shoulder pitch
	targetAngles[8] = AL::ALValue::array(0.0f, 0.0f); // Left wrist yaw
	targetAngles[9] = AL::ALValue::array(0.0f, 0.0f); // Right wrist yaw

													  /** Set the corresponding time lists, in seconds. */
	AL::ALValue targetTimes;
	targetTimes.arraySetSize(10);
	targetTimes[0] = AL::ALValue::array(3.0f, 6.0f);
	targetTimes[1] = AL::ALValue::array(3.0f, 6.0f);
	targetTimes[2] = AL::ALValue::array(3.0f, 6.0f);
	targetTimes[3] = AL::ALValue::array(3.0f, 6.0f);
	targetTimes[4] = AL::ALValue::array(3.0f, 6.0f);
	targetTimes[5] = AL::ALValue::array(3.0f, 6.0f);
	targetTimes[6] = AL::ALValue::array(3.0f, 6.0f);
	targetTimes[7] = AL::ALValue::array(3.0f, 6.0f);
	targetTimes[8] = AL::ALValue::array(3.0f, 6.0f);
	targetTimes[9] = AL::ALValue::array(3.0f, 6.0f);
	/** Specify that the desired angles are absolute. */
	bool isAbsolute = true;

	/** Call the angle interpolation method. The joint will reach the
	* desired angles at the desired times.
	*/

	std::lock_guard<std::mutex> lock(move_mtx);
	motionProxy.angleInterpolation(jointName, targetAngles, targetTimes, isAbsolute);
}




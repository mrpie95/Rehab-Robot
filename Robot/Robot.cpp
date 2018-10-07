#include "Robot.h"
#include <chrono>
#include <vector>

Robot::Robot(const char * ip) : speakProxy(ip, 9559), motionProxy(ip, 9559), postureProxy(ip, 9559), speechRecProxy(ip, 9559), memoryProxy(ip, 9559),
behaviorProxy(ip, 9559)
{
}

Robot::Robot(const Robot &)
{
	//actually does nothing just need a copy constructor to use mutex
}


Robot::~Robot()
{
}

//void Robot::async_speak_move_call(int delay_milliseconds, void(Robot::* moveFunction)(), void(Robot::* speakFunction)(const char*), const char* text)
//{
//	if (delay_milliseconds > 0)
//	{
//		std::async(std::launch::async, moveFunction, this);
//		std::this_thread::sleep_for(std::chrono::milliseconds(delay_milliseconds));
//		std::async(std::launch::async, speakFunction, this, text);
//	}
//	else
//	{
//		std::async(std::launch::async, speakFunction, this, text);
//		std::this_thread::sleep_for(std::chrono::milliseconds(delay_milliseconds));
//		std::async(std::launch::async, moveFunction, this);
//	}
//
//}

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
	std::lock_guard<std::mutex> lock(move_mtx);
	motionProxy.stiffnessInterpolation(jointName, stiffness, time);
}

void Robot::wakeup()
{
	std::lock_guard<std::mutex> lock(move_mtx);
	motionProxy.wakeUp();
}

void Robot::stand()
{
	std::lock_guard<std::mutex> lock(move_mtx);
	postureProxy.goToPosture("Stand", 1.0);
}

void Robot::dance()
{
	std::lock_guard<std::mutex> lock(std::mutex);
	behaviorProxy.runBehavior("tanya-swinburne/Dances/GangnamStyle");
}

void Robot::standOnOneLeg()
{
	//std::lock_guard<std::mutex> lock(move_mtx);
	//behaviorProxy.runBehavior("rchactionlib/DownBody/LegRaises/Left/LegRaisesLeft02");
	/*auto s = behaviorProxy.getInstalledBehaviors();

	for (auto ss : s)
	{
		std::cout << ss << '\n';
	}*/
}

void Robot::handsOutFront()
{
	AL::ALValue jointName = AL::ALValue::array("LElbowYaw", "RElbowYaw", "LElbowRoll", "RElbowRoll", "LShoulderRoll", "LShoulderPitch", "RShoulderRoll", "RShoulderPitch", "LWristYaw", "RWristYaw");
	/** Target stiffness. */
	AL::ALValue stiffness = 1.0f;
	/** Time (in seconds) to reach the target. */
	AL::ALValue time = 1.0f;
	/** Call the stiffness interpolation method. */

	std::lock_guard<std::mutex> lock(move_mtx);
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

	motionProxy.angleInterpolation(jointName, targetAngles, targetTimes, isAbsolute);
}

void Robot::handsOnHead()
{
	AL::ALValue jointName = AL::ALValue::array("LElbowYaw", "RElbowYaw", "LElbowRoll", "RElbowRoll", "LShoulderRoll", "LShoulderPitch", "RShoulderRoll", "RShoulderPitch", "LWristYaw", "RWristYaw");
	/** Target stiffness. */
	AL::ALValue stiffness = 1.0f;
	/** Time (in seconds) to reach the target. */
	AL::ALValue time = 1.0f;
	/** Call the stiffness interpolation method. */
	std::lock_guard<std::mutex> lock(move_mtx);
	motionProxy.stiffnessInterpolation(jointName, stiffness, time);
	/** Hands on head */
	/** Set the target angle list, in radians. */
	AL::ALValue targetAngles;
	targetAngles.arraySetSize(10);
	//
	targetAngles[0] = AL::ALValue::array(0.0f, 0.3f, 0.0f); //left elbowyaw
	targetAngles[1] = AL::ALValue::array(0.0f, -0.3f, 0.0f); // right elbow yaw
	targetAngles[2] = AL::ALValue::array(0.0f, -1.2f, 0.0f); //left elbow roll
	targetAngles[3] = AL::ALValue::array(0.0f, 1.2f, 0.0f); // right elbow roll
	targetAngles[4] = AL::ALValue::array(0.0f, -1.0f, 0.0f); // left shoulder roll
	targetAngles[5] = AL::ALValue::array(0.0f, -1.7f, 1.5f); // left sholder pitch
	targetAngles[6] = AL::ALValue::array(0.0f, 1.0f, 0.0f); // right shoulder roll
	targetAngles[7] = AL::ALValue::array(0.0f, -1.7f, 1.5f); // right shoulder pitch
	targetAngles[8] = AL::ALValue::array(0.0f, -1.5f, -0.7f); // Left wrist yaw
	targetAngles[9] = AL::ALValue::array(0.0f, 1.5f, 0.7f); // Right wrist yaw

															/** Set the corresponding time lists, in seconds. */
	AL::ALValue targetTimes;
	targetTimes.arraySetSize(10);
	targetTimes[0] = AL::ALValue::array(1.0f, 3.0f, 4.0f);
	targetTimes[1] = AL::ALValue::array(1.0f, 3.0f, 4.0f);
	targetTimes[2] = AL::ALValue::array(1.0f, 3.0f, 4.0f);
	targetTimes[3] = AL::ALValue::array(1.0f, 3.0f, 4.0f);
	targetTimes[4] = AL::ALValue::array(1.0f, 3.0f, 4.0f);
	targetTimes[5] = AL::ALValue::array(1.0f, 3.0f, 6.0f);
	targetTimes[6] = AL::ALValue::array(1.0f, 3.0f, 4.0f);
	targetTimes[7] = AL::ALValue::array(1.0f, 3.0f, 6.0f);
	targetTimes[8] = AL::ALValue::array(1.0f, 3.0f, 4.0f);
	targetTimes[9] = AL::ALValue::array(1.0f, 3.0f, 4.0f);
	/** Specify that the desired angles are absolute. */
	bool isAbsolute = true;

	/** Call the angle interpolation method. The joint will reach the
	* desired angles at the desired times.
	*/
	motionProxy.angleInterpolation(jointName, targetAngles, targetTimes, isAbsolute);
}

void Robot::handsOnHips() 
{
	AL::ALValue jointName = AL::ALValue::array("LElbowYaw", "RElbowYaw", "LElbowRoll", "RElbowRoll", "LShoulderRoll", "LShoulderPitch", "RShoulderRoll", "RShoulderPitch", "LWristYaw", "RWristYaw");
	/** Target stiffness. */
	AL::ALValue stiffness = 1.0f;
	/** Time (in seconds) to reach the target. */
	AL::ALValue time = 1.0f;
	/** Call the stiffness interpolation method. */
	std::lock_guard<std::mutex> lock(move_mtx);
	motionProxy.stiffnessInterpolation(jointName, stiffness, time);
	/*Hands on hips*/
	AL::ALValue targetAngles;
	targetAngles.arraySetSize(10);
	targetAngles[0] = AL::ALValue::array(0.0f, 0.3f, 0.0f); //left elbowyaw
	targetAngles[1] = AL::ALValue::array(0.0f, -0.3f, 0.0f); // right elbow yaw
	targetAngles[2] = AL::ALValue::array(0.0f, -1.3f, 0.0f); //left elbow roll
	targetAngles[3] = AL::ALValue::array(0.0f, 1.3f, 0.0f); // right elbow roll
	targetAngles[4] = AL::ALValue::array(0.0f, 0.95f, 0.0f); // left shoulder roll
	targetAngles[5] = AL::ALValue::array(0.0f, 1.3f, 1.5f); // left sholder pitch
	targetAngles[6] = AL::ALValue::array(0.0f, -0.95f, 0.0f); // right shoulder roll
	targetAngles[7] = AL::ALValue::array(0.0f, 1.3f, 1.5f); // right shoulder pitch
	targetAngles[8] = AL::ALValue::array(0.0f, -1.5f, 0.0f); // Left wrist yaw
	targetAngles[9] = AL::ALValue::array(0.0f, 1.5f, 0.0f); // Right wrist yaw

															/** Set the corresponding time lists, in seconds. */
	AL::ALValue targetTimes;
	targetTimes.arraySetSize(10);
	targetTimes[0] = AL::ALValue::array(1.0f, 4.0f, 6.0f);
	targetTimes[1] = AL::ALValue::array(1.0f, 4.0f, 6.0f);
	targetTimes[2] = AL::ALValue::array(1.0f, 4.0f, 6.0f);
	targetTimes[3] = AL::ALValue::array(1.0f, 4.0f, 6.0f);
	targetTimes[4] = AL::ALValue::array(1.0f, 4.0f, 6.0f);
	targetTimes[5] = AL::ALValue::array(1.0f, 4.0f, 6.0f);
	targetTimes[6] = AL::ALValue::array(1.0f, 4.0f, 6.0f);
	targetTimes[7] = AL::ALValue::array(1.0f, 4.0f, 6.0f);
	targetTimes[8] = AL::ALValue::array(1.0f, 4.0f, 6.0f);
	targetTimes[9] = AL::ALValue::array(1.0f, 4.0f, 6.0f);
	/** Specify that the desired angles are absolute. */
	bool isAbsolute = true;

	/** Call the angle interpolation method. The joint will reach the
	* desired angles at the desired times.
	*/
	motionProxy.angleInterpolation(jointName, targetAngles, targetTimes, isAbsolute);

}
void Robot::handsOnShoulders()
{
	AL::ALValue jointName = AL::ALValue::array("LElbowYaw", "RElbowYaw", "LElbowRoll", "RElbowRoll", "LShoulderRoll", "LShoulderPitch", "RShoulderRoll", "RShoulderPitch", "LWristYaw", "RWristYaw");
	/** Target stiffness. */
	AL::ALValue stiffness = 1.0f;
	/** Time (in seconds) to reach the target. */
	AL::ALValue time = 1.0f;
	/** Call the stiffness interpolation method. */
	std::lock_guard<std::mutex> lock(move_mtx);
	motionProxy.stiffnessInterpolation(jointName, stiffness, time);
	/** Hands on head */
	/** Set the target angle list, in radians. */
	AL::ALValue targetAngles;
	targetAngles.arraySetSize(10);
	targetAngles[0] = AL::ALValue::array(0.0f, 0.0f, 0.0f); //left elbow yaw
	targetAngles[1] = AL::ALValue::array(0.0f, 0.0f, 0.0f); // right elbow yaw
	targetAngles[2] = AL::ALValue::array(0.0f, -2.0f, 0.0f); //left elbow roll
	targetAngles[3] = AL::ALValue::array(0.0f, 2.0f, 0.0f); // right elbow roll
	targetAngles[4] = AL::ALValue::array(0.0f, 0.2f, 0.0f); // left shoulder roll
	targetAngles[5] = AL::ALValue::array(0.0f, 0.0f, 1.5f); // left sholder pitch
	targetAngles[6] = AL::ALValue::array(0.0f, -0.2f, 0.0f); // right shoulder roll
	targetAngles[7] = AL::ALValue::array(0.0f, 0.0f, 1.5f); // right shoulder pitch
	targetAngles[8] = AL::ALValue::array(0.0f, 0.5f, 0.0f); // Left wrist yaw
	targetAngles[9] = AL::ALValue::array(0.0f, 0.5f, 0.0f); // Right wrist yaw

															/** Set the corresponding time lists, in seconds. */
	AL::ALValue targetTimes;
	targetTimes.arraySetSize(10);
	targetTimes[0] = AL::ALValue::array(2.5f, 6.0f, 9.0f);
	targetTimes[1] = AL::ALValue::array(2.5f, 6.0f, 9.0f);
	targetTimes[2] = AL::ALValue::array(2.5f, 6.0f, 9.0f);
	targetTimes[3] = AL::ALValue::array(2.5f, 6.0f, 9.0f);
	targetTimes[4] = AL::ALValue::array(2.5f, 6.0f, 9.0f);
	targetTimes[5] = AL::ALValue::array(2.5f, 6.0f, 9.0f);
	targetTimes[6] = AL::ALValue::array(2.5f, 6.0f, 9.0f);
	targetTimes[7] = AL::ALValue::array(2.5f, 6.0f, 9.0f);
	targetTimes[8] = AL::ALValue::array(2.5f, 6.0f, 9.0f);
	targetTimes[9] = AL::ALValue::array(2.5f, 6.0f, 9.0f);
	/** Specify that the desired angles are absolute. */
	bool isAbsolute = true;

	/** Call the angle interpolation method. The joint will reach the
	* desired angles at the desired times.
	*/
	motionProxy.angleInterpolation(jointName, targetAngles, targetTimes, isAbsolute);

}
void Robot::squat()
{
	AL::ALValue jointName = AL::ALValue::array("RHipPitch", "LHipPitch", "RKneePitch", "LKneePitch", "LAnklePitch", "LAnkleRoll", "RAnklePitch", "RAnkleRoll", "LShoulderPitch", "RShoulderPitch");
	/** Target stiffness. */
	AL::ALValue stiffness = 1.0f;
	/** Time (in seconds) to reach the target. */
	AL::ALValue time = 1.0f;
	/** Call the stiffness interpolation method. */
	std::lock_guard<std::mutex> lock(move_mtx);
	motionProxy.stiffnessInterpolation(jointName, stiffness, time);
	/** Squat */
	/** Set the target angle list, in radians. */
	AL::ALValue targetAngles;
	targetAngles.arraySetSize(10);
	targetAngles[0] = AL::ALValue::array(0.0f, -1.0f, 0.0f); //Right Hip Pitch
	targetAngles[1] = AL::ALValue::array(0.0f, -1.0f, 0.0f); //Left Hip Pitch
	targetAngles[2] = AL::ALValue::array(0.0f, 1.5f, 0.0f);  //Right Knee Pitch
	targetAngles[3] = AL::ALValue::array(0.0f, 1.5f, 0.0f);  //Left Knee Pitch
	targetAngles[4] = AL::ALValue::array(0.0f, -0.5f, 0.0f); //Left Ankle Pitch
	targetAngles[5] = AL::ALValue::array(0.0f, 0.0f, 0.0f);  //Left Ankle Roll
	targetAngles[6] = AL::ALValue::array(0.0f, -0.5f, 0.0f); //Right Ankle Pitch
	targetAngles[7] = AL::ALValue::array(0.0f, 0.0f, 0.0f); //Right Ankle Roll
	targetAngles[8] = AL::ALValue::array(0.0f, 0.0f, 1.5f);    //Left Shoulder Pitch
	targetAngles[9] = AL::ALValue::array(0.0f, 0.0f, 1.5f);    //Right Shoulder Pitch




															   /** Set the corresponding time lists, in seconds. */
	AL::ALValue targetTimes;
	targetTimes.arraySetSize(10);
	targetTimes[0] = AL::ALValue::array(2.0f, 5.0f, 8.0f);
	targetTimes[1] = AL::ALValue::array(2.0f, 5.0f, 8.0f);
	targetTimes[2] = AL::ALValue::array(2.0f, 5.0f, 8.0f);
	targetTimes[3] = AL::ALValue::array(2.0f, 5.0f, 8.0f);
	targetTimes[4] = AL::ALValue::array(2.0f, 5.0f, 8.0f);
	targetTimes[5] = AL::ALValue::array(2.0f, 5.0f, 8.0f);
	targetTimes[6] = AL::ALValue::array(2.0f, 5.0f, 8.0f);
	targetTimes[7] = AL::ALValue::array(2.0f, 5.0f, 8.0f);
	targetTimes[8] = AL::ALValue::array(2.0f, 5.0f, 8.0f);
	targetTimes[9] = AL::ALValue::array(2.0f, 5.0f, 8.0f);

	/** Specify that the desired angles are absolute. */
	bool isAbsolute = true;

	/** Call the angle interpolation method. The joint will reach the
	* desired angles at the desired times.
	*/
	motionProxy.angleInterpolation(jointName, targetAngles, targetTimes, isAbsolute);
}

void Robot::waveLeftHand()
{
	AL::ALValue jointName = AL::ALValue::array("LElbowYaw", "LElbowRoll", "LWristYaw", "LShoulderRoll", "LShoulderPitch");
	/** Target stiffness. */
	AL::ALValue stiffness = 1.0f;
	/** Time (in seconds) to reach the target. */
	AL::ALValue time = 1.0f;
	/** Call the stiffness interpolation method. */
	std::lock_guard<std::mutex> lock(move_mtx);
	motionProxy.stiffnessInterpolation(jointName, stiffness, time);
	/** Squat */
	/** Set the target angle list, in radians. */
	AL::ALValue targetAngles;
	targetAngles.arraySetSize(5);
	targetAngles[0] = AL::ALValue::array(-6.0f, -1.0f, -6.0f, 0.0f); //Left Elbow Yaw
	targetAngles[1] = AL::ALValue::array(-3.0f, -3.0f, -3.0f, 0.0f);  //Left Elbow Roll
	targetAngles[2] = AL::ALValue::array(1.0f, 1.0f, 1.0f, 0.0f); 		//Left Wrist Yaw
	targetAngles[3] = AL::ALValue::array(0.0f, 0.0f, 0.0f, 0.0f);      //Left Shoulder Roll
	targetAngles[4] = AL::ALValue::array(0.0f, 0.0f, 0.0f, 1.5f);      //Left Shoulder Pitch



																	   /** Set the corresponding time lists, in seconds. */
	AL::ALValue targetTimes;
	targetTimes.arraySetSize(6);
	targetTimes[0] = AL::ALValue::array(3.0f, 4.0f, 5.0f, 6.0f);
	targetTimes[1] = AL::ALValue::array(3.0f, 4.0f, 5.0f, 6.0f);
	targetTimes[2] = AL::ALValue::array(3.0f, 4.0f, 5.0f, 6.0f);
	targetTimes[3] = AL::ALValue::array(3.0f, 4.0f, 5.0f, 6.0f);
	targetTimes[4] = AL::ALValue::array(3.0f, 4.0f, 5.0f, 6.0f);
	/** Specify that the desired angles are absolute. */
	bool isAbsolute = true;

	/** Call the angle interpolation method. The joint will reach the
	* desired angles at the desired times.
	*/
	motionProxy.angleInterpolation(jointName, targetAngles, targetTimes, isAbsolute);
}
void Robot::waveRightHand()
{
	AL::ALValue jointName = AL::ALValue::array("RElbowYaw", "RElbowRoll", "RWristYaw", "RShoulderRoll", "RShoulderPitch");
	/** Target stiffness. */
	AL::ALValue stiffness = 1.0f;
	/** Time (in seconds) to reach the target. */
	AL::ALValue time = 1.0f;
	/** Call the stiffness interpolation method. */
	std::lock_guard<std::mutex> lock(move_mtx);
	motionProxy.stiffnessInterpolation(jointName, stiffness, time);
	/** Squat */
	/** Set the target angle list, in radians. */
	AL::ALValue targetAngles;
	targetAngles.arraySetSize(5);
	targetAngles[0] = AL::ALValue::array(6.0f, 1.0f, 6.0f, 0.0f);   //Right Elbow Yaw
	targetAngles[1] = AL::ALValue::array(3.0f, 3.0f, 3.0f, 0.0f);   //Right Elbow Yaw
	targetAngles[2] = AL::ALValue::array(-1.0f, -1.0f, -1.0f, 0.0f); //Right Wrist Yaw
	targetAngles[3] = AL::ALValue::array(0.0f, 0.0f, 0.0f, 0.0f);    //Right Shoulder Roll
	targetAngles[4] = AL::ALValue::array(0.0f, 0.0f, 0.0f, 1.5f);    //Right Shoulder Pitch


																	 /** Set the corresponding time lists, in seconds. */
	AL::ALValue targetTimes;
	targetTimes.arraySetSize(5);
	targetTimes[0] = AL::ALValue::array(3.0f, 4.0f, 5.0f, 6.0f);
	targetTimes[1] = AL::ALValue::array(3.0f, 4.0f, 5.0f, 6.0f);
	targetTimes[2] = AL::ALValue::array(3.0f, 4.0f, 5.0f, 6.0f);
	targetTimes[3] = AL::ALValue::array(3.0f, 4.0f, 5.0f, 6.0f);
	targetTimes[4] = AL::ALValue::array(3.0f, 4.0f, 5.0f, 6.0f);

	/** Specify that the desired angles are absolute. */
	bool isAbsolute = true;

	/** Call the angle interpolation method. The joint will reach the
	* desired angles at the desired times.
	*/
	motionProxy.angleInterpolation(jointName, targetAngles, targetTimes, isAbsolute);
}


//void Robot::raiseOneLeg()
//{
//	AL::ALValue jointName = AL::ALValue::array("RHipPitch", "RKneePitch", "LAnklePitch", "LAnkleRoll", "RAnklePitch", "RAnkleRoll", "LHipPitch", "LHipRoll", "LKneePitch");
//	/** Target stiffness. */
//	AL::ALValue stiffness = 1.0f;
//	/** Time (in seconds) to reach the target. */
//	AL::ALValue time = 1.0f;
//	/** Call the stiffness interpolation method. */
//	std::lock_guard<std::mutex> lock(move_mtx);
//	motionProxy.stiffnessInterpolation(jointName, stiffness, time);
//	/** Squat */
//	/** Set the target angle list, in radians. */
//	AL::ALValue targetAngles;
//	targetAngles.arraySetSize(9);
//	targetAngles[0] = AL::ALValue::array(0.0f, -1.0f, 0.0f); //Right Hip Pitch
//	targetAngles[1] = AL::ALValue::array(0.0f, 1.0f, 0.0f); // Right Knee Pitch
//	targetAngles[2] = AL::ALValue::array(0.0f, 0.0f, 0.0f); // Left Ankle Pitch
//	targetAngles[3] = AL::ALValue::array(0.0f, 0.2f, 0.0f); // Left Ankle Roll
//	targetAngles[4] = AL::ALValue::array(0.0f, 0.0f, 0.0f); // Right Ankle Pitch
//	targetAngles[5] = AL::ALValue::array(0.0f, 0.0f, 0.0f); // Right Ankle Roll
//	targetAngles[6] = AL::ALValue::array(0.0f, 0.0f, 0.0f); // Left Hip Pitch
//	targetAngles[7] = AL::ALValue::array(0.0f, 0.2f, 0.0f); // Left Hip Roll
//	targetAngles[8] = AL::ALValue::array(0.0f, 0.0f, 0.0f); // Left Knee Pitch
//
//
//
//															/** Set the corresponding time lists, in seconds. */
//	AL::ALValue targetTimes;
//	targetTimes.arraySetSize(9);
//	targetTimes[0] = AL::ALValue::array(1.0f, 3.0f, 4.0f);
//	targetTimes[1] = AL::ALValue::array(1.0f, 3.0f, 4.0f);
//	targetTimes[2] = AL::ALValue::array(1.0f, 3.0f, 4.0f);
//	targetTimes[3] = AL::ALValue::array(1.0f, 3.0f, 4.0f);
//	targetTimes[4] = AL::ALValue::array(1.0f, 3.0f, 4.0f);
//	targetTimes[5] = AL::ALValue::array(1.0f, 3.0f, 4.0f);
//	targetTimes[6] = AL::ALValue::array(1.0f, 3.0f, 4.0f);
//	targetTimes[7] = AL::ALValue::array(1.0f, 3.0f, 4.0f);
//	targetTimes[8] = AL::ALValue::array(1.0f, 3.0f, 4.0f);
//
//
//	/** Specify that the desired angles are absolute. */
//	bool isAbsolute = true;
//
//	/** Call the angle interpolation method. The joint will reach the
//	* desired angles at the desired times.
//	*/
//	motionProxy.angleInterpolation(jointName, targetAngles, targetTimes, isAbsolute);
//
//}



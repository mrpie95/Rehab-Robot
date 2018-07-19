#pragma once
#include <OpenNI.h>
#include <NiTE.h>
#include <vector>

class KinectStream
{
private:
	openni::VideoFrameRef depthFrame;
	openni::VideoFrameRef colourFrame;
	openni::VideoStream& colourStream;
	openni::VideoStream& depthStream;
	openni::Device& kinect;

	openni::VideoStream** streams;
	float colors[4][3] = { { 1, 0, 0 },{ 0, 1, 0 },{ 0, 0, 1 },{ 1, 1, 1 } };

	int colorTextureMapX;
	int colorTextureMapY;
	openni::RGB888Pixel* colorTextureMap;
	openni::RGB888Pixel* depthTextureMap;

	int streamWidth;
	int streamHeight;

	nite::UserTracker& tracker;
	nite::UserTrackerFrameRef trackerFrame;
	nite::UserData user;
	nite::SkeletonState userSkeltonState = nite::SKELETON_NONE;

	void DrawLimb(nite::UserTracker* pUserTracker, const nite::SkeletonJoint& joint1, const nite::SkeletonJoint& joint2, int color);
	void DrawSkeleton(nite::UserTracker* pUserTracker, const nite::UserData& userData);
	void updateUserState(const nite::UserData& user, uint64_t delta);
public:
	KinectStream(openni::Device& device, openni::VideoStream& depthStream, openni::VideoStream& colourStream, nite::UserTracker& tracker);
	~KinectStream();

	void init();
	void run();
	void runTracker();

	void drawDepthFrame();
	void drawColorFrame();


};


#pragma once
#include <OpenNI.h>
#include <NiTE.h>

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
	

	void DrawLimb(nite::UserTracker* pUserTracker, const nite::SkeletonJoint& joint1, const nite::SkeletonJoint& joint2, int color);

public:
	KinectStream(openni::Device& device, openni::VideoStream& depthStream, openni::VideoStream& colourStream);
	~KinectStream();

	void init();
	void run();

	void drawDepthFrame();
	void drawColorFrame();


};


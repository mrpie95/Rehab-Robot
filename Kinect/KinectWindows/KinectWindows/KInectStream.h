#pragma once
#include <OpenNI.h>


class KinectStream
{
private:
	openni::VideoFrameRef depthFrame;
	openni::VideoFrameRef colourFrame;
	openni::VideoStream& colourStream;
	openni::VideoStream& depthStream;
	openni::Device& kinect;

	

	int textureMapX;
	int textureMapY;
	openni::RGB888Pixel* textureMap;

public:
	KinectStream(openni::Device& device, openni::VideoStream& depthStream, openni::VideoStream& colourStream);
	~KinectStream();

	void init();
	void run();
};


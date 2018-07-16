#include "Window.h"
#include <iostream>
#include <OpenNI.h>
#include "KInectStream.h"

#define log(x) std::cout << x << std::endl;


int main(int argc, char** argv)
{
	Window colorWindow;
	Window depthWindow;
	colorWindow.init();
	depthWindow.init();

	if (openni::OpenNI::initialize() != openni::Status::STATUS_OK)
	{
		log(openni::OpenNI::getExtendedError());
	}
	else
	{
		log("OpenNI succefully initilized");
	}

	
	openni::Array<openni::DeviceInfo> devices;
	openni::OpenNI::enumerateDevices(&devices);
	for (int i = 0; i < devices.getSize(); i++)
	{
		log(devices[i].getName());
	}

	openni::Device kinect;
	openni::VideoStream depth, color;
	const char* deviceuri = openni::ANY_DEVICE;
	openni::Status kinectStatus = kinect.open(deviceuri);

	if (kinectStatus != openni::Status::STATUS_OK)
	{
		log(openni::OpenNI::getExtendedError());
	}
	else
	{
		log("Kinect URI successfully opened");
	}

	kinectStatus = depth.create(kinect, openni::SENSOR_DEPTH);
	
	if (kinectStatus == openni::Status::STATUS_OK)
	{
		kinectStatus = depth.start();
		if (kinectStatus != openni::Status::STATUS_OK)
		{
			log(openni::OpenNI::getExtendedError());
			depth.destroy();
		}
	}
	else
	{
		log(openni::OpenNI::getExtendedError());
	}

	kinectStatus = color.create(kinect, openni::SENSOR_COLOR);

	if (kinectStatus == openni::Status::STATUS_OK)
	{
		kinectStatus = color.start();
		if (kinectStatus != openni::Status::STATUS_OK)
		{
			log(openni::OpenNI::getExtendedError());
			color.destroy();
		}
	}
	else
	{
		log(openni::OpenNI::getExtendedError());
	}

	KinectStream kinectStream(kinect, depth, color);
	kinectStream.init();

	SDL_Event e;
	for (;;) {
		SDL_PollEvent(&e);
		if (e.window.event == SDL_WINDOWEVENT_CLOSE) {
			break;
		}
		kinectStream.run();
		colorWindow.clearFlipBuffers();
		depthWindow.clearFlipBuffers();
	}
	

	return 0;
}
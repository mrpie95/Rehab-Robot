#include "Window.h"
#include <iostream>
#include <OpenNI.h>

#define log(x) std::cout << x << std::endl;


int main(int argc, char** argv)
{
	Window w;
	w.init();

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

	SDL_Event e;

	for (;;) {
		SDL_PollEvent(&e);
		if (e.type == SDL_QUIT) {
			break;
		}
		w.draw();
	}
	

	return 0;
}
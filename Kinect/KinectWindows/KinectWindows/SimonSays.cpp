#include "SimonSays.h"



SimonSays::SimonSays()
{
}


SimonSays::~SimonSays()
{
}

void SimonSays::init()
{
	camera.init();
	skeletonWindow.init();

	if (openni::OpenNI::initialize() != openni::Status::STATUS_OK)
	{
		log(openni::OpenNI::getExtendedError());
	}
	else
	{
		log("OpenNI succefully initilized");
	}

	nite::NiTE::initialize();


	openni::Array<openni::DeviceInfo> devices;
	openni::OpenNI::enumerateDevices(&devices);
	for (int i = 0; i < devices.getSize(); i++)
	{
		log(devices[i].getName());
	}

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

	if (tracker.create(&kinect) != openni::Status::STATUS_OK)
	{
		log("failed to create traker");
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
	
	kinectStream = new KinectStream(kinect, depth, color, tracker);
	kinectStream->init();


	gestures.push_back(new HandsOnHead());
	gestures.push_back(new HandsOnHips());
}

void SimonSays::run()
{
	SDL_Event e;

	//TODO:: this crashes here when you close window
	for (;;) {
		SDL_PollEvent(&e);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		kinectStream->run();
		kinectStream->drawColorFrame();
		kinectStream->runTracker();
		camera.FlipBuffers();


		SDL_GL_MakeCurrent(skeletonWindow.getWindow(), skeletonWindow.getOpenGLContext());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		kinectStream->runTracker();
		skeletonWindow.FlipBuffers();

		SDL_GL_MakeCurrent(camera.getWindow(), camera.getOpenGLContext());

		if (kinectStream->getUserSkeleton())
		{
			for (auto g: gestures)
			{
				if (g->checkForGesture(*kinectStream->getUserSkeleton()))
				{
					log(g->getName());
				}
			}
		}

		if (e.window.event == SDL_WINDOWEVENT_CLOSE) {
			break;
		}
	}
	nite::NiTE::shutdown();
	openni::OpenNI::shutdown();
}
#include "SimonSays.h"



SimonSays::SimonSays()
{
}


SimonSays::~SimonSays()
{
}

int SimonSays::getRandomNumber()
{
	srand(time(NULL));
	return rand() % 3;	
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
	gestures.push_back(new HandsOnShoulders());
}

void SimonSays::run()
{
	SDL_Event e;
	bool playingGame = true;
	int num = getRandomNumber();
	std::string action;

	auto start = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed;

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
		
		elapsed = std::chrono::high_resolution_clock::now() - start;
		
		//log(elapsed.count());

		if (playingGame)
		{
			switch (num)
			{
			case 0:
				log("Simon says put your hands on your head");
				action = "Head";
				break;
			case 1:
				log("Simon says put your hands on your hips");
				action = "Hips";
				break;
			case 2:
				log("Simon says put your hand on your shoulders");
				action = "Shoulders";
				break;
			default:
				log("Error with rng");
			}

			if (kinectStream->getUserSkeleton())
			{
				for (auto g : gestures)
				{
					if (g->checkForGesture(*kinectStream->getUserSkeleton()))
					{
						log(g->getName());

						if (action == g->getName() && elapsed.count() > 5)
						{
							log("Correct action");
							start = std::chrono::high_resolution_clock::now();
						}
						else
						{
							log("Incorrect action");
							start = std::chrono::high_resolution_clock::now();
						}
					}
				}
			}


			playingGame = false;
		}


		

		if (e.window.event == SDL_WINDOWEVENT_CLOSE) {
			break;
		}
	}
	nite::NiTE::shutdown();
	openni::OpenNI::shutdown();
}
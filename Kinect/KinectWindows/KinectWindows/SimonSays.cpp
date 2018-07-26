#include "SimonSays.h"
#include "WaveGesture.h"
#include "StandOnOneLeg.h"

#define GESTURE_DEBUG 0

#define SIMON_NOT_SAY_CHANCE 0.2f

SimonSays::SimonSays()
{
	camera = new Window("Camera", 800, 600, 160, 200);
	skeletonWindow = new Window("Skeleton", 800,600, 960, 200);
}


SimonSays::~SimonSays()
{
}

int SimonSays::getRandomNumber(int max)
{
	
	return rand() % max;
}


//TODO: better alg needed, too random
bool SimonSays::roll()
{
	unsigned int lowerbound = RAND_MAX * SIMON_NOT_SAY_CHANCE;
	unsigned int roll = rand();

	if (roll >= lowerbound)
		return false;
	else
		return true; //topdecked
}

void SimonSays::init()
{
	srand(time(NULL));
	camera->init();
	skeletonWindow->init();

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
	gestures.push_back(new WaveGesture(Hand::rightHand));
	gestures.push_back(new WaveGesture(Hand::leftHand));
	gestures.push_back(new StandOnOneLeg());
}

void SimonSays::run()
{
	SDL_Event e;
	bool playingGame = true;
	int num = 0;
	std::string action;

	auto start = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed;
	bool simonSays;
	bool first = true;
	GestureInterface* prevGesture = nullptr;

	//TODO:: it sometimes crashes here
	for (;;) {
		SDL_PollEvent(&e); 
		kinectStream->run();
		kinectStream->drawColorFrame();
		kinectStream->runTracker();
		camera->FlipBuffers();

		SDL_GL_MakeCurrent(skeletonWindow->getWindow(), skeletonWindow->getOpenGLContext());
		kinectStream->runTracker();
		skeletonWindow->FlipBuffers();

		SDL_GL_MakeCurrent(camera->getWindow(), camera->getOpenGLContext());
		
	
#if GESTURE_DEBUG
		if (kinectStream->getUserSkeleton())
		{
			for (auto g : gestures)
			{
				g->updateSkeleton(*kinectStream->getUserSkeleton());
				if (g->checkForGesture())
				{
					log(g->getName());
				}
			}
		}
#else 
		//simon says starts here
		elapsed = std::chrono::high_resolution_clock::now() - start;

		if (kinectStream->getUserSkeleton() && !kinectStream->isUserLost())
		{
			int gestureCount = gestures.size();
	

			if (!gestureSelected && elapsed.count() > 1.0f)
			{
				simonSays = !roll();
				int randnum = getRandomNumber(gestureCount);
				gestureSelected = gestures[randnum];

				while (prevGesture == gestureSelected)
				{
					gestureSelected = gestures[randnum];
					randnum = getRandomNumber(gestureCount);
				}

				prevGesture = gestureSelected;
				start = std::chrono::high_resolution_clock::now();
			}
			else if (gestureSelected)
			{
				gestureSelected->updateSkeleton(*kinectStream->getUserSkeleton());

				if (simonSays)
				{
					if (first)
						std::cout << "Simon says " << gestureSelected->getName() << std::endl;
					first = false;


					if (gestureSelected->checkForGesture())
					{
						first = true;
						gestureSelected = nullptr;
						start = std::chrono::high_resolution_clock::now();
					}

					//failed to complete gesture in time
					if (elapsed.count() > 5.0f)
					{
						log("failed");
						first = true;
						gestureSelected = nullptr;
						start = std::chrono::high_resolution_clock::now();
					}
				}
				else 
				{
					if (first)
						std::cout << gestureSelected->getName() << std::endl;
					first = false;


					//game end condition
					if (gestureSelected->checkForGesture())
					{
						log("You lose");
						first = true;
						gestureSelected = nullptr;
						start = std::chrono::high_resolution_clock::now();
					}

					//new gesture
					if (elapsed.count() > 2.0f)
					{
						first = true;
						gestureSelected = nullptr;
						start = std::chrono::high_resolution_clock::now();
					}
				}
			}
		}
#endif

		if (e.window.event == SDL_WINDOWEVENT_CLOSE) {
			break;
		}
	}
	nite::NiTE::shutdown();
	openni::OpenNI::shutdown();
}
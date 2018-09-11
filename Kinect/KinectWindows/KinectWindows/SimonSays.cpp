#include "SimonSays.h"
#include "WaveGesture.h"
#include "StandOnOneLeg.h"
#include "HandsOutFront.h"
#include "SquatGesture.h"
#include <thread>
#define GESTURE_DEBUG 1

#define SIMON_NOT_SAY_CHANCE 0.2f

SimonSays::SimonSays()
{

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
	kinectStream = new KinectStream();
	kinectStream->init();


	user.initGestureChecker();
}


void SimonSays::run()
{

	Gesture* g = new SquatGesture();
	SDL_Event e;
	bool playingGame = true;
	int num = 0;
	std::string action;

	auto start = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed;
	bool simonSays;
	bool first = true;
	Gesture* prevGesture = nullptr;

	//TODO:: it sometimes crashes here
	for (;;) {
		SDL_PollEvent(&e); 
		elapsed = std::chrono::high_resolution_clock::now() - start;
	
		kinectStream->run();
		
		kinectStream->drawString(std::to_string((int)(1 / elapsed.count())), 0, 0, 0, 32, 0xffff00);
		start = std::chrono::high_resolution_clock::now();
	
#if GESTURE_DEBUG
		if (kinectStream->getUserSkeleton())
		{
			user.update(*kinectStream->getUserSkeleton());
		}

		kinectStream->drawString(user.print().c_str(), 0,930, 0, 32, 0);		
		kinectStream->BufferSwap();
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
					{
						std::string output = "Simon says ";
						output = output + gestureSelected->getName();
						log(output);
					}
						
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
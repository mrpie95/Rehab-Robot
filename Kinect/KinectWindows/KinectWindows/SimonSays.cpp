#include "SimonSays.h"
#include "WaveGesture.h"
#include "StandOnOneLeg.h"
#include "HandsOutFront.h"
#include "SquatGesture.h"
#include <thread>
#define GESTURE_DEBUG 0

#define SIMON_NOT_SAY_CHANCE 0.3f

SimonSays::SimonSays()
{

}


SimonSays::~SimonSays()
{
}

int SimonSays::getRandomNumber(int max)
{
	srand(time(NULL));
	return rand() % max;
}


//TODO: better alg needed, too random
bool SimonSays::roll()
{
	
	unsigned int lowerbound = RAND_MAX * SIMON_NOT_SAY_CHANCE;
	unsigned int roll = rand();
	srand(time(NULL));
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
	gestureSelected = nullptr;
	int gestureCount = user.getGestures().size();
	int score = 0;
	//TODO:: it sometimes crashes here
	for (;;) {
		elapsed = std::chrono::high_resolution_clock::now() - start;
		start = std::chrono::high_resolution_clock::now();
		int frameRate = 1.0f / elapsed.count();
		SDL_PollEvent(&e); 
	
		kinectStream->run();
		
	
		kinectStream->drawString(std::to_string(frameRate), 0, 0, 0, 32, 0xffff00);
		kinectStream->drawString(user.print().c_str(), 0, 930, 0, 32, 0);
		kinectStream->BufferSwap();
	
		if (kinectStream->getUserSkeleton())
		{
			user.update(*kinectStream->getUserSkeleton());
		}

		if (e.window.event == SDL_WINDOWEVENT_CLOSE) {
			break;
		}
	}
}
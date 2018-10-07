#include "SimonSays.h"
#include "WaveGesture.h"
#include "StandOnOneLeg.h"
#include "HandsOutFront.h"
#include "SquatGesture.h"
#include <thread>
#define GESTURE_DEBUG 0

#define SIMON_NOT_SAY_CHANCE 0.3f

SimonSays::SimonSays(): nao("0.0.0.0")
{

}

SimonSays::SimonSays(const char* ip): nao(ip)
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
	nao.stand();
	nao.say("Lets begin");
	nao.say("If you like to begin cross your arms. If not instructions will play");

	auto start = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed;
	elapsed = std::chrono::high_resolution_clock::now() - start;

	while (elapsed.count() < 5.0f)
	{
		kinectStream->run();
		kinectStream->BufferSwap();
		if (kinectStream->getUserSkeleton())
		{
			return;
		}

		elapsed = std::chrono::high_resolution_clock::now() - start;
	}

	nao.say("Simon says is a game where i tell you what you must do.");
		
	nao.say("However, you must only obey commands that begin with the words Simon Says.");
		
	nao.say("If the word Simon isn't spoken, you mush not do the action."); 
		
	
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
		SDL_PollEvent(&e); 
	
		kinectStream->run();
		
		kinectStream->drawString(std::to_string((int)(elapsed.count())), 0, 0, 0, 32, 0xffff00);

		kinectStream->drawString(user.print().c_str(), 0, 930, 0, 32, 0);
		kinectStream->BufferSwap();
	
#if GESTURE_DEBUG
		if (kinectStream->getUserSkeleton())
		{
			user.update(*kinectStream->getUserSkeleton());
		}

		
#else 
		//simon says starts here
		elapsed = std::chrono::high_resolution_clock::now() - start;

		if (kinectStream->getUserSkeleton() && !kinectStream->isPrimeUserLost())
		{
			user.update(*kinectStream->getUserSkeleton());
			
			if (score == 5)
			{
				nao.dance();
				std::async(std::launch::async, &Robot::say, nao, "Well done, you win. Would you like to play again.");
				score = 0;
			}
	

			if (!gestureSelected && elapsed.count() > 6.0f)
			{
				simonSays = !roll();
				int randnum = getRandomNumber(gestureCount);
				gestureSelected = user.getGestures()[randnum];
				while (prevGesture == gestureSelected)
				{
					gestureSelected = user.getGestures()[randnum];
					randnum = getRandomNumber(gestureCount);
				}

				prevGesture = gestureSelected;
				start = std::chrono::high_resolution_clock::now();
				first = true;
			}
			else if (gestureSelected)
			{
				if (simonSays)
				{
					if (first)
					{
						std::string output = "Simon says ";
						output = output + gestureSelected->getName();
						

						if (!strcmp(gestureSelected->getName(),"Hands on hips"))
						{
							std::async(std::launch::async, &Robot::handsOnHips, nao);
						}
						else if (!strcmp(gestureSelected->getName(), "Hands on head"))
						{
							std::async(std::launch::async, &Robot::handsOnHead, nao);
						}
						else if (!strcmp(gestureSelected->getName(), "Hands Out Front"))
						{
							std::async(std::launch::async, &Robot::handsOutFront, nao);
						} 
						else if (!strcmp(gestureSelected->getName(), "Hands on shoulders"))
						{
							std::async(std::launch::async, &Robot::handsOnShoulders, nao);
						}
						else if (!strcmp(gestureSelected->getName(), "Wave left hand"))
						{
							std::async(std::launch::async, &Robot::waveLeftHand, nao);
						}
						else if (!strcmp(gestureSelected->getName(), "Wave right hand"))
						{
							std::async(std::launch::async, &Robot::waveRightHand, nao);
						}
						else if (!strcmp(gestureSelected->getName(), "Squat"))
						{
							std::async(std::launch::async, &Robot::squat, nao);
						}
						else if (!strcmp(gestureSelected->getName(), "Stand on one Leg"))
						{
							//std::async(std::launch::async, &Robot::standOnOneLeg, nao);
						}
						
							
						std::async(std::launch::async, &Robot::say, nao, output.c_str());
						log(output);
						first = false;
					}
						
					


					if (gestureSelected == user.getLastGesture())
					{
						std::async(std::launch::async, &Robot::say, nao , "Correct");
						first = true;
						gestureSelected = nullptr;
						score++;
						start = std::chrono::high_resolution_clock::now();
					}

					//failed to complete gesture in time
					if (elapsed.count() > 10.0f)
					{
						//log("failed");
						first = true;
						gestureSelected = nullptr;
						start = std::chrono::high_resolution_clock::now();
					}
				}
				else 
				{
					if (first)
					{
						std::async(std::launch::async, &Robot::say, nao, gestureSelected->getName());
					}


					first = false;


					//game end condition
					if (gestureSelected == user.getLastGesture())
					{
						std::async(std::launch::async, &Robot::say, nao, "You lose");
						first = true;
						gestureSelected = nullptr;
						start = std::chrono::high_resolution_clock::now();
					}

					//new gesture
					if (elapsed.count() > 4.0f)
					{
						first = true;
						gestureSelected = nullptr;
						start = std::chrono::high_resolution_clock::now();
					}
				}
			}
		}
#endif

		if (kinectStream->isPrimeUserLost() && elapsed.count() > 3)
		{
			std::async(std::launch::async, &Robot::say, nao, "Oh, No, I can't see you.");
			start = std::chrono::high_resolution_clock::now();
		}

		if (e.window.event == SDL_WINDOWEVENT_CLOSE) {
			break;
		}
	}
	nite::NiTE::shutdown();
	openni::OpenNI::shutdown();
}
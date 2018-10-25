#include "SimonSays.h"
#include "WaveGesture.h"
#include "StandOnOneLeg.h"
#include "HandsOutFront.h"
#include "SquatGesture.h"
#include <thread>
#include "INIHandler.h"
#define GESTURE_DEBUG 0



SimonSays::SimonSays(): nao("0.0.0.0")
{

}

SimonSays::SimonSays(const char* ip): nao(ip)
{
}


SimonSays::~SimonSays()
{
	delete kinectStream;
}

int SimonSays::getRandomNumber(int max)
{
	srand(time(NULL));
	return rand() % max;
}


//TODO: better alg needed, too random
bool SimonSays::roll()
{
	float chance = INIHandler::getInstance().getValue<float>("fSimonNotSaysChance");
	unsigned int lowerbound = RAND_MAX * chance;
	unsigned int roll = rand();
	srand(time(NULL));
	if (roll >= lowerbound)
		return false;
	else
		return true; //topdecked
}

void SimonSays::init()
{
	srand(time(NULL));
	kinectStream = new KinectStream();
	kinectStream->init();
	user.initGestureChecker();
	nao.stand();
	nao.say(INIHandler::getInstance().getValue<std::string>("sStartUpMessage").c_str());
	nao.say(INIHandler::getInstance().getValue<std::string>("sQueryUserForInstructions").c_str());

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
	//std::async(std::launch::async, &Robot::idleAnimation, nao);
	nao.say("Simon says is a game where i tell you what you must do.");
		
	nao.say("However, you must only obey commands that begin with the words Simon Says.");
	//std::async(std::launch::async, &Robot::idleAnimation, nao);
	nao.say("If the word Simon isn't spoken, you mush not do the action."); 
}

void SimonSays::init(std::string gestures)
{
	srand(time(NULL));
	kinectStream = new KinectStream();
	kinectStream->init();
	user.initGestureChecker(gestures);
	nao.stand();
	nao.say(INIHandler::getInstance().getValue<std::string>("sStartUpMessage").c_str());
	nao.say(INIHandler::getInstance().getValue<std::string>("sQueryUserForInstructions").c_str());

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
	//std::async(std::launch::async, &Robot::idleAnimation, nao);
	nao.say("Simon says is a game where i tell you what you must do.");

	nao.say("However, you must only obey commands that begin with the words Simon Says.");

	nao.say("If the word Simon isn't spoken, you mush not do the action.");
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
	Gesture* prevGesture = nullptr;
	gestureSelected = nullptr;
	int gestureCount = user.getGestures().size();
	int score = 0;

	int ScoreToWin = INIHandler::getInstance().getValue<int>("iScoreToWin");
	float TimeToCompleteGestureIn = INIHandler::getInstance().getValue<float>("fTimeToCompleteGestureIn");
	float TimeToFailGestureIn = INIHandler::getInstance().getValue<float>("fTimeToFailGesturesIn");
	float TimeToSelectNextGestureIn = INIHandler::getInstance().getValue<float>("fTimeToSelectNextGesture");
	std::thread idleAnimationThread;
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
			
			if (score == ScoreToWin)
			{
				nao.dance();
				const char* winningMessage = INIHandler::getInstance().getValue<std::string>("sWinningMessag").c_str();
				std::async(std::launch::async, &Robot::say, nao, winningMessage);
				score = 0;
				//Would You like to play again??
			}
	

			if (!gestureSelected && (elapsed.count() > TimeToSelectNextGestureIn))
			{
				simonSays = !roll();
				log(simonSays);
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
						else if (!strcmp(gestureSelected->getName(), "Hands Out Front"))
						{
							std::async(std::launch::async, &Robot::handsOutFront, nao);
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
						int randomNum = getRandomNumber(INIHandler::getInstance().getValue<std::vector<std::string>>("svCorrrectGestureResponse").size()-1);
						std::string rightResponse = INIHandler::getInstance().getValue<std::vector<std::string>>("svCorrrectGestureResponse")[randomNum];

						//log(rightResponse);
						nao.say(rightResponse.c_str());
						first = true;
						gestureSelected = nullptr;
						score++;
						start = std::chrono::high_resolution_clock::now();
					}

					//failed to complete gesture in time
					if (elapsed.count() > TimeToCompleteGestureIn)
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
						int randomNum = getRandomNumber(INIHandler::getInstance().getValue<std::vector<std::string>>("svIncorrectGestureResponce").size()-1);
						std::string wrongResponce = INIHandler::getInstance().getValue<std::vector<std::string>>("svIncorrectGestureResponce")[randomNum];
						//log(wrongResponce);
						nao.say(wrongResponce.c_str());
						first = true;
						gestureSelected = nullptr;
						start = std::chrono::high_resolution_clock::now();
					}

					//new gesture
					if (elapsed.count() > TimeToFailGestureIn)
					{
						first = true;
						gestureSelected = nullptr;
						start = std::chrono::high_resolution_clock::now();
					}

				}
			}
		}
#endif


		/*if (kinectStream->isPrimeUserLost() && elapsed.count() > 4)
		{
			std::async(std::launch::async, &Robot::say, nao, "Oh, No, I can't see you.");
			std::async(std::launch::async, &Robot::idleAnimation, nao);
			start = std::chrono::high_resolution_clock::now();
		}*/


		if (e.window.event == SDL_WINDOWEVENT_CLOSE) {
			break;
		}


		if ((int)elapsed.count() % 4 == 0 && fmod(elapsed.count(), 4.0f) < 0.1)
		{
			//std::async(std::launch::async, &Robot::idleAnimation, nao);

		}
	}
}
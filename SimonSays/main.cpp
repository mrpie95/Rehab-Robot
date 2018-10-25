#include "Robot.h"
#include <chrono>
#include "SimonSays.h"
#include <exception>
#include "INIHandler.h"
#include <iostream>

#define PYTHON_ENTRY_POINTS 1


#if PYTHON_ENTRY_POINTS


/** PROGRAM EXIT CODES
*	0 - ok;
*	1 - OpenNI failed to initialise
*	2 - Failed to find any kinected devices
*	3 - Failed to open Kinect device
*	4 - Failed to create NiTE tracker
*	5 - Failed to open depth stream
*	6 - Failed to open colour stream
*	7 - Failed to load font file
**/



extern "C" __declspec(dllexport) int python_entry_init(const char* gestures, const char* ip)
{
	std::string input(gestures);
	SimonSays* game;
	game = new SimonSays(ip);
	game->init(input);
	game->run();
	
}
extern "C" __declspec(dllexport) int getErrorCode()
{		
	return 0;
}

#endif

int main(int argc, char** argv)
{
	
	SimonSays* game;
	game = new SimonSays("169.254.79.239");
	game->init();
	game->run();

	/*try
	{
		SimonSays game("169.254.79.239");
		game.init();
		game.run();
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}*/
	
	
	return 0;
}
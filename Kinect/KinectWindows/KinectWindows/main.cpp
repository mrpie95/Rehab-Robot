#include "Robot.h"
#include <chrono>
#include "SimonSays.h"

#include <exception>


extern "C" __declspec(dllexport) void simonSays()
{
	try
	{
		SimonSays game("169.254.79.239");
		game.init();
		game.run();
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
}

int main(int argc, char** argv)
{
	//Robot nao("169.254.79.239");
	//nao.stand();
	//nao.standOnOneLeg();


	try
	{
		SimonSays game("169.254.79.239");
		game.init();
		game.run();
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
	
	
	return 0;
}
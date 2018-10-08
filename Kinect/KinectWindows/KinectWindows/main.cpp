#include "SimonSays.h"
#include "INIHandler.h"
#define log(x) std::cout << x << '\n';


int main(int argc, char** argv)
{
	SimonSays game;
	game.init();
	game.run();
	return 0;
}
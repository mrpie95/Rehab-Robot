#include "SimonSays.h"
#include "INIHandler.h"
#define log(x) std::cout << x << '\n';


int main(int argc, char** argv)
{

	log(INIHandler::getInstance().getValue<int>("iScoreToWin"));
	log("TEst");
	std::cin.get();
	return 0;
}
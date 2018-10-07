#include "SimonSays.h"
#include "INIHandler.h"
#define log(x) std::cout << x << '\n';


int main(int argc, char** argv)
{

	auto temp = INIHandler::getInstance().getValue(std::vector<std::string>(), "svCorrrectGestureResponse");

	for (auto s: temp)
	{
		log(s);
	}

	/*try
	{
		SimonSays simon;
		simon.init();
		simon.run();
	}
	catch (...)
	{
		log("Yeah Nah");
		return 123456789;
	}*/
	log("TEst");
	std::cin.get();
	return 0;
}
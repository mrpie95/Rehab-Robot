#include "SimonSays.h"


#define log(x) std::cout << x << std::endl;


int main(int argc, char** argv)
{
	try
	{
		SimonSays simon;
		simon.init();
		simon.run();
	}
	catch (...)
	{
		log("Yeah Nah");
		return 123456789;
	}
	return 0;
}
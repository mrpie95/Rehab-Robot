#include "Robot.h"
#include <chrono>
int main(int argc, char** argv)
{
	Robot nao("169.254.79.239");
	std::future<void> th2 = std::async(std::launch::async, &Robot::handsOutFront, nao);
	std::future<void> th1 = std::async(std::launch::async, &Robot::say, nao, "Hands Out Front");

	std::this_thread::sleep_for(std::chrono::seconds(5));
	return 0;
}
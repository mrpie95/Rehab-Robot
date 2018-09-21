#include <ctime>
#include <iostream>  
#include <stdlib.h>
#include <fstream>

using namespace std;

//A simple classes used to generate logs 
class logger  {  
	
	public:
		logger(); //creates a log log file of there isn't one 

		void logEvent(string s); //function used to log a event 
};
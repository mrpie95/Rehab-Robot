#include "logger.h"

logger::logger()  
{

}  
	 
void logger::logEvent(string s)
{
	ofstream file;
	time_t     now = time(0);
    struct tm  tstruct;
    char       date[80];
    tstruct = *localtime(&now);

    strftime(date, sizeof(date), "%Y-%m-%d.%X", &tstruct);

	file.open ("Log.txt", std::fstream::out | std::fstream::app);

	file << "Event: " << date << " - " + s + "\n";

	file.close();
}

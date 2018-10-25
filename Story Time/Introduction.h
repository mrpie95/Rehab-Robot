#include <iostream>
#include <alcommon/alproxy.h>
#include <alcommon/almodule.h>
#include <alproxies/alrobotpostureproxy.h>
#include <alproxies/alanimatedspeechproxy.h>
#include <alproxies/alautonomousmovesproxy.h>
#include <alerror/alerror.h>

class Introduction {

	public:
	

	void Introduce(std::string pip){
		std::string decision;
 		AL::ALRobotPostureProxy move( pip, 9559);
 		AL::ALAnimatedSpeechProxy animatedSay( pip, 9559);

  		move.applyPosture("Stand", 0.5);


 		animatedSay.say("^start(animations/Stand/Gestures/Hey_1) HELLO! I am Maria!^wait(animations/Stand/Gestures/Hey_1) ^start(animations/Stand/Gestures/YouKnowWhat_1)  Do you want  to hear a story?^run(animations/Stand/Gestures/YouKnowWhat_1) ");
  		move.applyPosture("Stand", 0.5);
			
		std::cout<< "Do you want to hear a story?";
		std::getline (std::cin,decision);
		if(decision== "yes"){
			 animatedSay.say("^start(animations/Stand/Gestures/Enthusiastic_5)I will tell you a story about my visit to the Zoo! ^wait(animations/Stand/Gestures/Enthusiastic_5)");
		}
		else{
		animatedSay.say("^run(animations/Stand/Gestures/YouKnowWhat_1)Okay. What do you want to do then?^run(animations/Stand/Gestures/YouKnowWhat_1)");
			}
  		
	}


};



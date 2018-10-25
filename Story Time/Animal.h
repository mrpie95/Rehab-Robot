/*
 * Copyright (c) 2012-2018 SoftBank Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */
#include <iostream>
#include <fstream>
#include <alcommon/alproxy.h>
#include <alcommon/almodule.h>
#include <alproxies/alaudioplayerproxy.h>
#include <alproxies/altexttospeechproxy.h>
#include <alproxies/alanimatedspeechproxy.h>
#include <alerror/alerror.h>
#include "Gesture.h"
#include <thread>
#include "gorillaGesture.h"
#include "elephantGesture.h"
#include "monkeyGesture.h"
#include "lionGesture.h"
#include "kangarooGesture.h"
using namespace std;


class Animal {

	public:

	const char* story;
	//const char* noise;
	Gesture gesture;


	void readStory(std::string pip){
	ifstream inFile;
	inFile.open(story);
	string line;
	while(std::getline(inFile,line)){
		const std::string phraseToSay = line;
		try
		{
		AL::ALAnimatedSpeechProxy tts(pip, 9559);
		tts.say(phraseToSay);
		std::cout<< "Children made noises?";

		}
		catch (const AL::ALError& e)
		{
		  std::cerr << "Caught exception: " << e.what() << std::endl;
		  exit(1);
		}
  	}

	}


	static void makeNoise(const char* noise){
	  try{
     		AL::ALAudioPlayerProxy tts( "10.42.0.93", 9559);
      		tts.playFile(noise, 0.2, 0.0);

	  }
	  catch (const AL::ALError& e)
	    {
	      std::cerr << "Caught exception: " << e.what() << std::endl;
	      exit(1);
	    }

	}


	static void noise_and_move(std::string pip, const char* noise, std::string animal){
		 AL::ALMotionProxy motion(pip, 9559);
         	 motion.wakeUp();
		std::thread t3(makeNoise, noise);
		if (animal == "elephant"){
		 std::thread t2(Gesture::elephantArmAnimation, motion);
		 std::thread t1(Gesture::elephantHeadAnimation, motion);
		 t1.join();
		 t2.join();
		 t3.join();
		}

		else if (animal == "gorilla"){
		 std::thread t2(gorillaGesture::gorillaArmAnimtion, motion);
		 std::thread t1(gorillaGesture::gorillaHeadAnimation, motion);
		 t1.join();
		 t2.join();
		 t3.join();
		}
		else if (animal == "kangaroo"){
		 std::thread t2(kangarooGesture::kangarooLegAnimation, motion);
		 std::thread t1(kangarooGesture::kangarooBodyAnimation, motion);
		 t1.join();
		 t2.join();
		 t3.join();
		}
		else if (animal == "lion"){
		 std::thread t2(lionGesture::lionLegAnimation, motion);
		 std::thread t1(lionGesture::lionHeadAnimation, motion);
		 std::thread t4(lionGesture::lionBodyAnimation, motion);
		 t1.join();
		 t2.join();
		 t4.join();
		 t3.join();
		}
		else {
		 std::thread t2(monkeyGesture::monkeyLegAnimation, motion);
		 std::thread t1(monkeyGesture::monkeyHeadAnimation, motion);
		 std::thread t4(monkeyGesture::monkeyBodyAnimation, motion);
		 t1.join();
		 t2.join();
		 t4.join();
		 t3.join();
		}

	}


};

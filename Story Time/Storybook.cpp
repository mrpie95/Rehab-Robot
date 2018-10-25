#include <iostream>
#include <stdlib.h>
#include <alcommon/alproxy.h>
#include "Animal.h"
#include "Introduction.h"
#include <thread>
#include <string>

using namespace std;


int main(int argc, char* argv[])
{
  if(argc != 2)
  {
    std::cerr << "Wrong number of arguments!" << std::endl;
    std::cerr << "Usage: say NAO_IP" << std::endl;
    exit(2);
  }
     std::string pip = argv[1];
     std::string decision;
     int number;

     //Introduction Intro;
     //Intro.Introduce(pip);

     std::cout<< "Choose story number (choose a number between 1-5). Type 0 to exit.";
     std::cin >>number;
     //while (number != 0){

     if (number==1){

        Animal Elephant;
        Elephant.story = "/home/nao/Downloads/naoqi-sdk-2.5.5.5-linux64/read/Elephant.txt";
        Elephant.readStory(pip);
        Elephant.noise_and_move(pip, "/home/nao/naoqi/preferences/elephant9.wav", "elephant");

     }
     else if (number==2){

        Animal Elephant;
        Elephant.story = "/home/nao/Downloads/naoqi-sdk-2.5.5.5-linux64/read/Elephant.txt";
        Elephant.readStory(pip);
        Elephant.noise_and_move(pip, "/home/nao/naoqi/preferences/elephant9.wav", "elephant");

        Animal Gorilla;
        Gorilla.story = "/home/nao/Downloads/naoqi-sdk-2.5.5.5-linux64/read/Gorilla.txt";
        Gorilla.readStory(pip);
        Gorilla.noise_and_move(pip, "/home/nao/naoqi/preferences/elephant9.wav", "gorilla");

     }
     else if (number==3){

        Animal Elephant;
        Elephant.story = "/home/nao/Downloads/naoqi-sdk-2.5.5.5-linux64/read/Elephant.txt";
        Elephant.readStory(pip);
        Elephant.noise_and_move(pip, "/home/nao/naoqi/preferences/elephant9.wav", "elephant");

       Animal Gorilla;
       Gorilla.story = "/home/nao/Downloads/naoqi-sdk-2.5.5.5-linux64/read/Gorilla.txt";
       Gorilla.readStory(pip);
       Gorilla.noise_and_move(pip, "/home/nao/naoqi/preferences/elephant9.wav", "gorilla");

       Animal Kangaroo;
       Kangaroo.story = "/home/nao/Downloads/naoqi-sdk-2.5.5.5-linux64/read/Kangaroo.txt";
       Kangaroo.readStory(pip);
       Kangaroo.noise_and_move(pip, "/home/nao/naoqi/preferences/elephant9.wav", "kangaroo");

     }
     else if (number==4){

        Animal Elephant;
        Elephant.story = "/home/nao/Downloads/naoqi-sdk-2.5.5.5-linux64/read/Elephant.txt";
        Elephant.readStory(pip);
        Elephant.noise_and_move(pip, "/home/nao/naoqi/preferences/elephant9.wav", "elephant");

        Animal Gorilla;
        Gorilla.story = "/home/nao/Downloads/naoqi-sdk-2.5.5.5-linux64/read/Gorilla.txt";
        Gorilla.readStory(pip);
        Gorilla.noise_and_move(pip, "/home/nao/naoqi/preferences/elephant9.wav", "gorilla");

        Animal Kangaroo;
        Kangaroo.story = "/home/nao/Downloads/naoqi-sdk-2.5.5.5-linux64/read/Kangaroo.txt";
        Kangaroo.readStory(pip);
        Kangaroo.noise_and_move(pip, "/home/nao/naoqi/preferences/elephant9.wav", "kangaroo");

        Animal Lion;
        Lion.story = "/home/nao/Downloads/naoqi-sdk-2.5.5.5-linux64/read/Lion.txt";
        Lion.readStory(pip);
        Lion.noise_and_move(pip, "/home/nao/naoqi/preferences/elephant9.wav", "lion");

     }
     else {

        Animal Elephant;
        Elephant.story = "/home/nao/Downloads/naoqi-sdk-2.5.5.5-linux64/read/Elephant.txt";
        Elephant.readStory(pip);
        Elephant.noise_and_move(pip, "/home/nao/naoqi/preferences/elephant9.wav", "elephant");

        Animal Gorilla;
        Gorilla.story = "/home/nao/Downloads/naoqi-sdk-2.5.5.5-linux64/read/Gorilla.txt";
        Gorilla.readStory(pip);
        Gorilla.noise_and_move(pip, "/home/nao/naoqi/preferences/elephant9.wav", "gorilla");

        Animal Kangaroo;
        Kangaroo.story = "/home/nao/Downloads/naoqi-sdk-2.5.5.5-linux64/read/Kangaroo.txt";
        Kangaroo.readStory(pip);
        Kangaroo.noise_and_move(pip, "/home/nao/naoqi/preferences/elephant9.wav", "kangaroo");

        Animal Monkey;
        Monkey.story = "/home/nao/Downloads/naoqi-sdk-2.5.5.5-linux64/read/Monkey.txt";
        Monkey.readStory(pip);
        Monkey.noise_and_move(pip, "/home/nao/naoqi/preferences/elephant9.wav", "monkey");

     }

     /*std::cout<< "Want to hear another story?";
     std::cin >> decision;
     if (decision =="yes"){
         std::cout<< "Choose the next story number (choose a number between 1-5). Type 0 to exit.";
         std::cin >>number;
     }

     else {
         number = 0;
     }*/



     //}



     //create gesture objects for each animal
     gorillaGesture gorillaAnimation;
     monkeyGesture monkeyAnimation;
     elephantGesture elephantAnimation;
     kangarooGesture kangarooAnimation;
     lionGesture lionAnimation;


  exit(0);
}

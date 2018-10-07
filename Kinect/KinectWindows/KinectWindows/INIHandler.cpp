#include "INIHandler.h"
#include <fstream>
#include <sstream>
#include <iostream>

#define log(x) std::cout << x << '\n'

INIHandler::INIHandler()
{
}

void INIHandler::Load()
{

	//wave
	_valuesInt["iNumberOfConsectiveLeftRightChecksForWave"] = 4;
	_valuesFloat["fTimeToCompleteWave"] = 5.0f;

	//head
	_valuesFloat["fHandsOnHeadDistanceLeftHand"] = 200.0f;
	_valuesFloat["fHandsOnHeadDistanceRightHand"] = 200.0f;

	//hips
	_valuesFloat["fLeftHandToLeftHipDistance"] = 200.0f;
	_valuesFloat["fRightHandToRightHipDistance"] = 200.0f;

	//shoulders
	_valuesFloat["fLeftHandToLeftShoulderDistance"] = 200.0f;
	_valuesFloat["fRightHandToRightShoulderDistance"] = 200.0f;

	//squat
	_valuesFloat["fAngleOfSquat"] = 0.0f;

	//oneleg
	_valuesFloat["fStandOnOneLegDistanceBetweenFeet"] = 300.0f;

	//handsOutFront
	_valuesFloat["fHandOutFrontLeftHandDistanceFromChest"] = 400.0f;
	_valuesFloat["fHandOutFrontRightHandDistanceFromChest"] = 400.0f;

	//simon says
	_valuesFloat["fSimonNotSaysChance"] = 0.3f;
	_valuesInt["iScoreToWin"] = 5;
	_valuesFloat["fTimeToSelectNextGesture"] = 6.0f;

	_valuesFloat["fTimeToCompleteGestureIn"] = 8.0f;
	_valuesFloat["fTimeToFailGesturesIn"] = 4.0f;

	_valuesString["sStartUpMessage"] = "Let's begin";
	_valuesString["sQueryUserForInstructions"] = "If you like to begin cross your arms. If not instuctions will play.";
	_valuesFloat["fTimeToWaitForUserResponce"] = 5.0f;

	_valuesVectorString["svCorrrectGestureResponse"] = { "Correct!", "Well done!", "Good Job!", "Awesome!", "Mathmatical!" };
	_valuesVectorString["svIncorrectGestureResponce"] = { "Oh no, you should only go when i say, Simon says", "Bad Luck, remember to only go on simon says." };
	_valuesString["sWinningMessage"] = "Congrats You win!";

}

void INIHandler::Load(std::string filepath)
{
	std::fstream file;
	file.open(filepath, std::ios::in, std::ios::binary);
	
	if (file.is_open())
	{
		std::string line;
		std::vector<std::string> parsedString;
		int lineNumber = 0;

		while (std::getline(file, line))
		{
			if (line.empty())
				continue;

			if (line[0] == '/')
				continue;


			stringParser(line, '=', parsedString);
			lineNumber++;
			if (parsedString.size() != 2)
			{
				log(std::string("INI file failed to load varible on line ") + std::to_string(lineNumber));
				continue;
			}

			if (parsedString[0][0] == 'i') //int
			{
				_valuesInt[parsedString[0]] = std::stoi(parsedString[1]);
			}
			else if (parsedString[0][0] == 'f') //float
			{
				_valuesFloat[parsedString[0]] = std::stof(parsedString[1]);
			}
			else if (parsedString[0][0] == 's' &&  parsedString[0][1] == 'v') //string vector
			{
				std::vector<std::string> temp;
				stringParser(parsedString[1], ';', temp);
				_valuesVectorString[parsedString[0]] = temp;
				temp.clear();
			}
			else if (parsedString[0][0] == 's') //string
			{
				_valuesString[parsedString[0]] = parsedString[1];
			}
			else //string
			{
				_valuesString[parsedString[0]] = parsedString[1];
			}

			parsedString.clear();
		}
	}
	else
	{
		log("Failed to load ini file, loading default values,  writing new ini file at " + filepath);
		Load();
		Write(filepath);
	}

}

void INIHandler::Write(std::string filepath)
{
	std::fstream file;
	file.open(filepath, std::ios::out, std::ios::binary);

	if (file.is_open())
	{
		file << "// File to Load Game Varibles For Simon Says\n";
		file << "// Distances are in millimeters, time is in seconds\n";
		file << "// If the varible starts with 'sv' you can store multiple varibles using ; as a break between varibles on a SINGLE line.\n";
		file << "// If you ever stuff up the file delete it and run the program it should spawn a new one. \n";
		file << "\n";


		for (auto i: _valuesInt)
		{
			file << i.first << "=" << i.second << '\n';
		}
		file << "\n";
		for (auto f: _valuesFloat)
		{
			file << f.first << "=" << f.second << '\n';
		}
		file << "\n";
		for (auto s: _valuesString)
		{
			file << s.first << "=" << s.second << '\n';
		}
		file << "\n";
		for (auto sv: _valuesVectorString)
		{
			file << sv.first << "=";
			std::string temp;
			for (auto s: sv.second)
			{
				
				temp.append(s + " ; ");
			}
			temp.pop_back();
			temp.pop_back();
			file << temp << "\n";
		}
	}

}

std::vector<std::string>& INIHandler::stringParser(std::string & s, char delim, std::vector<std::string>& elems)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;

}

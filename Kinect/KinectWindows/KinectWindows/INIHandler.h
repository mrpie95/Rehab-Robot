#pragma once
#include <string>
#include <map>
#include <vector>
#include <mutex>

class INIHandler
{
private:
	INIHandler();
	std::vector<std::string>& stringParser(std::string & s, char delim, std::vector<std::string>& elems);
	void Load();
	void Load(std::string filePath);
	void Write(std::string);

	std::map<std::string, int> _valuesInt;
	std::map<std::string, float> _valuesFloat;
	std::map<std::string, std::string> _valuesString;
	std::map<std::string, std::vector<std::string>> _valuesVectorString;
public:
	static INIHandler& getInstance()
	{
		static INIHandler instance;
		static std::once_flag flag;
		std::call_once(flag, []() { instance.Load("SimonSays.ini"); } );
		return instance;
	}

	template<typename T>
	T getValue(const std::string& key) = delete;

	template<>
	std::string getValue<std::string>(const std::string& key) {
		return !_valuesString.count(key) ? std::string() : _valuesString[key];
	}

	template<>
	int getValue<int>(const std::string& key) {
		return !_valuesInt.count(key) ? int() : _valuesInt[key];
	}

	template<>
	float getValue<float>(const std::string& key) {
		return !_valuesFloat.count(key) ? float() : _valuesFloat[key];
	}

	template<>
	std::vector<std::string> getValue<std::vector<std::string>>(const std::string& key) {
		return !_valuesVectorString.count(key) ? std::vector<std::string>() : _valuesVectorString[key];
	}


	INIHandler(const INIHandler&) = delete;
	void operator=(const INIHandler&) = delete;
};


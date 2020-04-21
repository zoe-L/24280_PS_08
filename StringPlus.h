#pragma once

#include <string>
#include <msclr\marshal_cppstd.h>  //  needed for string conversions

using namespace std;

class StringPlus {
public:
	static string ltrim(string& inString) {
		auto firstNonSpace = inString.find_first_not_of(" ");
		if (firstNonSpace == -1)
			return "";
		else
			return inString.substr(firstNonSpace);
	}
	static string rtrim(string& inString) {
		return inString.substr(0, inString.find_last_not_of(" ") + 1);
	}
	static string trim(string& inString) {
		return ltrim(rtrim(inString));
	}
	static string convertString(System::String^ aString) {
		msclr::interop::marshal_context context;
		std::string standardString = context.marshal_as<std::string>(aString);
		return standardString;
	}
	static std::vector<std::string> split(std::string str, std::string delim) {
		char* cstr = const_cast<char*>(str.c_str());
		char* current;
		std::vector<std::string> arr;
		current = strtok(cstr, delim.c_str());
		while (current != NULL) {
			arr.push_back(current);
			current = strtok(NULL, delim.c_str());
		}
		return arr;
	}

};
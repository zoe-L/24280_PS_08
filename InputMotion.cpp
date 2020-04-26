#include <fstream>
#include <sstream>
#include <string>
#include "InputMotion.h"
#include <iostream>


InputMotion::InputMotion()
{
	rotationSpeed = 0.;
	interval = 0.;
}

InputMotion::InputMotion(float revPerMinute, float timeInterval)
{
	rotationSpeed = revPerMinute;
	interval = timeInterval;
}

void InputMotion::readFile(ifstream& input)
{
	stringstream wholeLineStream;
	string wholeLineString;
	bool continueReading = true;
	int colonLocation;


	while (!input.eof() && continueReading) {
		// read the whole line, need #include <string>
		getline(input, wholeLineString);

		// check if keyword is in the line
		if (wholeLineString.find("Motion End") != string::npos) {
			continueReading = false;
		}
		// if there is a colon, set up my string stream so that it starts just after colon 
		else if ((colonLocation = wholeLineString.find(":")) != string::npos) {
			wholeLineStream.str(wholeLineString.substr(colonLocation + 1));

			if (wholeLineString.find("rotationSpeed") != string::npos) {
				wholeLineStream >> rotationSpeed;
			}
			else if (wholeLineString.find("interval") != string::npos) {
				wholeLineStream >> interval;
			}
			wholeLineStream.clear();
		}
	}
}

void InputMotion::writeFile(ostream& output)
{
	// use first line to identify motion class
	output << "InputMotion:" << endl;
	output << "rotationSpeed: " << rotationSpeed << endl;
	output << "interval: " << interval << endl;
	output << "Motion End: " << endl;
}

float InputMotion::getDeltaTheta()
{
	// RPM * (360 deg/rv) / (60 sec/min) = deg/sec
	timeElapse();
	rotationSpeed = 0;
	for (int i = 0; i < speedExpression.size(); i++) {
		rotationSpeed += speedExpression[i] * pow(time, i);
	}
	crankPos += rotationSpeed * 6 * interval;
	if (fabs(crankPos)  >= 360) {
		crankPos = 0;
		if (repeatOn == true) {
			rotationSpeed = speedExpression[0];
			resetTime();
		}
	}
	return rotationSpeed * 6 * interval;
}

void InputMotion::setSpeed(vector<float> poly)
{
	speedExpression = poly;
	resetTime();
	timeElapse();
}

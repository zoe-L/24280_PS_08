/*
Nestor Gomez
24-280 C++ for Engrs.
PS07. Due Apr. 16, 2020

Models simple steady-state rotational crank motion

*/

#pragma once
#include <vector>
using namespace std;

class InputMotion {
protected:
	float rotationSpeed; // given in rpm, CCW is positive (right-hand rule)
	float interval; // seconds 
	float time = 0;
	vector<float> speedExpression;

public:
	InputMotion();
	//default constructor
	
	InputMotion(float revPerMinute, float timeInterval);
	//constructor that sets the two main parameters
	
	virtual void readFile(ifstream& input);
	//reads data from given file stream.Stops reading when encountering motion End : ?or end - of - file
	
	virtual void writeFile(ostream& output);
	//writes data to given file stream(cannot use virtual friend function)
	
	virtual float getDeltaTheta();
	//returns the number of degrees that the link should change for each simulation step.

	// in future, set() and get() may have restrictions
	void timeElapse() { time += interval; }
	void resetTime() { time = 0; }
	void setSpeed(vector<float> poly);
	void setInterval(float timeInterval) { interval = timeInterval; }
	float getSpeed() { return rotationSpeed; }
	float getInterval() { return interval; }
};
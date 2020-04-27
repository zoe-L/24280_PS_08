/*
Nestor Gomez
24-280 C++ for Engrs.
PS07. Due Apr. 16, 2020

Provides storage for links in system and manages simulation steps

*/
#pragma once
#include "OtherLinks.h"
#include "InputMotion.h"

enum GrashofState {
	NON_GRASHOF, DOUBLE_CRANK, DOUBLE_ROCKER, CRANK_ROCKER, PARALLEL
};

class LinkageSystem {
protected:
	bool simulationIsRunning = false;
	InputMotion* itsMotion = nullptr;

	Link* theCrank = nullptr;
	Link* theCoupler = nullptr;
	Link* theRocker = nullptr;

public:
	void readFile(ifstream& input);
	void paint(Graphics^ g);

	void setCrank(Link* aLink);
	void setCoupler(Link* aLink);
	void setRocker(Link* aLink);

	Link* getCrank() { return theCrank; }
	Link* getCoupler() { return theCoupler; }
	Link* getRocker() { return theRocker; }

	friend ostream& operator<<(ostream& os, const LinkageSystem& aSystem);
	//writes all the system data to an output stream so that it looks just like a linksys input file.

	Point2D lowerBoundingBox();
	Point2D upperBoundingBox();
	// return the bounding box for the whole system. 

	GrashofState checkGrashofsLaw();
	// https://me-mechanicalengineering.com/grashofs-law/ 
	//     nice and short but has </> typo
	// https://www.cs.cmu.edu/~rapidproto/mechanisms/chpt5.html
	//     not as nicely formatted, but good reference

	bool canSimulate();

	void turnSimulationOn() { simulationIsRunning = true; }
	void turnSimulationOff() { simulationIsRunning = false; }

	void simulate(System::Windows::Forms::Form^ theSimulator);
	// this function is typically called within a separate thread

	InputMotion* getMotion() { return itsMotion; }
	void setMotion(InputMotion* aMotion);

};
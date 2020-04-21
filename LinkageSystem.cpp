#include <vector>
#include <chrono>
#include <thread>
#include <algorithm> 
#include "LinkageSystem.h"
#include "LinkageSimulator.h"

void LinkageSystem::readFile(ifstream& input)
{

	string wholeLineString;
	bool continueReading = true;

	while (!input.eof() && continueReading) {
		// read the whole line
		getline(input, wholeLineString);

		// check if keyword is in the line
		if (wholeLineString.find("Crank Link") != string::npos) {
			if (theCrank != nullptr)
				delete theCrank;
			theCrank = new Crank();
			theCrank->readFile(input);
		}
		else if (wholeLineString.find("Coupler Link") != string::npos) {
			if (theCoupler != nullptr)
				delete theCoupler;
			theCoupler = new Coupler();
			theCoupler->readFile(input);
		}
		else if (wholeLineString.find("Rocker Link") != string::npos) {
			if (theRocker != nullptr)
				delete theRocker;
			theRocker = new Rocker();
			theRocker->readFile(input);
		}
		else if (wholeLineString.find("Motion") != string::npos) {
			InputMotion *aMotion = new InputMotion();
			aMotion->readFile(input);
			setMotion(aMotion); // this will take care of crank too
		}
	}
}

void LinkageSystem::setMotion(InputMotion* aMotion)
{
	if (itsMotion != nullptr)
		delete itsMotion;

	itsMotion = aMotion;

	if (theCrank != nullptr)
		((Crank*)theCrank)->setMotion(aMotion);
}

void LinkageSystem::paint(Graphics^ g)
{
	if (theCrank != nullptr) {
		theCrank->paint(g);
	}
	if (theCoupler != nullptr) {
		theCoupler->paint(g);
	}

	if (theRocker != nullptr) {
		theRocker->paint(g);
	}
}

void LinkageSystem::setCrank(Link* aLink)
{
	if (aLink != nullptr) {
		theCrank = aLink;
		Point2D oldPin1 = theCrank->getPin(1, false);
		Point2D oldPin2 = theCrank->getPin(2, false);
		if (oldPin1.X > -INFINITY && oldPin2.X > -INFINITY && theCoupler != nullptr) {
			Point2D otherPin1 = theCoupler->getPin(1, false);
			if (otherPin1.X > -INFINITY) {
				theCrank->setPin(2, false, otherPin1);
				Point2D newPin2 = { otherPin1.X - oldPin2.X + oldPin1.X,
					otherPin1.Y - oldPin2.Y + oldPin1.Y };
				theCrank->setPin(1, false, newPin2);
			}
		}
	}
}

void LinkageSystem::setCoupler(Link* aLink)
{
	theCoupler = aLink;
	if (aLink != nullptr) {
		theCoupler = aLink;
		Point2D oldPin1 = theCoupler->getPin(1, false);
		Point2D oldPin2 = theCoupler->getPin(2, false);
		if (oldPin1.X > -INFINITY && oldPin2.X > -INFINITY) {
			if (theCrank != nullptr & theRocker == nullptr) {
				Point2D otherPin2 = theCrank->getPin(2, false);
				if (otherPin2.X > -INFINITY) {
					theCoupler->setPin(1, false, otherPin2);
					Point2D newPin2 = { otherPin2.X - oldPin2.X + oldPin1.X,
						otherPin2.Y - oldPin2.Y + oldPin1.Y };
					theCoupler->setPin(2, false, newPin2);
				}
			}
			else if (theCrank == nullptr & theRocker != nullptr) {
				Point2D otherPin1 = theRocker->getPin(1, false);
				if (otherPin1.X > -INFINITY) {
					theCoupler->setPin(2, false, otherPin1);
					Point2D newPin2 = { otherPin1.X - oldPin2.X + oldPin1.X,
						otherPin1.Y - oldPin2.Y + oldPin1.Y };
					theCoupler->setPin(1, false, newPin2);
				}
			}
			else if (theCrank != nullptr & theRocker != nullptr) {
				Point2D otherPin1 = theRocker->getPin(1, false);
				Point2D otherPin2 = theCrank->getPin(2, false);
				if (otherPin1.X > -INFINITY && otherPin2.X > -INFINITY) {
					theCoupler->setPin(1, false, otherPin2);
					theCoupler->setPin(2, false, otherPin1);
				}
			}
		}
	}
}

void LinkageSystem::setRocker(Link* aLink)
{
	if (aLink != nullptr) {
		theRocker = aLink;
		Point2D oldPin1 = theRocker->getPin(1, false);
		Point2D oldPin2 = theRocker->getPin(2, false);
		if (oldPin1.X > -INFINITY && oldPin2.X > -INFINITY && theCoupler != nullptr) {
			Point2D otherPin2 = theCoupler->getPin(2, false);
			if (otherPin2.X > -INFINITY) {
				theRocker->setPin(1, false, otherPin2);
				Point2D newPin2 = { otherPin2.X + oldPin2.X - oldPin1.X,
					otherPin2.Y + oldPin2.Y - oldPin1.Y };
				theRocker->setPin(2, false, newPin2);
			}
		}
	}
}

Point2D LinkageSystem::lowerBoundingBox()
{
	Point2D otherBound;
	float minX = INFINITY, minY = INFINITY;
	if (theCrank != nullptr) {
		otherBound = theCrank->lowerBoundingBox();
		if (otherBound.X < minX)
			minX = otherBound.X;
		if (otherBound.Y < minY)
			minY = otherBound.Y;
	}
	if (theCoupler != nullptr) {
		otherBound = theCoupler->lowerBoundingBox();
		if (otherBound.X < minX)
			minX = otherBound.X;
		if (otherBound.Y < minY)
			minY = otherBound.Y;
	}
	if (theRocker != nullptr) {
		otherBound = theRocker->lowerBoundingBox();
		if (otherBound.X < minX)
			minX = otherBound.X;
		if (otherBound.Y < minY)
			minY = otherBound.Y;
	}
	if (minX < INFINITY && minY < INFINITY)
		return { minX, minY };
	else
		return { -INFINITY, -INFINITY };
}

Point2D LinkageSystem::upperBoundingBox()
{
	Point2D otherBound;
	float maxX = -INFINITY, maxY = -INFINITY;
	if (theCrank != nullptr) {
		otherBound = theCrank->upperBoundingBox();
		if (otherBound.X > maxX)
			maxX = otherBound.X;
		if (otherBound.Y > maxY)
			maxY = otherBound.Y;
	}
	if (theCoupler != nullptr) {
		otherBound = theCoupler->upperBoundingBox();
		if (otherBound.X > maxX)
			maxX = otherBound.X;
		if (otherBound.Y > maxY)
			maxY = otherBound.Y;
	}
	if (theRocker != nullptr) {
		otherBound = theRocker->upperBoundingBox();
		if (otherBound.X > maxX)
			maxX = otherBound.X;
		if (otherBound.Y > maxY)
			maxY = otherBound.Y;
	}
	if (maxX > -INFINITY && maxY > -INFINITY)
		return { maxX, maxY };
	else
		return { -INFINITY, -INFINITY };
}

GrashofState LinkageSystem::checkGrashofsLaw()
{
	// check that all three links are there
	if (theCrank != nullptr && theCoupler != nullptr && theRocker != nullptr) {
		// check that the pins connect properly or near enough
		//      pin2Curr of crank is coincident with pin1Curr of coupler
		//      pin2Curr of coupler is coincident with pin1Curr of rocker

		// create a vector with the 4 lenghts
		// sort the vector. The shortest is at [0], the longest is at [3]
		vector <float> linkLenghts;
		linkLenghts.push_back(theCrank->getEffectiveLength());
		linkLenghts.push_back(theCoupler->getEffectiveLength());
		linkLenghts.push_back(theRocker->getEffectiveLength());
		
		float groundLinkLength = Line2D::getLength(
			theCrank->getPin(1, false),	theRocker->getPin(2, false));
		linkLenghts.push_back(groundLinkLength);

		sort(linkLenghts.begin(), linkLenghts.end());
		float sPlusL = linkLenghts[0] + linkLenghts[3];
		float pPlusQ = linkLenghts[1] + linkLenghts[2];

		if (fabs(sPlusL - pPlusQ) < 1e-8) {
			return PARALLEL;
		}
		else if (sPlusL > pPlusQ)
			return NON_GRASHOF;
		else if (fabs(linkLenghts[0] - groundLinkLength) < 1e-8)
			return DOUBLE_CRANK;
		else if (fabs(theCoupler->getEffectiveLength() - linkLenghts[0]) < 1e-8)
			return DOUBLE_ROCKER;
		else if (fabs(theCrank->getEffectiveLength() - linkLenghts[0]) < 1e-8)
			return CRANK_ROCKER;
		else
			return NON_GRASHOF;
	}
	else
		return NON_GRASHOF;
}

bool LinkageSystem::canSimulate()
{
	if (itsMotion == nullptr)
		return false;
	else {
		GrashofState currState = checkGrashofsLaw();

		// in future, we may be able to handle double rocker
		return (currState != NON_GRASHOF && currState != DOUBLE_ROCKER);
	}
}



//void LinkageSystem::simulate(System::Windows::Forms::Form^ theSimulator)
//{
//	auto start = std::chrono::system_clock::now();
//	long long elapsed, timeStep, prevTimeStep = 0;
//
//	while (simulationIsRunning) {
//		// start the timer
//		start = std::chrono::system_clock::now();
//
//		// check that simulation can actually run: 
//		//      have all three links, have input motion, meets Grashof's Criteria
//		if (canSimulate()) {
//			timeStep = itsMotion->getInterval() * 1e9; // timeStep in nanoseconds
//
//			theCrank->moveLink(nullptr, theCoupler);
//			theCoupler->moveLink(theCrank, theRocker);
//			theRocker->moveLink(theCoupler, nullptr);
//			theSimulator->Refresh();
//
//			// add a delay to account for real time interval
//			elapsed = std::chrono::nanoseconds(std::chrono::system_clock::now() - start).count();
//			if (elapsed > timeStep){
//				((ps07LinkageSimulator::LinkageSimulator ^)theSimulator)->showMessage(
//					"Simulation not possible using real time. " + elapsed + " > " + timeStep);
//				prevTimeStep = timeStep;
//			}
//			else if (prevTimeStep != timeStep)
//				((ps07LinkageSimulator::LinkageSimulator^)theSimulator)->showMessage("- - -");
//
//			std::this_thread::sleep_for(std::chrono::nanoseconds(timeStep - elapsed));
//		}
//	}
//}




void LinkageSystem::simulate(System::Windows::Forms::Form^ theSimulator)
{
	auto start = std::chrono::system_clock::now();
	long long elapsedTime, timeInterval;

	while (simulationIsRunning) {
		// start the timer
		start = std::chrono::system_clock::now();

		// check that simulation can actually run: 
		//      have all three links, have input motion, meets Grashof's Criteria
		if (canSimulate()) {
			timeInterval = itsMotion->getInterval() * 1e9;
			
			// do the step
			theCrank->moveLink(nullptr, theCoupler);
			theCoupler->moveLink(theCrank, theRocker);
			theRocker->moveLink(theCoupler, nullptr);
			theSimulator->Refresh();

			// if elapsed time (in nanosecs) for this simulation step < time interval, then wait
			elapsedTime = std::chrono::nanoseconds(std::chrono::system_clock::now() - start).count();

			// put thread to sleep for remainer of time interval (timeInterval - elapsedTime)
			std::this_thread::sleep_for(std::chrono::nanoseconds(timeInterval - elapsedTime));
			
			if (elapsedTime > timeInterval) {
				// tell LinkageSimulator to display a message on feedbackLabel
				((ps07LinkageSimulator::LinkageSimulator^)theSimulator)->showFeedback(
					"Interval too small, simulation not realtime");
			}
			else
				((ps07LinkageSimulator::LinkageSimulator^)theSimulator)->showFeedback(
					"Simulation running.");
		}
	}
}


ostream& operator<<(ostream& os, const LinkageSystem& aSystem)
{
	if (aSystem.theCrank != nullptr) {
		os << "Crank Link:" << endl;
		os << *(aSystem.theCrank);
		os << "Link End:" << endl;
	}
	if (aSystem.theCoupler != nullptr) {
		os << "Coupler Link:" << endl;
		os << *(aSystem.theCoupler);
		os << "Link End:" << endl;
	}
	if (aSystem.theRocker != nullptr) {
		os << "Rocker Link:" << endl;
		os << *(aSystem.theRocker);
		os << "Link End:" << endl;
	}
	if (aSystem.itsMotion != nullptr) {
		//os << "InputMotion:" << endl;  
		aSystem.itsMotion->writeFile(os);
		//os << "Motion End:" << endl;	
	}
	return os;
}

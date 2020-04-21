#pragma once
#include <string>
#include "Shape2D.h"
#include "ColorConverter.h"

using namespace std;
using namespace System::Drawing;

class Link {
protected:
	string linkID;
	Point2D pin1Local, pin2Local; // set to (-INF, -INF) if not assigned
	Point2D pin1Curr, pin2Curr; // set to (-INF, -INF) if not assigned
	float thickness;
	float colorH, colorS, colorV;
	Shape2D* geometry = nullptr;

	float getRotAngleRadians();

public:
	Link();
	// constructor that sets all default values

	void readFile(ifstream& input);
	//takes the input stream and loads all the data into the link, replacing any data that may already be
	//	assigned.  See attached file for a sample link file(.link). Note that not all link parameters may be in the
	//	file.

	friend ostream& operator<<(ostream& os, const Link& aLink);
	//writes all the link data to an output stream so that it looks just like a link input file.
	
	void setID(string aString) { linkID = aString; }
	string getID() { return linkID; }

	void setPin(int number, bool local, Point2D aPoint);
	Point2D getPin(int number, bool local);

	void setPin1Local(Point2D aPoint) { pin1Local = aPoint; }
	void setPin2Local(Point2D aPoint) { pin2Local = aPoint; }
	void setPin1Curr(Point2D aPoint) { pin1Curr = aPoint; }
	void setPin2Curr(Point2D aPoint) { pin1Curr = aPoint; }
	Point2D getPin1Local() { return pin1Local; }
	Point2D getPin2Local() { return pin1Local; }
	Point2D getPin1Curr() { return pin1Curr; }
	Point2D getPin2Curr() { return pin2Curr; }

	float getArea();
	// returns the area of the link, scaled accordingly. returns 0.0 if no area

	void setThickness(float newThickness) {
		if (newThickness >= 0)
			thickness = newThickness;
	}
	float getThickness() { return thickness; }

	Color getColor() {
		return colorFromHSV(colorH, colorS, colorV);
	}
	void setColor(Color newColor) {
		colorToHSV(newColor, colorH, colorS, colorV);
	}
	float getEffectiveLength() ;
	//calculates and returns the length between the current locations of the link’s pins.
	
	void addShape(Shape2D* aShape) { 
		//if (geometry != nullptr)
		//	delete geometry;
		geometry = aShape; 
	};

	void addShape(std::string filename);
	//adds a Shape2D to the link.
	
	Shape2D* getShape() {
		return geometry;
	};
	//returns the Shape2D that is currently associated with the link.
	
	void paint(Graphics^ g, bool useLocalCoords = false, float lineWidth = 0., bool filled = false);
	//displays the link on the graphics space.If useLocalCoords is set to true, display the link using only its
	//	local coordinates(i.e., do not apply rotation or scaling that are implied in pin1Curr and pin2Curr).

	virtual void moveLink(Link* prevLink, Link* nextLink) {};
	// virtual empty function, to be defined by subclasses

	Point2D getLocalFromCurr(Point2D worldCoords);
	Point2D getCurrFromLocal(Point2D shapeCoords);

	Point2D lowerBoundingBox();
	Point2D upperBoundingBox();
	// return the bounding box for the link. Will almost certainly be conservative due
	// to link rotation

	int nearestPin(Point2D testPoint, bool useLocalCoords = false);

};
#pragma once
/*
				   Nestor Gomez
				   24-280 C++ for Engrs.
	 __            ps05. Due Feb. 14, 2020
	/  `-_
   /      `____    Models a shape as a sequence of coordinate vertices
   |           |   (xi, yi) that define a non-self-intersecting closed loop
   |           |   with straight line segments from vertex to vertex. In
   |          /    order to close the loop, we assumed that there is an
	`._____,-'     additional line segment from the last vertex to the
				   first vertex.
*/

#include <fstream>
#include <vector>
#include "Line2D.h"

using namespace std;
using namespace System::Drawing;

class Shape2D {
protected:
	vector<Point2D> thePoints;
	float areaTotal;   // the area of the shape
	float perimTotal;
	float momInertiaX;
	float momInertiaY;
	Point2D lowerBound;
	Point2D upperBound;
	Point2D centroidPnt;
	int highlightPoint = -1;

	//protected function, returns true if any edge of the shape intersects another, thereby creating a non - real
	//	shape.This function is called whenever there is a request for a change to the shape that may create
	//	self - intersection(s).
	bool selfIntersects();

	//protected function used to assure that dependent member variables are kept up - to - date.This function
	//	is called whenever there is change to the shape that may affect the dependent variables.
	void recalcShape();

	float pointDiameter();
	// returns a working size for anything related to showing and selecting points

	bool isInSquare(Point2D testPoint, Point2D targetPoint);

public:
	//  default constructor for the class. Initializes member variables only.
	Shape2D();

	//  additional constructor for the class. Takes a pre - created
	//	ifstream and uses it to read coordinate information for the shape. Note that the method’s parameter
	//	cannot be a string filename because the file may already be in the process of being read.The
	//	constructor needs to instantiate any constituent objectsand /or data structures.
	Shape2D(ifstream& input);

	//  adds a coordinate point such that the
	//	new point becomes the index - th point.For example, an index value of 3 will insert a point between
	//	the existing 2nd and 3rd points such that the new point becomes the new 3rd point. An index of 1 will
	//	insert the new point at the start of the shape and an index greater than the number of points will insert
	//	the new point as the last point. Function returns false only if the new point cannot be added for any
	//	reason.
	bool addPoint(Point2D newPoint, int index);

	//  creates a coordinate point with the given coordinatesand inserts it into the path such that the 
	//	new point becomes the index - th point. Otherwise similar to above.
	bool addPoint(float newX, float newY, int index);

	//  creates a coordinate point between vertices
	//	index - 1 and index and inserts it into the line segment at the given ratio.The ratio is a number greater
	//	than zero and less than 1. Note that, like above, the new point becomes the index - th point. Returns
	//	false if it cannot insert point(e.g., index is too large or too small, ratio value is inappropriate). [A
	//	ratio close to zero will insert the new vertex near index - 1; a ratio of 0.5 will insert the new vertex at
	//	the middle of the segment; and a ratio close to 1 will insert the new vertex near old index.]
	bool addPoint(int index, float ratio);

	//  removes the indicated point from the shape.
	//  Function returns false only if the point cannot be removed for any reason.
	bool removePoint(int index);

	//  returns the length of the perimeter of the shape.
	float perimeter() {
		return perimTotal;
	};

	//returns the value of the area encompassed by the shape.Returns - 1 if the shape has fewer than three
//	points.
	float area() {
		return areaTotal;
	};

	//returns the coordinates of centroid of the area encompassed by the shape.Returns(-INFINITY, -
	//	INFINITY) if the shape has fewer than three points.
	Point2D centroid() {
		return centroidPnt;
	};

	//return a point corresponding to the upper right corner of a bounding box for the shape(maximum X
	//	and maximum Y value of all points).
	Point2D upperBoundingBox() {
		return upperBound;
	};

	//return a point corresponding to the lower left corner of a bounding box for the shape(minimum X and
	//	minimum Y value of all points).
	Point2D lowerBoundingBox() {
		return lowerBound;
	};

	int getPointCount() { return thePoints.size(); }
	Point2D getPoint(int index) {
		if (index > 0 && index <= thePoints.size())
			return thePoints[index - 1];
		else
			return { -INFINITY, -INFINITY };
	}
	//void paint(Graphics^ g, Pen^ p = gcnew Pen(Color::CornflowerBlue, 0), bool showPoints = false,
	//	bool filled = false, Image^ anImage = nullptr);
	void paint(Graphics^ g, Pen^ p = nullptr, bool showPoints = false,
		bool filled = false, Image^ anImage = nullptr);
	//generates the geometry of the shape on the given graphic space, with given colorand other parameters
	//(many of which have default values for now).This can be tricky, so we’ll develop it in lecture.

	//  used to output all the coordinates of a shape
	friend ostream& operator<<(ostream& os, const Shape2D& aShape);

	void setHighlight(int index);
	//sets highlightPoint member variable.If index is less than or equal to zero or index is greater than
	//	number of points, set index to - 1.

	bool movePoint(Point2D newLoc, int index);
	//takes the point at index and moves it to the given location, returning true. If the move cannot be made
	//	either because there is no point at index or movement would create a self-intersecting shape, no change
	//	is made and the function returns false.

	int indexOfNearestPoint(Point2D testPoint);
	// returns the index of the shape point that has testPoint within a square of pointDiameter()

};
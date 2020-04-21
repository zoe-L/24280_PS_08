#include <algorithm>
#include <sstream>
#include "StringPlus.h"
#include "Shape2D.h"
#define TOLERANCE 1e-8

bool Shape2D::selfIntersects()
{
	if (thePoints.size() < 3)
		return false;
	else {
		Point2D trueIntersect, currBack, currFront, otherBack, otherFront;
		int size = thePoints.size(); // makes it easier/faster to use
		int backIndex = size - 1;
		float tempInfinity = -INFINITY;
		bool checkLastSegment = false; // for first loop

		// cycle through each segment from last (last point to first point)
		// and check trueIntersect with all other segments starting from current + 2
		// to last segment. Don't check if segments are adjacent
		currBack = thePoints.back();
		for (int frontIndex = 0; frontIndex < size; frontIndex++) {
			currFront = thePoints[frontIndex];

			for (int otherFrontIndex = frontIndex + 2;
				otherFrontIndex < size;
				otherFrontIndex++) {
				otherBack = thePoints[otherFrontIndex - 1];
				otherFront = thePoints[otherFrontIndex];

				// be sure not to check last segment against gap segment
				if (backIndex != otherFrontIndex) {
					trueIntersect = Line2D::getTrueIntersection(currBack, currFront,
						otherBack, otherFront);
					if (trueIntersect.X > -INFINITY || trueIntersect.Y > -INFINITY)
						return true;   //  <<<<<<<<<< possible exit from function
				}
			}
			// advance by one point
			currBack = currFront;
			backIndex = frontIndex;
		}
		return false; // could not find self-intersection
	}
}

void Shape2D::recalcShape()
{
	// initialize
	areaTotal = perimTotal = momInertiaX = momInertiaY = 0.;

	// check if there are enough points and that they are valid
	if (thePoints.size() < 3 || selfIntersects()) {
		centroidPnt = lowerBound = upperBound = { -INFINITY, -INFINITY };
	}
	else {
		Point2D currBack = thePoints.back();
		lowerBound = upperBound = currBack;
		float deltaX, deltaY, minX, minY, rectArea, triArea;
		float rectXbar, rectYbar, triXbar, triYbar;
		float sumXbarArea = 0, sumYbarArea = 0;

		float sumIX = 0, sumIY = 0; // sum of inertia about y=0 and x=0, respectively

		for (auto& currFront : thePoints) {  // a nice clean way of cycling through a vector

			deltaX = currFront.X - currBack.X;
			deltaY = fabsf(currFront.Y - currBack.Y); // triangle needs to be always positive
			minX = min(currFront.X, currBack.X);
			minY = min(currFront.Y, currBack.Y);
			rectArea = deltaX * minY;
			triArea = deltaX * deltaY / 2.;
			rectXbar = (currFront.X + currBack.X) / 2.;
			rectYbar = minY / 2.;
			triYbar = minY + fabsf(deltaY) / 3.;

			// triXbar is a bit tricky
			if (currBack.Y > currFront.Y)
				triXbar = currBack.X + (deltaX) / 3.;
			else
				triXbar = currBack.X + 2. * (deltaX) / 3.;

			// running sums
			perimTotal += Line2D::getLength(currFront, currBack);
			areaTotal += rectArea + triArea;
			sumXbarArea += rectArea * rectXbar + triArea * triXbar;
			sumYbarArea += rectArea * rectYbar + triArea * triYbar;

			// take moments of inertia about the global axes
			sumIX += deltaX * powf(minY, 3) / 3. +
				deltaX * fabsf(powf(deltaY, 3)) / 36. + triArea * triYbar * triYbar;
			sumIY += minY * powf(deltaX, 3) / 12. + rectArea * rectXbar * rectXbar +
				fabsf(deltaY) * (powf(deltaX, 3)) / 36. + triArea * triXbar * triXbar;

			// overall maximums and minimums
			if (currFront.X < lowerBound.X)
				lowerBound.X = currFront.X;
			if (currFront.Y < lowerBound.Y)
				lowerBound.Y = currFront.Y;

			if (currFront.X > upperBound.X)
				upperBound.X = currFront.X;
			if (currFront.Y > upperBound.Y)
				upperBound.Y = currFront.Y;

			// get ready for next loop
			currBack = currFront;
		}
		// finish up
		if (fabsf(areaTotal) > 1e-8) {
			centroidPnt = { sumXbarArea / areaTotal, sumYbarArea / areaTotal };
			momInertiaX = sumIX - areaTotal * centroidPnt.Y * centroidPnt.Y;
			momInertiaY = sumIY - areaTotal * centroidPnt.X * centroidPnt.X;
		}
		// do not correct this until after centroid calculation
		// in general, if shape is defined CCW, the area will be negative (e.g., a hole)
		// we could change that by changing sign of deltaX
		areaTotal = fabsf(areaTotal);
		momInertiaX = fabsf(momInertiaX);
		momInertiaY = fabsf(momInertiaY);
	}
}


Shape2D::Shape2D()
{
	recalcShape();
}

Shape2D::Shape2D(ifstream& input)
{	// add the capability to stop reading when encountering "Shape End:"
	stringstream wholeLineStream;
	string wholeLineString;
	bool continueReading = true;

	// added some error checking to disallow duplicate points
	float prevX = 0., prevY = 0.;
	bool firstTime = true;

	float xCoord, yCoord;
	while (!input.eof() && continueReading) {
		// read the whole line
		getline(input, wholeLineString);

		// check if keyword is in the line
		if (wholeLineString.find("Shape End") != string::npos) // if yes, stop reading, 
			continueReading = false;

		else {   //  else get the numbers 
			// initialize string stream
			wholeLineStream.str(wholeLineString);

			// input >> xCoord >> yCoord;
			wholeLineStream >> xCoord >> yCoord;

			// reset string stream so it will read from start next time around
			wholeLineStream.clear();

			if (firstTime ||
				fabs(prevX - xCoord) > TOLERANCE || fabs(prevY - yCoord) > TOLERANCE)
				thePoints.push_back({ xCoord, yCoord });

			prevX = xCoord; prevY = yCoord;
			firstTime = false;
		}
	}

	bool shapeNoGood = selfIntersects();
	// don't know what to do if the shape is bad
	// should I delete all the points????

	recalcShape();
}

bool Shape2D::addPoint(Point2D newPoint, int index)
{
	if (index <= 0)
		return false;
	else {
		if (index > thePoints.size())
			thePoints.push_back(newPoint);
		else
			thePoints.insert(thePoints.begin() + index - 1, newPoint);

		recalcShape();
		return true;
	}
}

bool Shape2D::addPoint(float newX, float newY, int index)
{
	return addPoint({ newX, newY }, index);
}

bool Shape2D::addPoint(int index, float ratio)
{

	if (index <= 0 || index > thePoints.size() || ratio <= 0. || ratio >= 1.)
		return false;
	else {
		Point2D pnt1, pnt2, newPoint;
		if (index == 1)
			pnt1 = thePoints.back();
		else
			pnt1 = thePoints[index - 2];

		pnt2 = thePoints[index - 1];

		// interpolating
		newPoint.X = pnt1.X + ratio * (pnt2.X - pnt1.X);
		newPoint.Y = pnt1.Y + ratio * (pnt2.Y - pnt1.Y);;

		// add the point
		addPoint(newPoint, index);
		//recalcShape(); // not needed since shape is essentially the same

		return true;
	}
}

bool Shape2D::removePoint(int index)
{
	if (index <= 0 || index > thePoints.size())
		return false;
	else {
		thePoints.erase(thePoints.begin() + index - 1);
		recalcShape();

		return true;
	}
}

float Shape2D::pointDiameter()
{
	return max(upperBound.X - lowerBound.X, lowerBound.Y - lowerBound.Y) / 80.;
}

void Shape2D::paint(Graphics^ g, Pen^ p, bool showPoints,
	bool filled, Image^ anImage)
{
	float diameter = pointDiameter();
	if (p == nullptr)
		p = gcnew Pen(Color::CornflowerBlue, 0);

	// go through all the points
	// draw a line between last point and curr point
	//Point2D lastPoint;
	//lastPoint = thePoints.back();
	//for (auto& currPoint : thePoints) {
	//	g->DrawLine(p, lastPoint.X, lastPoint.Y,
	//		currPoint.X, currPoint.Y);
	//	if (highlightPoint != -1) {
	//		g->DrawRectangle(p, currPoint.X - diameter / 2.,
	//			currPoint.Y - diameter / 2., diameter, diameter);
	//	}

	//	lastPoint = currPoint;
	//}

	// traditional loop
	//for (int i = 0; i < thePoints.size(); i++) {
	//	currPoint = thePoints[i];
	//	g->DrawLine(p, lastPoint.X, lastPoint.Y,
	//		currPoint.X, currPoint.Y);
	//	lastPoint = currPoint;
	//}

	// drawing a continuous shape
	//create and load up a cli::array of points
	cli::array<PointF>^ pointArray = gcnew cli::array<PointF>(thePoints.size());
	int i = 0;
	for (auto& currPoint : thePoints) {
		pointArray[i++] = PointF(currPoint.X, currPoint.Y);
		if (highlightPoint != -1) {
			g->DrawRectangle(p, currPoint.X - diameter / 2.,
				currPoint.Y - diameter / 2., diameter, diameter);
		}
	}

	// draw as a curve
	if (filled) {
		Brush^ theBrush;
		
		if (anImage != nullptr)
			theBrush = gcnew TextureBrush(anImage);
		else
			theBrush = gcnew SolidBrush(p->Color);

		g->FillClosedCurve(theBrush, pointArray);
	}
	else {
		g->DrawClosedCurve(p, pointArray, 0.0,  // 0.0 is the spline tension
			Drawing2D::FillMode::Winding); // winding parameter is needed but ignored
	}

	// draw highlight
	if (highlightPoint != -1) {
		diameter *= 3;
		g->DrawEllipse(p, thePoints[highlightPoint - 1].X - diameter / 2.,
			thePoints[highlightPoint - 1].Y - diameter / 2., diameter, diameter);
	}
}

void Shape2D::setHighlight(int index)
{
	if (index > 0 && index <= thePoints.size())
		highlightPoint = index;
	else
		highlightPoint = -1;
}

bool Shape2D::movePoint(Point2D newLoc, int index)
{
	if (index > 0 && index <= thePoints.size()) {
		Point2D oldPoint = thePoints[index - 1];
		thePoints[index - 1] = newLoc;
		if (selfIntersects()) {
			thePoints[index - 1] = oldPoint;
			return false;
		}
		else {
			recalcShape();
			return true;
		}
	}
	else
		return false;
}

bool Shape2D::isInSquare(Point2D testPoint, Point2D targetPoint) {
	float halfDiam = pointDiameter() / 2.;
	return !(testPoint.X < (targetPoint.X - halfDiam) || testPoint.X >(targetPoint.X + halfDiam)
		|| testPoint.Y < (targetPoint.Y - halfDiam) || testPoint.Y >(targetPoint.Y + halfDiam));

}

int Shape2D::indexOfNearestPoint(Point2D testPoint)
{
	float halfDiam = pointDiameter() / 2.;

	// do quick bounds check
	if (testPoint.X < (lowerBound.X - halfDiam) || testPoint.X >(upperBound.X + halfDiam)
		|| testPoint.Y < (lowerBound.Y - halfDiam) || testPoint.Y >(upperBound.Y + halfDiam))
		return -1;
	else {  // go through all points to see if there's a match
		Point2D currPoint;
		for (int i = 0; i < thePoints.size(); i++) {
			if (isInSquare(testPoint, thePoints.at(i)))
				return i + 1;
		}
		return -1;
	}
}

//float Shape2D::perimeter()
//{
//	if (thePoints.size() < 3)
//		return -INFINITY;
//	else {
//		// initialize by including the "last" segment
//		float perimSum = Line2D::getLength(thePoints.back(), thePoints.front());
//
//		for (int i = 1; i < thePoints.size(); i++)
//			perimSum += Line2D::getLength(thePoints[i - 1], thePoints[i]);
//
//		return perimSum;
//	}
//}



ostream& operator<<(ostream& os, const Shape2D& aShape)
{
	// for each point in vector, output x and y
	for (int i = 0; i < aShape.thePoints.size(); i++) {
		os << aShape.thePoints.at(i).X << "\t"
			<< aShape.thePoints[i].Y << endl;
	}
	return os;
}

//double results[3];
//
//Point2D currBack = thePoints.back();
//for (auto& currFront : thePoints) {  // a nice clean way of cycling through a vector
//	g->DrawLine(p, currBack.X, currBack.Y, currFront.X, currFront.Y);
//
//	// get ready for next loop
//	currBack = currFront;
//}

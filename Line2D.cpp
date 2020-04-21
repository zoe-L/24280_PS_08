#include <math.h>
#include "Line2D.h"

#define TOLERANCE_LINE2D 1e-6  
// had to reduce tolerance from 1e-8

float Line2D::getLength(Point2D startPoint, Point2D endPoint)
{
	return getLength(startPoint.X, startPoint.Y, endPoint.X, endPoint.Y);
}

float Line2D::getLength(float startX, float startY, float endX, float endY)
{
	return sqrtf((startX - endX) * (startX - endX) +
		(startY - endY) * (startY - endY));

}

Point2D Line2D::getIntersection(Point2D start1, Point2D end1, Point2D start2, Point2D end2)
{
	float x1 = start1.X, y1 = start1.Y;
	float x2 = end1.X, y2 = end1.Y;
	float x3 = start2.X, y3 = start2.Y;
	float x4 = end2.X, y4 = end2.Y;
	float pX, pY;
	float denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

	if (fabs(denominator) < TOLERANCE_LINE2D)
		return { -INFINITY, -INFINITY };  // lines are parallel
	else {
		pX = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4))
			/ denominator;
		pY = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4))
			/ denominator;

		return { pX, pY };
	}
}

bool Line2D::isbetween(Point2D pointA, Point2D pointB, Point2D pointC)
{
	float lengthAB = getLength(pointA, pointB);
	float lengthAC = getLength(pointA, pointC);
	float lengthBC = getLength(pointB, pointC);
	return fabs(lengthAB + lengthBC - lengthAC) < TOLERANCE_LINE2D;
}

Point2D Line2D::getTrueIntersection(Point2D start1, Point2D end1,
	Point2D start2, Point2D end2)
{
	Point2D generalIntersect = getIntersection(start1, end1, start2, end2);
	if (generalIntersect.X == -INFINITY && generalIntersect.Y == -INFINITY)
		return generalIntersect;
	else {
		bool check1 = isbetween(start1, generalIntersect, end1);
		bool check2 = isbetween(start2, generalIntersect, end2);
		if (isbetween(start1, generalIntersect, end1)
			&& isbetween(start2, generalIntersect, end2))
			return generalIntersect;  // intersection is on both segments
		else
			return { -INFINITY, -INFINITY };  // intersection not on segments
	}
}


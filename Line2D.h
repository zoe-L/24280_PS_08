#pragma once

struct Point2D {
	float X;
	float Y;
};

class Line2D {
public:
	//returns the distance from one point to the other.
	static float getLength(Point2D startPoint, Point2D endPoint);
	
	//returns the distance from one point to the other.
	static float getLength(float startX, float startY, float endX, float endY);

	// returns intersection of two lines
	static Point2D getIntersection(Point2D start1, Point2D end1,
		Point2D start2, Point2D end2);

	// returns true if point B is exactly between points A and C
	// uses definition of betweeness
	static bool isbetween(Point2D pointA, Point2D pointB, Point2D pointC);

	// returns the intersection of the two line segments defined by startand end points given.The true
	//	intersection differs from the mathematical intersection in that the two line segments(not just their
	//	infinite linear extensions) must cross.If there is no true intersection(i.e., the lines are parallel), the
	//	coordinates of the results are set to(-INFINITY, -INFINITY).
	static Point2D getTrueIntersection(Point2D start1, Point2D end1,
		Point2D start2, Point2D end2);
};
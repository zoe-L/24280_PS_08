#include "OtherLinks.h"

void Crank::moveLink(Link* prevLink, Link* nextLink)
{
	if (itsMotion != nullptr) {
		// use motion to get new position of far pin (pin2)
		float angle = atan2(pin2Curr.Y - pin1Curr.Y, pin2Curr.X - pin1Curr.X);

		//float rpm = 5.0;  // will come from motion later
		//float deltaT = 0.1; // will come from motion later
		//angle += deltaT * rpm * PI / 60.; // will come from motion later

		// get change in angle (don't forget to convert to radians)
		angle += itsMotion->getDeltaTheta() * atan(1.) / 45.; 

		float radius = getEffectiveLength();
		pin2Curr.X = pin1Curr.X + radius * cos(angle);
		pin2Curr.Y = pin1Curr.Y + radius * sin(angle);
	}
}

void Coupler::moveLink(Link* prevLink, Link* nextLink)
{
	float couplerLength = getEffectiveLength();
	Point2D newPin1 = prevLink->getPin(2, false);
	Point2D rockerPin2 = nextLink->getPin(2, false);
	float rockerLength = nextLink->getEffectiveLength();
	float centerDistance = Line2D::getLength(newPin1, rockerPin2);
	float centerAngle = atan2(rockerPin2.Y - newPin1.Y, rockerPin2.X - newPin1.X);

	// calculate angle between center line and intersections using law of cosines
	float theta = acos((rockerLength * rockerLength - couplerLength * couplerLength
		- centerDistance * centerDistance) / (-2. * couplerLength * centerDistance));

	// get intersection points
	Point2D intersect1, intersect2;
	intersect1.X = newPin1.X + couplerLength * cos(centerAngle + theta);
	intersect2.X = newPin1.X + couplerLength * cos(centerAngle - theta);
	intersect1.Y = newPin1.Y + couplerLength * sin(centerAngle + theta);
	intersect2.Y = newPin1.Y + couplerLength * sin(centerAngle - theta);

	float distToIntersect1 = Line2D::getLength(intersect1, pin2Curr);
	float distToIntersect2 = Line2D::getLength(intersect2, pin2Curr);

	// check for distance to intersect < (centerdistance - length of rocker)

	// set the new positions of coupler link
	pin1Curr = newPin1;
	if (distToIntersect1 < distToIntersect2)
		pin2Curr = intersect1;
	else
		pin2Curr = intersect2;
}

void Rocker::moveLink(Link* prevLink, Link* nextLink)
{
	pin1Curr = prevLink->getPin(2, false);
}


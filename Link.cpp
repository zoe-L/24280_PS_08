#include <sstream>
#include "Link.h"
#include "StringPlus.h"
#include "ColorConverter.h"

Link::Link()
{
	pin1Local = { -INFINITY, -INFINITY };
	pin2Local = { -INFINITY, -INFINITY };
	pin1Curr = { -INFINITY, -INFINITY };
	pin2Curr = { -INFINITY, -INFINITY };
	colorH = 240.; colorS = 1.0; colorV = 1.0;
	thickness = -INFINITY;
}

void Link::readFile(ifstream& input)
{
	stringstream wholeLineStream;
	string wholeLineString;
	bool continueReading = true;
	int colonLocation;

	while (!input.eof() && continueReading) {
		// read the whole line
		getline(input, wholeLineString);

		// if there is a colon, set up my string stream so that it starts just after colon 
		if ((colonLocation = wholeLineString.find(":")) != string::npos)
			wholeLineStream.str(wholeLineString.substr(colonLocation + 1));

		// check if keyword is in the line
		if (wholeLineString.find("Link End") != string::npos) // if yes, stop reading, 
			continueReading = false;

		else if (wholeLineString.find("linkID") != string::npos) {
			linkID = StringPlus::trim(
				wholeLineString.substr(colonLocation + 1));
		}
		else if (wholeLineString.find("Shape Start") != string::npos) {
			geometry = new Shape2D(input);

		}
		else if (wholeLineString.find("pin") != string::npos) {
			Point2D newPnt;
			wholeLineStream >> newPnt.X >> newPnt.Y;
			wholeLineString = wholeLineString.substr(3, 6);
			if (wholeLineString.find("1") != string::npos) {
				if (wholeLineString.find("Local") != string::npos)
					pin1Local = newPnt;
				else
					pin1Curr = newPnt;
			}
			else {
				if (wholeLineString.find("Local") != string::npos)
					pin2Local = newPnt;
				else
					pin2Curr = newPnt;
			}
		}
		else if (wholeLineString.find("thickness") != string::npos) {
			wholeLineStream >> thickness;
		}
		else if (wholeLineString.find("color") != string::npos) {
			wholeLineStream >> colorH >> colorS >> colorV;
		}
		wholeLineStream.clear();
	}
}

void Link::setPin(int number, bool local, Point2D aPoint)
{
	if (local)
		if (number == 1)
			pin1Local = aPoint;
		else
			pin2Local = aPoint;
	else
		if (number == 1)
			pin1Curr = aPoint;
		else
			pin2Curr = aPoint;
}

Point2D Link::getPin(int number, bool local)
{
	if (local)
		if (number == 1)
			return pin1Local;
		else
			return pin2Local;
	else
		if (number == 1)
			return pin1Curr;
		else
			return pin2Curr;

}

float Link::getArea()
{
	if (geometry != nullptr) {
		float scale = getEffectiveLength() / Line2D::getLength(pin1Local, pin2Local);
		return geometry->area() * scale * scale;  // need to square scale to get area.
	}
	else
		return 0.0f;
}

float Link::getEffectiveLength()
{
	if (pin1Curr.X != -INFINITY && pin1Curr.Y != -INFINITY
		&& pin2Curr.X != -INFINITY && pin2Curr.Y != -INFINITY)
		return Line2D::getLength(pin1Curr, pin2Curr);
	else
		return -1;
}

void Link::addShape(std::string filename)
{
	ifstream inFile;
	inFile.open(filename);
	if (inFile.is_open()) {
		if (geometry != nullptr)
			delete geometry;
		geometry = new Shape2D(inFile);
		inFile.close();
	}
}

float Link::getRotAngleRadians()
{
	if (getEffectiveLength() > 0) {
		float rotationAngle = atan2(pin2Curr.Y - pin1Curr.Y, pin2Curr.X - pin1Curr.X);
		rotationAngle -= atan2(pin2Local.Y - pin1Local.Y, pin2Local.X - pin1Local.X);
		return rotationAngle;
	}
	else
		return 0.;
}

void Link::paint(Graphics^ g, bool useLocalCoords, float lineWidth, bool filled)
{
	float rotationAngle = getRotAngleRadians() * 45. / atan(1.);
	float scale = getEffectiveLength() / Line2D::getLength(pin1Local, pin2Local);
	if (!useLocalCoords && getEffectiveLength() > 0.) {
		g->TranslateTransform(pin1Curr.X, pin1Curr.Y);
		g->ScaleTransform(scale, scale);
		g->RotateTransform(rotationAngle);
		g->TranslateTransform(-pin1Local.X, -pin1Local.Y);

		lineWidth /= scale; // adjust lineWidth for scale of link
	}

	// draw the shape
	if (geometry != nullptr) {
		Pen^ aPen = gcnew Pen(colorFromHSV(colorH, colorS, colorV), lineWidth);
		geometry->paint(g, aPen, false, filled); // for filling with color
	}

	// draw the pins
	if (pin1Local.X > -INFINITY && pin2Local.X > -INFINITY) {

		float diameter = Line2D::getLength(pin1Local, pin2Local) / 12.;
		Pen^ aPen = gcnew Pen(Color::ForestGreen, lineWidth);
		g->DrawEllipse(aPen, pin1Local.X - diameter / 2., pin1Local.Y - diameter / 2.,
			diameter, diameter);
		g->DrawLine(aPen, pin1Local.X - diameter / 1.8, pin1Local.Y,
			pin1Local.X + diameter / 1.8, pin1Local.Y);
		g->DrawLine(aPen, pin1Local.X, pin1Local.Y - diameter / 1.8,
			pin1Local.X, pin1Local.Y + diameter / 1.8);

		g->DrawEllipse(aPen, pin2Local.X - diameter / 2., pin2Local.Y - diameter / 2.,
			diameter, diameter);
		g->DrawLine(aPen, pin2Local.X - diameter / 2., pin2Local.Y,
			pin2Local.X + diameter / 1.8, pin2Local.Y);
		g->DrawLine(aPen, pin2Local.X, pin2Local.Y - diameter / 1.8,
			pin2Local.X, pin2Local.Y + diameter / 1.8);

		// draw the name on the link
		float textSize = Line2D::getLength(pin1Local, pin2Local) / 15.;
		if (textSize > 0.) {
			// Create font and brush.
			System::Drawing::Font^ drawFont = gcnew System::Drawing::Font("Arial", textSize);
			SolidBrush^ drawBrush; 
			if (filled)
				drawBrush = gcnew SolidBrush(Color::Black); // for fill with color
			else
				drawBrush = gcnew SolidBrush(colorFromHSV(colorH, colorS, colorV));

			// translate and rotate so that text is along line from pin to pin
			float textAngle = atan2(pin2Local.Y - pin1Local.Y, pin2Local.X - pin1Local.X)
				* 45. / atan(1.);
			g->TranslateTransform(pin1Local.X, pin1Local.Y);
			g->RotateTransform(textAngle);

			// need to scale so that y-axis is down (otherwise text will be upside down)
			g->ScaleTransform(1, -1);

			// Create point for upper-left corner of text.
			PointF drawPoint = PointF(textSize * 2., -textSize / 2.);

			// Draw string to screen.
			g->DrawString(gcnew System::String(linkID.c_str()), drawFont, drawBrush, drawPoint);

			// scale back to our normal y-axis is up
			g->ScaleTransform(1, -1);

			// undo rotate and translate
			g->RotateTransform(-textAngle);
			g->TranslateTransform(-pin1Local.X, -pin1Local.Y);


		}

	}
	if (!useLocalCoords && getEffectiveLength() > 0.) {
		g->TranslateTransform(pin1Local.X, pin1Local.Y);
		g->RotateTransform(-rotationAngle);
		g->ScaleTransform(1 / scale, 1 / scale);
		g->TranslateTransform(-pin1Curr.X, -pin1Curr.Y);

		// for testing only, draw the bounding box
		//Point2D lowerBound = lowerBoundingBox();
		//Point2D upperBound = upperBoundingBox();

		//g->DrawRectangle(gcnew Pen(Color::Gray, 0.), lowerBound.X, lowerBound.Y,
		//	upperBound.X - lowerBound.X, upperBound.Y - lowerBound.Y);
	}

}

Point2D Link::getLocalFromCurr(Point2D worldCoords)
{
	// can only get this data if the link has local and current coordinates
	if (pin1Curr.X > -INFINITY && pin2Curr.X > -INFINITY && pin1Local.X > -INFINITY && pin2Local.X > -INFINITY) {

		// order of transformations was tough
		// essentially, same order as Link::paint, but opposite signs and scale

		// translate
		worldCoords.X -= pin1Curr.X; worldCoords.Y -= pin1Curr.Y;

		// scale
		float scale = Line2D::getLength(pin1Curr, pin2Curr)
			/ Line2D::getLength(pin1Local, pin2Local);
		worldCoords.X /= scale; worldCoords.Y /= scale;

		// rotate, keep angle in radians for easier calculations
		float angle = getRotAngleRadians();
		float newX = worldCoords.X * cos(-angle) - worldCoords.Y * sin(-angle);
		float newY = worldCoords.X * sin(-angle) + worldCoords.Y * cos(-angle);
		worldCoords.X = newX; worldCoords.Y = newY;

		// translate
		worldCoords.X += pin1Local.X; worldCoords.Y += pin1Local.Y;

		return worldCoords;
	}
	else
		return { -INFINITY, -INFINITY };

}

Point2D Link::getCurrFromLocal(Point2D shapeCoords)
{
	// can only get this data if the link has local and current coordinates
	if (pin1Curr.X > -INFINITY && pin2Curr.X > -INFINITY
		&& pin1Local.X > -INFINITY && pin2Local.X > -INFINITY) {

		// order of transformations was tough
		// essentially, same order as Link::paint, but using local

		// translate
		shapeCoords.X -= pin1Local.X; shapeCoords.Y -= pin1Local.Y;

		// scale
		float scale = Line2D::getLength(pin1Curr, pin2Curr) / Line2D::getLength(pin1Local, pin2Local);
		shapeCoords.X *= scale; shapeCoords.Y *= scale;

		// rotate, keep angle in radians for easier calculations
		float angle = getRotAngleRadians();
		float newX = shapeCoords.X * cos(angle) - shapeCoords.Y * sin(angle);
		float newY = shapeCoords.X * sin(angle) + shapeCoords.Y * cos(angle);
		shapeCoords.X = newX; shapeCoords.Y = newY;

		// translate
		shapeCoords.X += pin1Curr.X; shapeCoords.Y += pin1Curr.Y;

		return shapeCoords;
	}
	else
		return { -INFINITY, -INFINITY };

}

Point2D Link::lowerBoundingBox()
{
	if (geometry != nullptr) {
		Point2D geometryLow = getCurrFromLocal(geometry->lowerBoundingBox());
		Point2D geometryHigh = getCurrFromLocal(geometry->upperBoundingBox());
		return { min(geometryLow.X, geometryHigh.X), min(geometryLow.Y, geometryHigh.Y) };
	}
	else
		return { -INFINITY, -INFINITY };

}

Point2D Link::upperBoundingBox()
{
	if (geometry != nullptr) {
		Point2D geometryLow = getCurrFromLocal(geometry->lowerBoundingBox());
		Point2D geometryHigh = getCurrFromLocal(geometry->upperBoundingBox());
		return { max(geometryLow.X, geometryHigh.X), max(geometryLow.Y, geometryHigh.Y) };
	}
	else
		return { -INFINITY, -INFINITY };
}

int Link::nearestPin(Point2D testPoint, bool useLocalCoords)
{
	float radius;
	if (useLocalCoords) {
		radius = Line2D::getLength(pin1Local, pin2Local) / 24.;
		if (Line2D::getLength(pin1Local, testPoint) < radius)
			return 1;
		else if (Line2D::getLength(pin2Local, testPoint) < radius)
			return 2;
		else
			return -1;
	}
	else {
		radius = getEffectiveLength() / 24.;
		if (Line2D::getLength(pin1Curr, testPoint) < radius)
			return 1;
		else if (Line2D::getLength(pin2Curr, testPoint) < radius)
			return 2;
		else
			return -1;
	}
}

ostream& operator<<(ostream& os, const Link& aLink)
{
	os << "linkID: " << aLink.linkID << endl;
	os << "pin1Local: " << aLink.pin1Local.X << " " << aLink.pin1Local.Y << endl;
	os << "pin2Local: " << aLink.pin2Local.X << " " << aLink.pin2Local.Y << endl;
	os << "pin1Curr: " << aLink.pin1Curr.X << " " << aLink.pin1Curr.Y << endl;
	os << "pin2Curr: " << aLink.pin2Curr.X << " " << aLink.pin2Curr.Y << endl;
	os << "thickness: " << aLink.thickness << endl;
	os << "color: " << aLink.colorH << " " << aLink.colorS << " " << aLink.colorV << endl;
	if (aLink.geometry != nullptr) {
		os << "Shape Start:" << endl;
		os << *(aLink.geometry);
		os << "Shape End:" << endl;
	}
	return os;
}

#pragma once
#include "Link.h"
#include "InputMotion.h"

class Crank : public Link {
protected:
	InputMotion* itsMotion = nullptr;

public:
	void moveLink(Link* prevLink, Link* nextLink);

	void setMotion(InputMotion* aMotion) { itsMotion = aMotion; }
	InputMotion* getMotion() { return itsMotion; }
};

class Coupler : public Link {
public:
	void moveLink(Link* prevLink, Link* nextLink);
};

class Rocker : public Link {
public:
	void moveLink(Link* prevLink, Link* nextLink);
};
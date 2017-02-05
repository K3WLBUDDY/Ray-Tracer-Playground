#ifndef RAYH
#define RAYH

#include <iostream>
#include "sVector.h"

class ray
{
public:

	sVec::Vec3f A, B;

	ray(): A(0), B(0) {}
	ray(const sVec::Vec3f &a, const sVec::Vec3f &b) : A(a), B(b) {}

	sVec::Vec3f origin () const
	{
		return A;
	}

	sVec::Vec3f direction () const
	{
		return B;
	}

	sVec::Vec3f currentPos(float t) const
	{
		return A+B*t;
	}
	
};
#endif
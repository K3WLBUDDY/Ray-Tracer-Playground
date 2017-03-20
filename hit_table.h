#ifndef HITTABLEH
#define HITTABLEH

#include "ray.h"

struct hit_record
{
	float t;
	sVec::Vec3f p;//Hit Point on the Object
	sVec::Vec3f normal;//Normal from P

};

class hit_table
{
public:

	virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const=0;
};

#endif

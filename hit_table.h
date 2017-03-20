#ifndef HITTABLEH
#define HITTABLEH

#include "ray.h"

class material;


struct hit_record
{
	float t;
	sVec::Vec3f p;//Hit Point on the Object
	sVec::Vec3f normal;//Normal from P
	material *mat;

};



class hit_table
{
public:

	virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const=0;
};




#endif

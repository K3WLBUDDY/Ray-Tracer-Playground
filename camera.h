#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

class camera
{
public:
	camera()
	{
		 origin = sVec::Vec3f(0.0, 0.0 ,0.0);
		 vertical = sVec::Vec3f(0.0, 2.0, 0.0);
		 horizontal = sVec::Vec3f(4.0, 0.0, 0.0);
		 lower_left = sVec::Vec3f(-2.0, -1.0, -1.0);
	}

	ray get_ray(float u, float v)
	{
		return ray(origin , lower_left + horizontal*u + vertical*v - origin);
	}

	sVec::Vec3f origin;
	sVec::Vec3f vertical;
	sVec::Vec3f horizontal;
	sVec::Vec3f lower_left;
};

#endif

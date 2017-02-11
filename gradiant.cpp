#include <iostream>
#include <fstream>
#include "sVector.h"
#include "ray.h"
#include "sphere.h"

bool hit_sphere(const Vec3f& center, float radius, const ray& r)
{
	Vec3f oc = r.origin() - center;

	float a = dot(r.direction(), r.direction());
	float b = 2.0*dot(oc, r.direction());
	float c = dot(oc, oc) - radius*radius;
	float d = b*b -4*a*c;
	return(d>0);
}

sVec::Vec3f color(const ray &r)
{
	if (hit_sphere(Vec3f(0,0,-1), 0.5, r))
		return Vec3f(1,0,0);
	sVec::Vec3f unit_Dir = unit_vector(r.direction());
	float t = 0.5*(unit_Dir.y+1.0);

	//Standard Linear Interpolation. Research the fuck about it.
	return sVec::Vec3f(1.0, 1.0, 1.0)*(1.0-t)+ sVec::Vec3f(0.5,0.7,1.0)*t;
}

int main()
{
	int width=1920, height=1080;
	//sVec::Vec3f color;
	sVec::Vec3<int> rgb;
	sVec::Vec3f origin(0.0, 0.0 ,0.0);
	sVec::Vec3f vertical(0.0, 2.0, 0.0);
	sVec::Vec3f horizontal(4.0, 0.0, 0.0);
	sVec::Vec3f lower_left(-2.0, -1.0, -1.0);


	std::ofstream ofs("./gradiant_sphere.ppm",std::ios::out | std::ios::binary);

	ofs<<"P3\n"<<width<<" "<<height<<"\n255\n";


	for(int j=height-1;j>=0;j--)
		for(int i=0;i<width;i++)
		{

			//color.x = float(i)/float(width);
			//color.y =float(j)/float(width);

			float u = float(i)/float(width);
			float v= float(j)/float(height);

			ray r(origin, lower_left + horizontal*u + vertical*v);
			sVec::Vec3f col = color(r);
			//color.z = 0.5;

			/*
			float r=float(i)/float(width);
			float g=float(j)/float(height);
			float b=0.5;
			*/

			rgb.x=int(255.99*col.x);
			rgb.y=int(255.99*col.y);
			rgb.z=int(255.99*col.z);

			ofs<<rgb.x<<" "<<rgb.y<<" "<<rgb.z<<"\n";
		}
}

/*
	G++ Note - No need to specially link .h files as long as they're in the same wdir.

	Link .cpp files consecutively. 

	To search for include files in other dirs use -I <dir>
*/

/*Screen Coordinates : Lower Left Corner is the Origin */
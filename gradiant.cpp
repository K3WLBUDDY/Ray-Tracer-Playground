#include <iostream>
#include <fstream>
#include "sVector.h"
#include "ray.h"
#include "sphere.h"
#include "hit_table_list.h"
#include "hit_table.h"
#include <cfloat>
#include "camera.h"
#include "material.h"


sVec::Vec3f color(const ray &r, hit_table *world, int depth)
{
	hit_record rec;
	if(world->hit(r,0.001,FLT_MAX, rec))
	{

		ray scattered;
		Vec3f attenuation;

		if(depth<50 && rec.mat->scatter(r,rec,attenuation,scattered))
		{
			return attenuation*color(scattered, world, depth+1);
		}

		else
			return sVec::Vec3f(0,0,0);
	}

	else
	{
		sVec::Vec3f unit_Dir = unit_vector(r.direction());
		float t = 0.5*(unit_Dir.y+1.0);

		//Lerp for Background Gradiant
		return sVec::Vec3f(1.0, 1.0, 1.0)*(1.0-t)+ sVec::Vec3f(0.5,0.7,1.0)*t;
	}

}

int main()
{
	int width=1920, height=1080; //Initializing the Width and Height of the Final Image

	sVec::Vec3<int> rgb;

	hit_table *list[4];//Initializing a list of Objects containing 2 entries


	//Filling the list with 2 Spheres
	list[0] = new sphere(sVec::Vec3f(0,0,-1), 0.5, new lambertian(sVec::Vec3f(0.8, 0.8, 0.3)));
	list[1] = new sphere(sVec::Vec3f(0,-100.5,-1), 100, new lambertian(sVec::Vec3f(0.8, 0.8, 0.0)));
	list[2] = new sphere(sVec::Vec3f(1, 0, -1), 0.5, new metal(sVec::Vec3f(0.8, 0.6, 0.2)));
	list[3] = new sphere(sVec::Vec3f(-1, 0, -1), 0.5, new metal(sVec::Vec3f(0.8, 0.8, 0.8)));

	hit_table *world = new hit_table_list(list,4);// Initializing a for Objects that have been hit by the ray
	//Creating a File Stream
	std::ofstream ofs("./sphere6_metal.ppm",std::ios::out | std::ios::binary);

	ofs<<"P3\n"<<width<<" "<<height<<"\n255\n";

	//Initializing the Camera Classd
	camera cam;


	//Loop to iterate for each and every Pixel Width Wise Startring from Top Left
	for(int j=height-1;j>=0;j--)
		for(int i=0;i<width;i++)
		{

			sVec::Vec3f col(0,0,0); //The Initial Color Value for the Pixel

			//For loop for generating several Rays through a Pixel for AA
			for(int s=0;s<100; s++)
			{
				float u = float(i+drand48())/float(width);//drand48 returns a Number between 0.0 and 1.0
				float v = float(j+drand48())/float(height);
				ray r =cam.get_ray(u,v);
				sVec::Vec3f p =r.currentPos(2.0);
				col+=color(r,world,0); //Adds up all the colours obtained from the Sample Points
			}

			col = col/float(100);//Average of the Colours

			col = sVec::Vec3f(sqrt(col.x), sqrt(col.y), sqrt(col.z));//Gamma 2 Correction

			//Gets the Final RGB Value for the Pixels
			rgb.x=int(255.99*col.x);
			rgb.y=int(255.99*col.y);
			rgb.z=int(255.99*col.z);

			ofs<<rgb.x<<" "<<rgb.y<<" "<<rgb.z<<"\n";
		}
}

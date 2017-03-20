#include <iostream>
#include <fstream>
#include "sVector.h"
#include "ray.h"
#include "sphere.h"
#include "hit_table_list.h"
#include "hit_table.h"
#include <cfloat>
#include "camera.h"


//Diffuse Material
sVec::Vec3f random_in_unit_sphere()
{
	sVec::Vec3f p;
	do
	{
		p = sVec::Vec3f(drand48(), drand48(), drand48()) - sVec::Vec3f(1,1,1);
	}while(p.length_sq()>=1.0);

	return p;
}


sVec::Vec3f color(const ray &r, hit_table *world)
{
	hit_record rec;
	if(world->hit(r,0.001,FLT_MAX, rec))
	{
		//return 0.5*vec3(rec.normal.x()+1, rec.normal.y()+1, rec.normal.z()+1);

		//Diffuse Material
		sVec::Vec3f target = rec.p + rec.normal + random_in_unit_sphere();
		return color(ray(rec.p,  target-rec.p), world)*0.5;
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

	hit_table *list[2];//Initializing a list of Objects containing 2 entries


	//Filling the list with 2 Spheres
	list[0] = new sphere(sVec::Vec3f(0,0,-1), 0.5);
	list[1] = new sphere(sVec::Vec3f(0,-100.5,-1), 100);

	hit_table *world = new hit_table_list(list,2);// Initializing a for Objects that have been hit by the ray
	//Creating a File Stream
	std::ofstream ofs("./sphere5_diffuse_AA.ppm",std::ios::out | std::ios::binary);

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
				col+=color(r,world); //Adds up all the colours obtained from the Sample Points
			}

			col = col/float(100);//Average of the Colours

			col = sVec::Vec3f(sqrt(col.x), sqrt(col.y), sqrt(col.z));

			//Gets the Final RGB Value for the Pixels
			rgb.x=int(255.99*col.x);
			rgb.y=int(255.99*col.y);
			rgb.z=int(255.99*col.z);

			ofs<<rgb.x<<" "<<rgb.y<<" "<<rgb.z<<"\n";
		}
}

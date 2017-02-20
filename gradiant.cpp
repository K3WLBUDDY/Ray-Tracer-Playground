#include <iostream>
#include <fstream>
#include "sVector.h"
#include "ray.h"
#include "sphere.h"
#include "hit_table_list.h"
#include "hit_table.h"
#include <cfloat>
#include "camera.h"


sVec::Vec3f color(const ray &r, hit_table *world)
{
	hit_record rec;
	if(world->hit(r,0.0,FLT_MAX, rec))

		return sVec::Vec3f(rec.normal.x+1, rec.normal.y+1, rec.normal.z+1)*0.5;

	else
	{
		sVec::Vec3f unit_Dir = unit_vector(r.direction());
		float t = 0.5*(unit_Dir.y+1.0);
		return sVec::Vec3f(1.0, 1.0, 1.0)*(1.0-t)+ sVec::Vec3f(0.5,0.7,1.0)*t;
	}
	
}

int main()
{
	int width=1920, height=1080; //Initializing the Width and Height of the Final Image

	sVec::Vec3<int> rgb;

	hit_table *list[2];//Initializing a list of Objects


	//Initializing a list of Spheres with Center and Vertices
	list[0] = new sphere(sVec::Vec3f(0,0,-1), 0.5);
	list[1] = new sphere(sVec::Vec3f(0,-100.5,-1), 100);

	hit_table *world = new hit_table_list(list,2);

	//Creating a File Stream
	std::ofstream ofs("./sphere3_normal_AA.ppm",std::ios::out | std::ios::binary);

	ofs<<"P3\n"<<width<<" "<<height<<"\n255\n";

	//Initializing the Camera Class
	camera cam;


	//Loop to iterate for each and every Pixel Width Wise Startring from Top Left
	for(int j=height-1;j>=0;j--)
		for(int i=0;i<width;i++)
		{

			sVec::Vec3f col(0,0,0); //The Initial Color Value for the Pixel

			for(int s=0;s<100; s++)
			{
				float u = float(i+drand48())/float(width);
				float v = float(j+drand48())/float(height);
				ray r =cam.get_ray(u,v);
				sVec::Vec3f p =r.currentPos(2.0);
				col+=color(r,world);
			}
			col = col/float(100);

			//Gets the Final RGB Value for the Pixels
			rgb.x=int(255.99*col.x);
			rgb.y=int(255.99*col.y);
			rgb.z=int(255.99*col.z);

			ofs<<rgb.x<<" "<<rgb.y<<" "<<rgb.z<<"\n";
		}
}


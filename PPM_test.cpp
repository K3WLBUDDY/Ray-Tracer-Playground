#include <iostream>
#include <fstream>
#include "sVector.h"

int main()
{
	int width=1920, height=1080;
	sVec::Vec3f color;
	sVec::Vec3<int> rgb;

	std::ofstream ofs("./ppm_test.ppm",std::ios::out | std::ios::binary);

	ofs<<"P3\n"<<width<<" "<<height<<"\n255\n";


	for(int j=height-1;j>=0;j--)
		for(int i=0;i<width;i++)
		{

			color.x = float(i)/float(width);
			color.y =float(j)/float(width);
			color.z = 0.5;

			/*
			float r=float(i)/float(width);
			float g=float(j)/float(height);
			float b=0.5;
			*/

			rgb.x=int(255.99*color.x);
			rgb.y=int(255.99*color.y);
			rgb.z=int(255.99*color.z);

			ofs<<rgb.x<<" "<<rgb.y<<" "<<rgb.z<<"\n";
		}
}

/*
	G++ Note - No need to specially link .h files as long as they're in the same wdir.

	Link .cpp files consecutively. 

	To search for include files in other dirs use -I <dir>
*/
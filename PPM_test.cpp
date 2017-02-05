#include <iostream>
#include <fstream>
#include "sVector.h"

int main()
{
	int width=1920, height=1080;

	std::ofstream ofs("./ppm_test.ppm",std::ios::out | std::ios::binary);

	ofs<<"P3\n"<<width<<" "<<height<<"\n255\n";


	for(int j=height-1;j>=0;j--)
		for(int i=0;i<width;i++)
		{
			float r=float(i)/float(width);
			float g=float(j)/float(height);
			float b=0.5;

			int ir=int(255.99*r);
			int ig=int(255.99*g);
			int ib=int(255.99*b);

			ofs<<ir<<" "<<ig<<" "<<ib<<"\n";
		}
}
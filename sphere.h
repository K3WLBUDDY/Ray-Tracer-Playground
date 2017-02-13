#ifndef SPHERE_H
#define SPHERE_H

#include "sVector.h"
#include <cmath>
#include "hit_table.h"


using namespace sVec;

/*

class Sphere
{

	public:
		
    	Vec3f center;                          
    	float radius, radius2;                  
    	Vec3f surfaceColor, emissionColor;      
    	float transparency, reflection;  

        Sphere() {};       

        Sphere(const Vec3f &c, const float &r, const Vec3f &sc, const float &refl = 0, const float &transp = 0,  const Vec3f &ec = 0) : center(c), radius(r), radius2(r * r), surfaceColor(sc), emissionColor(ec), transparency(transp), reflection(refl) {}

    	bool intersect(const Vec3f &rayorig, const Vec3f &raydir, float &t0, float &t1) const
   		{

       		Vec3f l = center - rayorig;
        	float tca = l.dot(raydir);

        	if (tca < 0) 
        		return false;

        	float d2 = l.dot(l) - tca * tca;

        	if (d2 > radius2) 
        		return false;

        	float thc = sqrt(radius2 - d2);
        	t0 = tca - thc;
        	t1 = tca + thc;
        
        	return true;
    	}
};
#endif
*/

class sphere: public hit_table
{
public:
    Vec3f center;
    float radius;

    sphere(){};
    sphere(Vec3f c, float r): center(c), radius(r) {};
    virtual bool hit(const ray &r, float tmin, float tmax, hit_record& rec) const;
    
};

bool sphere::hit(const ray &r, float tmin, float tmax, hit_record& rec) const
{
    Vec3f oc = r.origin() - center;

    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius;
    float d = b*b -a*c;
    if(d>0)
    {
        float temp = (-b -sqrt(d))/a;
        if(temp<tmax && temp>tmin)
        {
            rec.t=temp;
            rec.p=r.currentPos(rec.t);
            rec.normal=(rec.p-center)/radius;
            return true;
        }   
        temp = (-b+sqrt(d))/a;
        if(temp<tmax && temp>tmin)
        {
            rec.t=temp;
            rec.p=r.currentPos(rec.t);
            rec.normal=(rec.p-center)/radius;
            return true;
        }
    }
        return false;
}

#endif
#ifndef SPHERE_H
#define SPHERE_H

#include "sVector.h"
#include <cmath>
#include "hit_table.h"


using namespace sVec;

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

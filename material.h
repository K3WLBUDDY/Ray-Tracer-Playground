#ifndef MATERIALH
#define MATERIALH

#include "ray.h"
#include "hit_table.h"
#include "hit_table_list.h"

struct hit_record;

class material
{
public:
	virtual bool scatter(const ray& r_in, const hit_record& rec, sVec::Vec3f& attenuation, ray& scattered) const =0;
};

//Generating a Randon Point in a Unit Sphere
sVec::Vec3f random_in_unit_sphere()
{
	sVec::Vec3f p;
	do
	{
		p = sVec::Vec3f(drand48(), drand48(), drand48()) - sVec::Vec3f(1,1,1);
	}while(p.length_sq()>=1.0);//Checks if the Generated Point is inside the Unit Sphere

	return p;
}

sVec::Vec3f reflect(const sVec::Vec3f& v, const sVec::Vec3f& n)
{
	return v - (n*dot(v,n))*2;
}

class lambertian : public material
{
public:

		lambertian(const sVec::Vec3f& a) : albedo(a) {}

		virtual bool scatter(const ray& r_in, const hit_record& rec, sVec::Vec3f& attenuation, ray& scattered) const
		{
			sVec::Vec3f target = rec.p + rec.normal + random_in_unit_sphere();
			scattered = ray(rec.p, target - rec.p);
			return true;
		}

		sVec::Vec3f albedo;
};

class metal : public material
{
public:
	metal(const sVec::Vec3f& a) : albedo(a) {}

	virtual bool scatter(const ray& r_in, const hit_record& rec, sVec::Vec3f& attenuation, ray& scattered) const
	{
		sVec::Vec3f reflected  = reflect(unit_vector(r_in.direction()), rec.normal);
		scattered = ray(rec.p, reflected);
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal)>0);
	}
	sVec::Vec3f albedo;

};



#endif

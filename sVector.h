#ifndef SVECTOR_H
#define SVECTOR_H

#include <iostream>
#include <cmath>

//To not mix with other vector libs
namespace sVec
{
	//Using templates to support generic datatypes
	template<typename T>
	class Vec3
	{
 		public:
  		// The three coordinates of the vector
 	 	T x,y,z;
		
  		//Using inline to reduce fn call overhead
		
		//Initializer list takes care of the default & parameterized
		//constructors
  		inline Vec3(): x(T(0)), y(T(0)), z(T(0)) {}
  	
  		inline Vec3(T val): x(val), y(val), z(val) {}

  		inline Vec3(T x_val, T y_val, T z_val): x(x_val), y(y_val), z(z_val) {}
		
		//Normalizes the vector i.e convert it to a unit vector by 
		//dividing it with its length
  		inline Vec3& normalize() 
  		{	

  			T nor_sq = length_sq();
  			if(nor_sq>0)
  			{
  				T invNor=1/sqrt(nor_sq);
  				x*=invNor, y*= invNor, z*=invNor;
  			}
  			return *this;
  		}

		//Using friend functions to avoid object dependent calls for 
		//commonly used ops
      		inline friend Vec3 unit_vector(Vec3<T> v)
      		{
        		return v/v.length();
      		}
		
		//Vec multiplication ops (Scalar)
 		inline Vec3<T> operator * (const T &f) const
  		{
  			return Vec3<T>(x*f, y*f, z*f);
  		}

  		inline Vec3<T> operator * (const Vec3<T> &v) const
  		{
  			return Vec3<T>(x*v.x, y*v.y, z*v.z);
  		}

		//Vec addition op
  		inline Vec3<T> operator + (const Vec3<T> &v) const
  		{
  			return Vec3<T>(x+v.x, y+v.y, z+v.z);
  		}
		
		//Vec subtraction ops
  		inline Vec3<T> operator - (const Vec3<T> &v) const
  		{
  			return Vec3<T>(x-v.x, y-v.y, z-v.z);
  		}
		
		//Vec negation
  		inline Vec3<T> operator -() const
 		{
  			return Vec3<T>(-x,-y,-z);
 		}
  		
		//Supporting shorthands
  		inline Vec3<T> operator += (const Vec3<T> &v) 
 		{
  			Vec3<T>(x+=v.x, y+=v.y, z+=v.z);
  			return *this;
 		}
  
 		inline Vec3<T> operator *= (const Vec3<T> &v)
  		{
  			Vec3<T>(x*=v.x, y*=v.y, z*=v.z);
  			return *this;
 		}
		
		//Division ops
      		inline Vec3<T> operator / (const Vec3<T> &v) const
      		{
        		return Vec3<T>(x/v.x, y/v.y, z/v.z);
      		}

      		inline Vec3<T> operator / (const T &f) const
      		{	
        		return Vec3<T>(x/f, y/f, z/f);
      		}

  		//Dot product ops
 		inline T dot(const Vec3<T> &v) const 
 		{ 
 			return x * v.x + y * v.y + z * v.z; 
 		} 

      
      		inline friend T dot(const Vec3<T> &a, const Vec3<T> &b)
      		{
        		return a.x*b.x + a.y*b.y + a.z*b.z;
      		}

		//Cross product ops
      		inline T cross(const Vec3<T> &v)const
      		{
        		return Vec3<T>((y*v.z-z*v.y), (-(x*v.z-z*v.x)), (x*v.y-y*v.x));
      		}
		
		//Returns the square of the Vec length
 		inline T length_sq() const
		{
			return x*x+y*y+z*z;
		}
		
		//Returns the actual length of the vec
 		inline T length() const
		{
			return sqrt(length_sq());
		}
		
		//IO operator overloaders
  		inline friend std::ostream & operator << (std::ostream &os, const Vec3<T> &v)
 		{
			os<< "["<<v.x<<" "<<v.y<<" "<<v.z<<"]";
			return os;
 		}

      		inline friend std::istream & operator >> (std::istream &is, const Vec3<T> &v)
      		{
        		is>>v.x>>v.y>>v.z;
      		}
	};

//Lazy typedef
typedef Vec3<float> Vec3f;
} 
#endif

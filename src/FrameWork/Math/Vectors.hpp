#pragma once
#include <math.h>

namespace Persist
{

template <typename T>
struct Vector3
{
    Vector3(T _x,T _y , T _z) : 
        x(_x),y(_y),z(_z)
    {
    }
    Vector3(const Vector3 & rhs) : 
        x(rhs.x) , y(rhs.y),z(rhs.z)
    {

    }

    T dot(const Vector3 & rhs)
    {
        return x*rhs.x + y * rhs.y + z * rhs.z;
    }
    T dot(const Vector3 & rhs) const
    {
        return x* rhs.x + y*rhs.y + z* rhs.z;
    }
    Vector3 operator *(const Vector3 & rhs)
    {
        return Vector3(x * rhs.x , y * rhs.y , z * rhs.z);
    }
    Vector3 operator*( T mul)
    {
        return Vector3(x *mul , y * mul , z * mul);
    }
    T length()
    {
        return sqrt(x*x + y*y + z*z);
    }
    Vector3 & normalize()
    {
        T len = length();
        if(len > 1e-6)
        {
            x/= len;
            y/= len;
            z/= len;
            return *this;
        }
        else 
        {
            throw Status::Error("normalize vector of length 0");
            return *this;
        }
    }



    //T x,y,z;
    union { T x , r ;};
    union { T y , g ;};
    union { T z , b ;};
};
using Vector3f = Vector3<float> ;

template <typename T>
struct Vector4 
{
    Vector4( T _x , T _y , T _z , T _w) :
        x(_x),y(_y),z(_z),w(_w)
    {

    }
    Vector4(const Vector4 & rhs) :
        x(rhs.x) , y (rhs.y) , z(rhs.z) ,w(rhs.z)
    {


    }


    union { T x,r; };
    union { T y,g; };
    union { T z,b; };
    union { T w,a; };
};
using Vector4f = Vector4<float>;

    
}
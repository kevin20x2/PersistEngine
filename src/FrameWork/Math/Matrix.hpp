#pragma once
#include "Vectors.hpp"


namespace Persist
{

// RightHanded Z Up
//https://www.mindcontrol.org/~hplus/graphics/matrix-layout.html
template <typename T>
class Matrix3x3
{

protected:
#ifdef DATA_TYPE_DX
union{
    T data_[9];
    T m11,m12,m13,m21,m22,m23,m31,m32,m33;
};
#else // OpenGL 
union {
    T data_[9];
    T m11,m21,m31,m12,m22,m32,m13,m23,m33;
};
#endif
};
using Matrix3x3f = Matrix3x3<float> ;


template <typename T>
class Matrix4x4
{

protected : 
#ifdef DATA_TYPE_DX
union {
    T data_[16];
    T m11,m12,m13,m14,m21,m22,m23,m24,m31,m32,m33,m34,m41,m42,m43,m44;
};
#else 
union {
    T data_[16];
    T m11,m21,m31,m41,m12,m22,m32,m42,m13,m23,m33,m43,m14,m24,m34,m44;
};
#endif
};
using Matrix4x4f = Matrix4x4<float>;


}

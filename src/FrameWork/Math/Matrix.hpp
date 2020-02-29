#pragma once
#include "Vectors.hpp"
#include "PersistMath.hpp"
#include <memory>


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


//TODO: SpeedUp
template <typename T>
class Matrix4x4
{
    public :
        static Matrix4x4 Identity ;  
        static Matrix4x4 scaleMatrix(const Vector3 <T> & scale)
        {
            Matrix4x4 ans;
            ans.nm_[0][0] = scale.x;
            ans.nm_[1][1] = scale.y;
            ans.nm_[2][2] = scale.z;
            return ans;
        }
        static Matrix4x4 translateMatrix(const Vector3 <T> & pos)
        {
            Matrix4x4 ans;
            ans.nm_[0][3] = pos.x;
            ans.nm_[1][3] = pos.y;
            ans.nm_[2][3] = pos.z;
            return ans;
        }
        //degree
        static Matrix4x4 rotationMatrix (const Vector3 <T> & rotation)
        {
            Vector3 <T> rot = rotation * Degree2Rad;
            Matrix4x4 rx ;
            rx.nm_[1][1] = cos(rot.x );
            rx.nm_[2][2] = cos(rot.x );
            rx.nm_[2][1] = sin(rot.x );
            rx.nm_[1][2] = -sin(rot.x);

            Matrix4x4 ry ;
            ry.nm_[0][0] = cos(rot.y);
            ry.nm_[2][2] = cos(rot.y);
            ry.nm_[2][0] = sin(rot.y);
            ry.nm_[0][2] = - sin(rot.y);

            Matrix4x4 rz ; 
            rz.nm_[0][0] = cos(rot.z);
            rz.nm_[1][1] = cos(rot.z);
            rz.nm_[1][0] = -sin(rot.z);
            rz.nm_[0][1] = sin(rot.z);

            // y ,x , z

            return ry * rx * rz ;


        }

        static Matrix4x4 viewMatrix(const Vector3<T> & translate , const Vector3<T> & rotation)
        {
            //Vector3<T> invRot(-rotaion.x , - rotation.y , - rotation.z);
            Vector3<T> invRot = - rotation * Degree2Rad;
            Matrix4x4 rx;
            rx.nm_[1][1] = cos(invRot.x);
            rx.nm_[2][2] = cos(invRot.x);
            rx.nm_[2][1] = sin(invRot.x);
            rx.nm_[1][2] = -sin(invRot.x);

            Matrix4x4 ry ;
            ry.nm_[0][0] = cos(invRot.y);
            ry.nm_[2][2] = cos(invRot.y);
            ry.nm_[2][0] = sin(invRot.y);
            ry.nm_[0][2] = - sin(invRot.y);

            Matrix4x4 rz ; 
            rz.nm_[0][0] = cos(invRot.z);
            rz.nm_[1][1] = cos(invRot.z);
            rz.nm_[1][0] = -sin(invRot.z);
            rz.nm_[0][1] = sin(invRot.z);

            // z , x, y
            Matrix4x4 rotMat = rz *rx *rz;

            Matrix4x4 transMat = translateMatrix(-translate);

            // Right Hand Z up 
            Matrix4x4 exchangeMat ;
            exchangeMat.m22 = 0 ;
            exchangeMat.m23 = 1 ;
            exchangeMat.m33 = 0 ;
            exchangeMat.m32 = 1;
            // OpenGL Right Hand Y up

            return exchangeMat *  rotMat * transMat;
        }



        Matrix4x4(const Matrix4x4 &rhs)
        {
            memcpy(data_, rhs.data_, sizeof(Matrix4x4));
        }
        Matrix4x4(const T array[16])
        {
            memcpy(data_, array, sizeof(Matrix4x4));
        }

        Matrix4x4() :
            Matrix4x4(Matrix4x4::Identity)
        {

        }

/*
        Matrix4x4(Matrix4x4 && rhs)
        {
            if(this != & rhs)
            {
                delete data_;
                data_ = nullptr;
                data_ = rhs.data_;
                rhs.data_ = nullptr;
            }
        }
        Matrix4x4 & operator= (Matrix4x4 && rhs)
        {
            if(this != & rhs)
            {
                delete data_;
                data_ = rhs.data_;
                rhs.data_ = nullptr;
            }

        }
        */

        Matrix4x4 mul(const Matrix4x4 & rhs)
        {
            Matrix4x4 ans ;
            for( int i = 0 ; i < 4 ; ++ i)
            {
                for(int j = 0 ; j < 4 ; ++ j)
                {
                    ans.nm_[i][j] = nm_[i][0] * rhs.nm_[0][j] + nm_[i][1]* rhs.nm_[1][j] + 
                                    nm_[i][2] * rhs.nm_[2][j] + nm_[i][3]*rhs.nm_[3][j];
                }

            }
            return ans;
        }
        Matrix4x4 operator* ( const Matrix4x4 & rhs)
        {
            return mul(rhs);
        }


//protected : 
#ifdef DATA_TYPE_DX
union {
    T data_[16];
    T nm_[4][4];
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

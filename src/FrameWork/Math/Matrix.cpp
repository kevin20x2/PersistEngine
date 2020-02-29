#include "Matrix.hpp"
namespace Persist
{
static constexpr float _tmp[] = 
                                              {1, 0, 0, 0,
                                              0, 1, 0, 0,
                                              0, 0, 1, 0,
                                              0, 0, 0, 1};

template <>
Matrix4x4 <float> Matrix4x4<float>::Identity = Matrix4x4<float>(_tmp);

/*
template <typename T>
Matrix4x4<T> Matrix4x4<T>::scaleMatrix(const Vector3<T> &scale)
{
  Matrix4x4 <T> ans;
  ans.nm_[0][0] = scale.x;
  ans.nm_[1][1] = scale.y;
  ans.nm_[2][2] = scale.z;
  return ans;
}
template <typename T>
Matrix4x4<T> Matrix4x4<T>::translateMatrix(const Vector3 <T> & pos)
{
    Matrix4x4<T> ans;
    ans.nm_[0][3] = pos.x;
    ans.nm_[1][3] = pos.y;
    ans.nm_[2][3] = pos.z;
    return ans;
}
//degree
template <typename T>
Matrix4x4<T> Matrix4x4<T>::rotationMatrix(const Vector3<T> &rotation)
{
    Vector3 <T> rot = rotation * Degree2Rad;
    Matrix4x4<T> rx ;
    rx.nm_[1][1] = cos(rot.x );
    rx.nm_[2][2] = cos(rot.x );
    rx.nm_[2][1] = sin(rot.x );
    rx.nm_[1][2] = -sin(rot.x);

    Matrix4x4<T> ry ;
    ry.nm_[0][0] = cos(rot.y);
    ry.nm_[2][2] = cos(rot.y);
    ry.nm_[2][0] = sin(rot.y);
    ry.nm_[0][2] = - sin(rot.y);

    Matrix4x4<T> rz ; 
    rz.nm_[0][0] = cos(rot.z);
    rz.nm_[1][1] = cos(rot.z);
    rz.nm_[1][0] = -sin(rot.z);
    rz.nm_[0][1] = sin(rot.z);

    // y ,x , z

    return ry * rx * rz ;

}

template <typename T>
Matrix4x4<T> Matrix4x4<T>::viewMatrix(const Vector3<T> &translate, const Vector3<T> &rotation)
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


template <typename T>
Matrix4x4<T> Matrix4x4<T>::mul(const Matrix4x4<T> & rhs)
{
    Matrix4x4<T> ans ;
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
*/

}
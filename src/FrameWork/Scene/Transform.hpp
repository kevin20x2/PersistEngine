#pragma once
#include <FrameWork/Math/Matrix.hpp>
namespace Persist
{

class Transform 
{
public:
    Transform() : 
    localPos_(Vector3f(0,0,0)), 
    worldMat_(Matrix4x4f::Identity),
    localRotation_(Vector3f(0,0,0)) ,
    localScale_(Vector3f(1,1,1))
    {
        updateWorldMat();
    }

    void updateWorldMat()
    {
        Matrix4x4f transMat = Matrix4x4f::translateMatrix(localPos_);
        Matrix4x4f rotationMat = Matrix4x4f::rotationMatrix(localRotation_);
        Matrix4x4f scaleMat = Matrix4x4f:: scaleMatrix(localScale_);
        worldMat_ = transMat * rotationMat * scaleMat;
    }


    void setLocalPosition(const Vector3f & pos)
    {
        localPos_ = pos;
        updateWorldMat();
    }
    void setLocalRotation(const Vector3f & rot)
    {
        localRotation_ = rot;
        updateWorldMat();
    }



    Vector3f localPosition() { return localPos_ ; }  
    Vector3f localRotation() { return localRotation_; } 
    Vector3f localScale() { return localScale_; }
    const Matrix4x4f & worldMatrix() { return worldMat_;}



private:
    Vector3f localPos_;
    Vector3f localRotation_ ;
    Vector3f localScale_ ;
    Matrix4x4f worldMat_ ;
};



}
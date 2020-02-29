#pragma once
#include "BaseComponent.hpp"
namespace Persist
{
class CameraComponent : public BaseComponent
{
    public : 
    CameraComponent(Unit * unit = nullptr ) : 
        BaseComponent(unit)
    {
        if(unit_ != nullptr)
        {
            pTransform_ = unit_->getComponent<TransformComponent>();
        }
        if(pTransform_)
        {
            updateViewMatrix();
        }
        updatePrjectionMat();
    }

    protected:
    void updateViewMatrix ()
    {
        if(pTransform_)
        {
           Vector3f rot =  pTransform_->transform().localRotation();
           Vector3f trans = pTransform_->transform().localPosition();
           viewMat_ = Matrix4x4f::viewMatrix(trans , rot);
        }

    }
    void updatePrjectionMat()
    {
        float cotHalfFov= 1.0f / tan(fov_/2);
        projMat_.m11 =  cotHalfFov / aspect_;
        projMat_.m22 = cotHalfFov;
        float FarMinusNear = farPlane_ - nearPlane_;
        projMat_.m33 = (farPlane_ + nearPlane_) / FarMinusNear;
        projMat_.m43 = -1.0f;
        projMat_.m34 = - 2.0 * farPlane_ * nearPlane_ / (FarMinusNear);



    }

    TransformComponent * pTransform_ = nullptr;
    float fov_ = 45.0f;
    float nearPlane_ = 1.0f;
    float farPlane_ = 100.f;
    float aspect_ = 1.0f;

    Matrix4x4f viewMat_;
    Matrix4x4f projMat_;


};

}
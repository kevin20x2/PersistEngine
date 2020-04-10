#pragma once
#include "BaseComponent.hpp"
#include <FrameWork/Unit/Unit.hpp>
#include <FrameWork/Math/Vectors.hpp>
#include <FrameWork/Math/Matrix.hpp>
#include <FrameWork/Unit/SceneUnit.hpp>
#include "TransformComponent.hpp"

namespace Persist
{
class CameraComponent : public BaseComponent
{
    public : 
    CameraComponent(Unit * unit = nullptr ) : 
        BaseComponent(unit),
        clearColor_(Vector4f(0.0f , 0.2f , 0.4f,1.0f))
    {
        if(unit_ != nullptr)
        {
            //pTransform_ = dynamic_cast<SceneUnit*> (unit_)->getTransformComponent();
            pTransform_ = unit_->getComponent<TransformComponent>();
        }
        if(pTransform_)
        {
            updateViewMatrix();
        }
        updatePrjectionMat();
    }
    public : 
    const Matrix4x4f & viewMat() { return viewMat_;}
    const Matrix4x4f & projectionMat() { return projMat_; }

    void render();
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

        float cotHalfFov= 1.0f / tan(fov_* Degree2Rad/2);
        projMat_.m11 =   cotHalfFov / aspect_;
        projMat_.m22 =  cotHalfFov;
        float FarMinusNear = farPlane_ - nearPlane_;
        //  z~ [0,1]
        projMat_.m33 = -1.0f *(farPlane_ ) / FarMinusNear;
        projMat_.m43 = -1.0f;
        projMat_.m34 = -  farPlane_ * nearPlane_ / (FarMinusNear);

        projMat_.print();




    }
    protected:

    TransformComponent * pTransform_ = nullptr;
    float fov_ = 60.0f;
    float nearPlane_ = 1.0f;
    float farPlane_ = 1000.f;
    float aspect_ = 0.8f;

    Matrix4x4f viewMat_;
    Matrix4x4f projMat_;
    Vector4f clearColor_ ;



};

}
#pragma once
#include <FrameWork/Math/Matrix.hpp>
namespace Persist
{

class Transform 
{
public:
    Transform() : 
    localPos_(Vector3f(0,0,0)), 
    worldMat_(Matrix4x4f::Identity)
    {

    }


private:
    Vector3f localPos_;
    Matrix4x4f worldMat_ ;
};



}
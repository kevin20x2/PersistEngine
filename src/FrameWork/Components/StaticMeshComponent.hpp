#pragma once
#include "BaseComponent.hpp"
#include <FrameWork/Geometry/Mesh.hpp>

namespace Persist
{
    class StaticMeshComponent : public BaseComponent
    {

        Mesh * mesh_;

    };

}


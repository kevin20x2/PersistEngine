#include "BaseRenderer.hpp"
#include "StaticMeshComponent.hpp"

namespace Persist
{
    class MeshRenderer : public IBaseRenderer
    {
        public : 
        MeshRenderer(Unit * unit = nullptr) :
            IBaseRenderer(unit)
        {
            meshComp_ = getComponent<StaticMeshComponent>();
        }

        virtual void _commit() override ;
        protected :
        // TODO : remove here
        StaticMeshComponent * meshComp_;

    };

}
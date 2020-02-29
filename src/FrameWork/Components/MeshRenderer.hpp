#include "BaseRenderer.hpp"

namespace Persist
{
    class MeshRenderer : public IBaseRenderer
    {
        public : 
        MeshRenderer(Unit * unit = nullptr) :
            IBaseRenderer(unit)
        {

        }

        protected :
        virtual void _render() override ;

    };

}
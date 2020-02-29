#include "BaseComponent.hpp"

namespace Persist
{
    interface IBaseRenderer : extends BaseComponent
    {
        public : 
        IBaseRenderer (Unit * unit = nullptr)  : 
            BaseComponent(unit)
        {

        }

        virtual ~IBaseRenderer() {}
        protected:
        virtual void _render() = 0 ;

    };

    
} // namespace nam

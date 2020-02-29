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
        virtual void _commit() = 0 ;
        protected:

    };

    
} // namespace nam

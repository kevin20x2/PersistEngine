#include "BaseComponent.hpp"

namespace Persist
{
    PERSIST_OBJECT()
    interface IBaseRenderer : extends BaseComponent
    {
        public : 
        IBaseRenderer (Unit * unit = nullptr)  : 
            BaseComponent(unit)
        {

        }

        virtual ~IBaseRenderer() {}
        virtual void _commit() {} ;
        protected:

    };

    
} // namespace nam

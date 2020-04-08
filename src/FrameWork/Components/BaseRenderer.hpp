#include "BaseComponent.hpp"

namespace Persist
{
    PERSIST_OBJECT()
    interface IBaseRenderer : extends BaseComponent
    {
        public : 
        REGISTER_CLASS(IBaseRenderer);
        IBaseRenderer (Unit * unit = nullptr)  : 
            BaseComponent(unit)
        {

        }

        virtual ~IBaseRenderer() {}
        virtual void _commit() {} ;
        protected:

    };

    
} // namespace nam

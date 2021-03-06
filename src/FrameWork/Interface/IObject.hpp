#pragma once
#include "Macro.hpp"
#include "Type.hpp"
#include "ObjectDefines.hpp"


namespace Persist
{
    
    PERSIST_OBJECT()
    interface IObject
    {
        
        public :
        using Super = void;
        using ThisType = IObject;
        virtual const Type * getType() { return typeOf<IObject>();}
        virtual ~IObject() {}

    };


}
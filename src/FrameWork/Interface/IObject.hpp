#pragma once
#include "Macro.hpp"
#include "Type.hpp"
#include "ObjectDefines.hpp"


namespace Persist
{
    
    interface IObject
    {
        
        public :
        using Super = void;
        using ThisType = IObject;
        virtual ~IObject() {}

    };


}
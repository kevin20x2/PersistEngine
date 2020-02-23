#pragma once
#include "Macro.hpp"
#include <FrameWork/Common/Status.hpp>

namespace Persist
{
    interface IRunTimeModule
    {

    public:
        virtual ~IRunTimeModule() {}

        virtual Status init() = 0 ; 

        virtual void tick() = 0 ;

        virtual void destroy() = 0 ;


    };

}


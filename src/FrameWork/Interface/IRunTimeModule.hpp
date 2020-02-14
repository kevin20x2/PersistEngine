#pragma once
#include "Macro.hpp"

namespace Persist
{
    interface IRunTimeModule
    {

    public:
        virtual ~IRunTimeModule() {}

        virtual int init() = 0 ; 

        virtual void tick() = 0 ;

        virtual void destroy() = 0 ;


    };

}


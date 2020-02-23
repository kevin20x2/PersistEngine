#pragma once
#include "IRunTimeModule.hpp"

namespace Persist {

    interface IApplication :  extends IRunTimeModule
    {

        public : 

        static IApplication * currentApplication();



        virtual ~IApplication() {}

        virtual Status init() = 0 ;

        virtual void destroy() = 0 ;

        virtual void tick() = 0;

        virtual bool isQuit() = 0;

        private : 
        static IApplication * current_application_;

    };
}

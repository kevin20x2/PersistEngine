#pragma once

#include <FrameWork/Interface/ObjectDefines.hpp>
#ifndef DYNAMIC_REGISTER_CLASS

#define DYNAMIC_REGISTER_CLASS(className) class className ; 
namespace Persist{
class IObject ;

#include "../../../dynamicObjectInit.inc"
}
#endif


#ifdef DYNAMIC_REGISTER_CLASS
    #undef  DYNAMIC_REGISTER_CLASS
    #define DYNAMIC_REGISTER_CLASS(className) registerClass<Persist::className>();
#else
    #define DYNAMIC_REGISTER_CLASS(className) registerClass<Persist::className>();
#endif 


void dynamicRegisterAllClass()
{
    registerClass <Persist ::IObject>();

#include "../../../dynamicObjectInit.inc"

}

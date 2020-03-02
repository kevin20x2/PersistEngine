#pragma once
#include "RHIDefines.hpp"


namespace Persist
{

struct RHIDepthStencilStateInitializer
{
    bool enableDepthWrite = true;
    EnumAsByte <ENMCompareFunctionType> depthCompFunc = CFT_Less ;


};

}
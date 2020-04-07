#pragma once
#include <FrameWork/Common/String.hpp>
#include <FrameWork/Unit/SceneUnit.hpp>


namespace Persist
{

class BaseImporter 
{
    public : 
    virtual SceneUnit * loadFromDisk(const String &  path) = 0 ; 

};

}
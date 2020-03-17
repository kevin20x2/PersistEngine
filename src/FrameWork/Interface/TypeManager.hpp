#pragma once
#include "Type.hpp"
namespace Persist
{

class TypeManager
{
    public : 
    static TypeManager * Get() ;

    void registerAllClass();
    void registerClass(const TypeRegisterDesc & desc );

    
};

}
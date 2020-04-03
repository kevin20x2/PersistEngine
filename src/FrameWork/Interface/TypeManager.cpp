#include "TypeManager.hpp"
#include <FrameWork/Type/DynamicRegisterClass.hpp>
#include <iostream>

namespace Persist
{
    TypeManager * TypeManager::Get()
    {
        static TypeManager local;
        return &local;
    }
    void TypeManager::registerClass(const TypeRegisterDesc & desc)
    {
        RTTI & value = * desc.value;
        value = desc.desc;
    }
    void TypeManager::registerAllClass()
    {
        dynamicRegisterAllClass();
    }


};

void GlobalRegisterType(const Persist::TypeRegisterDesc & desc)
{
    Persist::TypeManager::Get()->registerClass(desc);
    std::cout << desc.value->className <<std::endl;

}
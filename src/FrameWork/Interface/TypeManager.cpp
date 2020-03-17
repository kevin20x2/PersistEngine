#include "TypeManager.hpp"

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


};

void GlobalRegisterType(const Persist::TypeRegisterDesc & desc)
{
    Persist::TypeManager::Get()->registerClass(desc);

}
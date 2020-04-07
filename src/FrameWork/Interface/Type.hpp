#pragma once

namespace Persist
{

class IObject ;

// --------------------------------------------------------------------
// pod type
struct RTTI 
{
    enum { DefaultTypeID = -1 };

    const RTTI * father;
    const char * className;
    const char * namespaceName;
    int size;
    int typeID;
};

template <typename T>
struct RTTI_Container 
{
    static RTTI rtti; 
};

#define PE_RTTI_DEFAULT_INITLIST { nullptr , "[Unregistered]" , "" , -1 , -1 }

template <typename T>
RTTI RTTI_Container<T>::rtti = PE_RTTI_DEFAULT_INITLIST;

// --------------------------------------------------------------------

class Type 
{

    public:
    const char * className() const { return interal_.className; }
    const char * namespaceName() const { return interal_.namespaceName; }


    private : 
    RTTI interal_;
};
    


template <typename T>
const Type * typeOf() { 
    //typeInitializer<T>::Initializer.do_nothing();
    return reinterpret_cast<const Type *>( & RTTI_Container<T>::rtti); }

template <typename T>
bool isTypeOf(IObject * obj)
{
    return obj->getType() == typeOf<T>();
}


struct TypeRegisterDesc
{
    RTTI desc;
    RTTI * value;
};

template <typename T>
class typeInitializer
{
public: 
    inline void do_nothing() const {}
    typeInitializer()
    {
        registerClass<T>();
    }
    virtual ~typeInitializer(){ }
    static typeInitializer<T> Initializer; 
};
template <typename T>
typeInitializer<T> typeInitializer<T>::Initializer;

};

// --------------------------------------------
#include <functional>
#include <string>
namespace std
{
    
    template <>
    struct hash <Persist::Type>
    {
        public : 
        size_t operator()(const Persist::Type & type) const
        {
            std::string tmp = std::string(type.className()) + std::string(type.namespaceName());
            std::hash <std::string >  h ;
            return  h(tmp);
        }

    };
    
} // namespace name




#pragma once

namespace Persist
{



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
    const char * className() { return interal_.className; }


    private : 
    RTTI interal_;
};
    


template <typename T>
Type * typeOf() { 
    //typeInitializer<T>::Initializer.do_nothing();
    return reinterpret_cast <Type *>( & RTTI_Container<T>::rtti); }


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


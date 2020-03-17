#pragma once
#include "Type.hpp"

// -------------------------------
#define REGISTER_CLASS(TYPE_NAME_) \
public : \
    using Super = ThisType ; \
    using ThisType = TYPE_NAME_ ; \
    virtual Type * getType() { return typeOf<TYPE_NAME_>(); } \
    /*static typeInitializer<TYPE_NAME_> initializer_;*/\
    class MISSING_SEMICOLON_AFTER_REGISTER_CLASS_MACRO  


//---------------------------------------------------

template<typename T>
void registerClass();

//-----------------------------------------

#define PERSIST_IMPLEMENT_CLASS(TYPE_NAME_,ID_) IMPLEMENT_CLASS(Persist,TYPE_NAME_,ID_)


#define IMPLEMENT_CLASS(NAME_SPACE_,TYPE_NAME_,ID_) \
static Persist::TypeRegisterDesc NAME_SPACE_##TYPE_NAME_##ID_##DESC = {\
    {\
        &Persist::RTTI_Container <NAME_SPACE_::TYPE_NAME_::Super>::rtti,\
        #TYPE_NAME_,\
        #NAME_SPACE_,\
        sizeof(NAME_SPACE_::TYPE_NAME_),\
        Persist::RTTI::DefaultTypeID\
    },\
    &Persist::RTTI_Container <NAME_SPACE_::TYPE_NAME_>::rtti\
};\
template <>\
void registerClass<NAME_SPACE_::TYPE_NAME_>()\
{\
    Persist::TypeRegisterDesc & desc = NAME_SPACE_##TYPE_NAME_##ID_##DESC ;\
    void GlobalRegisterType(const Persist::TypeRegisterDesc & desc);\
    GlobalRegisterType(desc);\
}\




    


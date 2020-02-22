#pragma once
#include <FrameWork/Interface/Macro.hpp>
#include <FrameWork/Common/String.hpp>
#include <FrameWork/Common/Status.hpp>


namespace Persist
{

#define SERIALIZE (Name) \
public : \
virtual const String & getName() { return #Name; }\


interface ISerializeable 
{
    public : 
    virtual const String &  getName () = 0;
    template <typename TransferFunc>
    Status transfer(TransferFunc func) = 0 ;

};




}
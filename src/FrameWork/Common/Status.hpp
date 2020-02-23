#pragma once
#include "String.hpp"
#include <iostream>

namespace Persist
{

class Status 
{
    public : 

    enum StatusType
    {
        OK  = 0,
        InvalidArg = 1,
        CommonErr = 2
    };

    Status(StatusType type) : 
        value(type)
    {
    }

    static Status Error( StatusType type )
    {
        return Status(type);
    }
    static Status  Error(const String & err)
    {
        std::cout << err << std::endl;
        return Status(CommonErr);

    }
    static Status Ok()
    {
        return Status(OK);
    }
    StatusType value;

};


}
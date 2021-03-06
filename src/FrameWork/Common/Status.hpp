#pragma once
#include "String.hpp"
#include <iostream>
#include "Logger.hpp"

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
        PLOG() << err << PEND;
        return Status(CommonErr);

    }
    static Status Ok()
    {
        return Status(OK);
    }
    StatusType value;

};


}
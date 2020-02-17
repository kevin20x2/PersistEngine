#pragma once

namespace Persist
{

class Status 
{
    public : 

    enum StatusType
    {
        OK  = 0,
        InvalidArg = 1
    };

    Status(StatusType type) : 
        value(type)
    {
    }

    static Status Error( StatusType type )
    {
        return Status(type);
    }
    StatusType value;

};


}
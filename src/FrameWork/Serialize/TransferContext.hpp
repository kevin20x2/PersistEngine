#pragma once
#include <FrameWork/Common/Status.hpp>
#include <FrameWork/Common/String.hpp>

namespace  Persist
{

class TransferContext 
{
    public : 
    template <typename Type>
    static  Status addReadRequest(const String & path , Type & dst ) ;

};
    

}

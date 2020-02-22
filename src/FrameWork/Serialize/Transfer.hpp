#pragma once
#include <FrameWork/Common/String.hpp>
#include <fstream>


namespace Persist
{

#define TRANSFER(Name) transfer.transfer(#Name ,Name) ; 

struct ReadTransferBase
{
    template <typename Type>
    void transfer(const String & fieldName , Type & value ) ;

    ReadTransferBase(std::ifstream * ifs) :
    ifs_(ifs)
    {

    }

    std::ifstream * ifs_;

};


}
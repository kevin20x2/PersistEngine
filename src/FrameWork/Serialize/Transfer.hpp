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
    using byte_ifstream = std::basic_ifstream<uint8_t ,std:: char_traits<uint8_t>>;

    ReadTransferBase(byte_ifstream* ifs) :
    ifs_(ifs)
    {

    }

    byte_ifstream *ifs_;
};


}
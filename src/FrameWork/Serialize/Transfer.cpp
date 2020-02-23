#include "Transfer.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <FrameWork/Shaders/SerializeShaderData.hpp>
namespace Persist
{

template <typename Type>
void ReadTransferBase :: transfer(const String & name ,Type & value) 
{

// default do nothing
}

template <>
void ReadTransferBase :: transfer <ArrayBuffer>(const  String & name ,ArrayBuffer & buffer) 
{
    //ifs_->seekg(0, std::ios_base::end);
    //uint32_t fileSize = ifs_->tellg(); 
    //ifs_->seekg(0,std::ios_base::beg);

/*
    buffer.reserve(fileSize);
    if(fileSize > 0)
    {
        ifs_->read(buffer.data(),sizeof(uint8_t) * fileSize);
    }
    */


    std::copy( std::istreambuf_iterator<uint8_t>(*ifs_) , std::istreambuf_iterator<uint8_t>(),
    std::back_inserter(buffer)
    );


}


}
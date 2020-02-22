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
    std::copy( std::istreambuf_iterator<char>(*ifs_) , std::istreambuf_iterator<char>(),
    std::back_inserter(buffer)
    );


}


}
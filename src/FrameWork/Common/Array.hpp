#pragma once
#include <vector>
#include <FrameWork/Interface/Macro.hpp>
#include <unordered_map>



namespace Persist 
{
    // not sure is need do it myself so just extend std
    
    template <typename T>
    class Array : extends std::vector
    {

    };
    
    template <typename T>
    class HashMap : extends std::unordered_map
    {

    };


    

};
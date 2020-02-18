#pragma once
#include <vector>
#include <FrameWork/Interface/Macro.hpp>
#include <unordered_map>
#include <memory>



namespace Persist 
{
    // not sure is need do it myself so just extend std
    
    template <typename T , class Alloc = std::allocator <T> >
    using Array  =   std::vector <T ,Alloc>;

    
    template <typename Key , typename Value>
    class HashMap : extends std::unordered_map <Key,Value>
    {

    };


    

};
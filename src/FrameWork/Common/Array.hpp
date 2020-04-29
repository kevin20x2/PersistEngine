#pragma once
#include <vector>
#include <FrameWork/Interface/Macro.hpp>
#include <unordered_map>
#include <memory>



namespace Persist 
{
    // not sure is need do it myself so just extend std
    
    template <typename T , class Alloc = std::allocator <T> >
    //using Array  =   std::vector <T ,Alloc>;
    class Array : extends std::vector <T , Alloc >
    {
        public :
        // just copy from std::vector
        explicit Array ()
             {} 
        explicit Array (size_type n ,const value_type & val = value_type() ,
            const allocator_type & alloc = allocator_type()
        ) : std::vector (n ,val , alloc) {}


        Array(const Array & x) : 
        std::vector( x ) {}
        
        Array(std :: initializer_list <T> _list , const allocator_type & alloc = allocator_type()) :
            std::vector<T ,Alloc>(_list, alloc)
         {}






        uint32_t add(const T &  value)
        {
            push_back(value);
            return size() - 1;
        }

    };


    template <typename Key ,typename Value>
    using Pair  = std::pair <Key ,Value>;
    
    template <typename Key , typename Value>
    class HashMap : extends std::unordered_map <Key,Value>
    {

    };


    

};
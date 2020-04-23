#pragma once
#include <memory>

namespace Persist
{

class Memory 
{
    public : 

    static void Memcpy(void * dst , const void * src , size_t size)
    {
        ::memcpy(dst,src,size);
    }



};

}
#pragma once
#include <FrameWork/Common/Status.hpp>
#include <FrameWork/Common/String.hpp>


namespace Persist
{

//namespace IO
//{
    enum class IOMode :  uint8_t
    {
        IOM_Binary,
        IOM_Text 
    };

//}

class FileReader
{
    public : 

    FileReader(const String & fileName , IOMode mode = IOMode::IOM_Text );
    virtual ~FileReader();
    Status read(String & buf );
    private : 
    struct Rep;
    Rep * rep_ = nullptr;
};

}
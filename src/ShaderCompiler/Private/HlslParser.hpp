#pragma once
#include <FrameWork/Common/String.hpp>
#include "HlslCompileInfo.hpp"

namespace Persist
{

class HlslParser
{
    public : 
    HlslParser();


    bool parse(String & inSource , HlslCompileInfo & compileInfo);
};


}

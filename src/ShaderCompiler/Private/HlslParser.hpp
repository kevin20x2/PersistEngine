#pragma once

#include <FrameWork/Common/String.hpp>
#include <FrameWork/Common/Array.hpp>
#include "HlslToken.hpp"
#include "HlslCompileInfo.hpp"

namespace Persist
{

class HlslParser
{
    public : 
    HlslParser();


    bool parse(String & inSource , HlslCompileInfo & compileInfo);

    inline void addToken(const HlslToken &  token , const struct HlslTokenizer & tokenizer);

    private:


    Array <String > fileNames_;
    Array <HlslToken> tokens_;


};


}

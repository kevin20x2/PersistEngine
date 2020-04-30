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



    inline void addToken(const HlslToken &  token , const struct HlslTokenizer & tokenizer);

    bool prase(String & inSource , String &fileName , HlslCompileInfo & compileInfo);

    void Debug_Print();

    struct TokenHandler;


    private:
    bool tokenize(String & inSource , HlslCompileInfo & compileInfo);


    Array <String > fileNames_;
    Array <HlslToken> tokens_;
    TokenHandler * tokenHandler_ = nullptr;


};


}

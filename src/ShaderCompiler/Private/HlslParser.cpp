#include "HlslParser.hpp"
#include "HlslAST.hpp"


namespace Persist
{


struct HlslParser::TokenHandler 
{
    const Array <String > & fileNames_;
    const Array <HlslToken> & tokens_;

    TokenHandler(const Array <String > & fileName , const Array <HlslToken> & tokens) :
        fileNames_(fileName), tokens_(tokens)
    {

    }

    bool hasMoreTokens() const
    {
        return current_ < tokens_.size();
    }
    const HlslToken * peekToken(uint32_t delta = 0 ) const 
    {
        if(current_ + delta < tokens_.size())
        {
            return & tokens_[current_ + delta];
        }
        return nullptr;

    }
    bool matchToken(ENMHlslToken token)
    {
        const HlslToken * current = peekToken();

        if( current != nullptr && current->token_ == token)
        {
            ++current_;
            return true;

        }
        return false;
    }

    void sourceError(const String & info)
    {
        PLOG() << info <<PEND;

    }

    
    int current_ = 0; 



};

enum ENMParseResult
{
    Matched,
    NotMatched,
    Error
};

ENMParseResult ParseCBuffer(HlslParser ::TokenHandler & tokenHandler ,AST::Node ** ppNode)
{
    //if(tokenHandler.peekToken()->token_ != ENMHlslToken::LeftBrace)
   
    AST::CBufferDeclaration * cbuffer = new AST::CBufferDeclaration();

    const HlslToken *token = tokenHandler.peekToken();
    if(tokenHandler.matchToken(ENMHlslToken ::Identifier))
    {
        cbuffer->name_ = token->string_.toCharArray();
    }
    if (!tokenHandler.matchToken(ENMHlslToken::LeftBrace)) // {
    {
        tokenHandler.sourceError(String("expect '{' !"));
        return ENMParseResult::Error;
    }


}


ENMParseResult TryParseUnit( HlslParser :: TokenHandler & tokenHandler , AST::Node ** ppNode )
{
    if(tokenHandler.matchToken(ENMHlslToken ::CBuffer))
    {
        ENMParseResult result = ParseCBuffer(tokenHandler,ppNode);

        if(result == ENMParseResult::Matched || result == ENMParseResult::Error)
        {
            return result;
        }

    }

    return ENMParseResult::Matched;

}


HlslParser ::HlslParser() : 
    tokenHandler_(new TokenHandler(fileNames_,tokens_))
{


}


bool HlslParser::prase(String & inSource, String & fileName , HlslCompileInfo & compileInfo )
{

    if(!tokenize(inSource ,compileInfo ))
    {
        return false;
    }
    Array <AST::Node * > nodes ; 
    TokenHandler & tokenHandler = *tokenHandler_;

    while(tokenHandler.hasMoreTokens())
    {


    }



}




}
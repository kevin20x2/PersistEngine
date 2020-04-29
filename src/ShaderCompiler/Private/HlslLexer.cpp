#include "HlslToken.hpp"
#include "HlslParser.hpp"
#include <FrameWork/Common/String.hpp>
#include <FrameWork/Common/Logger.hpp>
#include "gtest/gtest.h"
namespace Persist
{

struct TrieTree
{

    struct TrieNode 
    {
        //Array <Pair <char , TrieNode * > > edge ;
        HashMap <char ,  TrieNode * > edge;
        ENMHlslToken token = ENMHlslToken::Invalid;
    };


    TrieNode * root ;

    TrieTree()  :
    root(new TrieNode())
    {
    }

    void insert(const String & symbol , ENMHlslToken token )
    {
        TrieNode * current = root;
        int len = symbol.length();
        for(int i = 0 ;i <len ; ++ i )
        {
            char ch = symbol[i];
            if(current->edge.find(ch ) == current->edge.end())
            {
                current->edge[ch] = new TrieNode();
            }
            current = current->edge[ch];
        }
        current->token = token;
    }
    bool find(const char * value , ENMHlslToken & token, String & outSymbol)
    {
        TrieNode * current = root;
        const char * ptr = value;

        while(ptr  && current->edge.find(*ptr) != current->edge.end())
        {
            current = current->edge[*ptr];
            ++ptr ;
        }


        if(current->token != ENMHlslToken::Invalid)
        {
            outSymbol = String(value , ptr);
            token = current->token ;
            return true;
        }
        return false;

    }
    bool isSymbol(const String & value ,ENMHlslToken & token )
    {
        TrieNode * current = root;

        int len = value.length();
        for(int i = 0 ;i < len ; ++i)
        {
            if(current->edge.find(value[i] ) != current->edge.end())
            {
                current = current->edge[value[i]];
            }
            else 
            {
                return false;
            }
        }
        if(current->token != ENMHlslToken::Invalid)
        {
            token = current->token;
            return true;
        }
        return false;
    }


} StaticTrieTree;

static void  addToken(const String & symbol , ENMHlslToken token)
{
    StaticTrieTree.insert(symbol , token);
}


static struct TrieTreeInitializer
{
    TrieTreeInitializer()
    {
        addToken("+" , ENMHlslToken::Plus);
        addToken("+=" , ENMHlslToken::PlusEqual);
        addToken("-" ,ENMHlslToken::Minus);
        addToken("-=" , ENMHlslToken::MinusEqual);
        addToken("*" , ENMHlslToken::Times);
        addToken("*=" , ENMHlslToken::TimesEqual);
        addToken("/" , ENMHlslToken::Div);
        addToken("/=" ,ENMHlslToken ::DivEqual);
        addToken("%" , ENMHlslToken::Mod);
        addToken("%=" ,ENMHlslToken::ModEqual);
        addToken("(" , ENMHlslToken ::LeftParenthesis);
        addToken(")", ENMHlslToken::RightParenthesis);


        addToken("==",ENMHlslToken::EqualEqual);
        addToken("!=" ,ENMHlslToken::NotEqual);
        addToken("<", ENMHlslToken::Lower);
        addToken("<=" ,ENMHlslToken::LowerEqual);
        addToken(">", ENMHlslToken::Greater);
        addToken(">=",ENMHlslToken::GreaterEqual);
        addToken("&&" ,ENMHlslToken::AndAnd);
        addToken("||",ENMHlslToken ::OrOr );

        addToken("=",ENMHlslToken::Assign);
        addToken("{", ENMHlslToken::LeftBrace);
        addToken("}",ENMHlslToken::RightBrace);
        addToken(";",ENMHlslToken:: Semicolon);
        addToken("if", ENMHlslToken::If);
        addToken("else" ,ENMHlslToken ::Else);
        addToken("for", ENMHlslToken::For);
        addToken("while",ENMHlslToken::While);
        addToken("do",ENMHlslToken::Do);
        addToken("return", ENMHlslToken::Return);
        addToken("switch",ENMHlslToken::Switch);
        addToken("case",ENMHlslToken::Case);
        addToken("break", ENMHlslToken::Break);
        addToken("default", ENMHlslToken::Default);
        addToken("continue",ENMHlslToken::Continue );
        addToken("goto",ENMHlslToken::Goto);

        addToken("++",ENMHlslToken::PlusPlus);
        addToken("--",ENMHlslToken::MinusMinus);


        addToken("void",ENMHlslToken::Void);
        addToken("const",ENMHlslToken::Const);
        addToken("precise",ENMHlslToken::Precise);

        addToken("bool",ENMHlslToken::Bool);
        //addToken("bool1",ENMHlslToken ::Bool1);

        addToken("int",ENMHlslToken::Int);
        addToken("int1",ENMHlslToken::Int1);
        addToken("int2",ENMHlslToken::Int2);
        addToken("int3",ENMHlslToken::Int3);
        addToken("int4",ENMHlslToken::Int4);

        addToken("int1x1",ENMHlslToken::Int1x1);
        addToken("int2x1",ENMHlslToken::Int2x1);
        addToken("int3x1",ENMHlslToken::Int3x1);
        addToken("int4x1",ENMHlslToken::Int4x1);

        addToken("int1x2",ENMHlslToken::Int1x2);
        addToken("int2x2",ENMHlslToken::Int2x2);
        addToken("int3x2",ENMHlslToken::Int3x2);
        addToken("int4x2",ENMHlslToken::Int4x2);

        addToken("int1x3",ENMHlslToken::Int1x3);
        addToken("int2x3",ENMHlslToken::Int2x3);
        addToken("int3x3",ENMHlslToken::Int3x3);
        addToken("int4x3",ENMHlslToken::Int4x3);

        addToken("int1x4",ENMHlslToken::Int1x4);
        addToken("int2x4",ENMHlslToken::Int2x4);
        addToken("int3x4",ENMHlslToken::Int3x4);
        addToken("int4x4",ENMHlslToken::Int4x4);
        
        addToken("half", ENMHlslToken::Half);

        addToken("half1",ENMHlslToken::Half1);
        addToken("half2",ENMHlslToken::Half2);
        addToken("half3",ENMHlslToken::Half3);
        addToken("half4",ENMHlslToken::Half4);

        addToken("half1x1",ENMHlslToken::Half1x1);
        addToken("half2x1",ENMHlslToken::Half2x1);
        addToken("half3x1",ENMHlslToken::Half3x1);
        addToken("half4x1",ENMHlslToken::Half4x1);

        addToken("half1x2",ENMHlslToken::Half1x2);
        addToken("half2x2",ENMHlslToken::Half2x2);
        addToken("half3x2",ENMHlslToken::Half3x2);
        addToken("half4x2",ENMHlslToken::Half4x2);


        addToken("half1x3",ENMHlslToken::Half1x3);
        addToken("half2x3",ENMHlslToken::Half2x3);
        addToken("half3x3",ENMHlslToken::Half3x3);
        addToken("half4x3",ENMHlslToken::Half4x3);

        addToken("half1x4",ENMHlslToken::Half1x4);
        addToken("half2x4",ENMHlslToken::Half2x4);
        addToken("half3x4",ENMHlslToken::Half3x4);
        addToken("half4x4",ENMHlslToken::Half4x4);

        addToken("float", ENMHlslToken::Float);

        addToken("float1", ENMHlslToken::Float1);
        addToken("float2", ENMHlslToken::Float2);
        addToken("float3", ENMHlslToken::Float3);
        addToken("float4", ENMHlslToken::Float4);

        addToken("float1x1", ENMHlslToken::Float1x1);
        addToken("float1x2", ENMHlslToken::Float1x2);
        addToken("float1x3", ENMHlslToken::Float1x3);
        addToken("float1x4", ENMHlslToken::Float1x4);

        addToken("float2x1", ENMHlslToken::Float2x1);
        addToken("float2x2", ENMHlslToken::Float2x2);
        addToken("float2x3", ENMHlslToken::Float2x3);
        addToken("float2x4", ENMHlslToken::Float2x4);

        addToken("float3x1", ENMHlslToken::Float3x1);
        addToken("float3x2", ENMHlslToken::Float3x2);
        addToken("float3x3", ENMHlslToken::Float3x3);
        addToken("float3x4", ENMHlslToken::Float3x4);

        addToken("float4x1", ENMHlslToken::Float4x1);
        addToken("float4x2", ENMHlslToken::Float4x2);
        addToken("float4x3", ENMHlslToken::Float4x3);
        addToken("float4x4", ENMHlslToken::Float4x4);

        addToken("texture" ,ENMHlslToken :: Texture);
        addToken("texture2D" ,ENMHlslToken :: Texture2D);
        addToken("texture3D" ,ENMHlslToken :: Texture3D);

        addToken("sampler",ENMHlslToken :: Sampler);
        addToken("sampler2D",ENMHlslToken :: Sampler2D);

        addToken("in",ENMHlslToken::In);
        addToken("out", ENMHlslToken::Out);
        addToken("inout",ENMHlslToken::InOut);
        addToken("static", ENMHlslToken::Static);
        addToken("uniform",ENMHlslToken::Uniform);

        addToken("[",ENMHlslToken::LeftSquareBracket);
        addToken("]",ENMHlslToken::RightSquareBracket);
        addToken("?",ENMHlslToken::Question);
        addToken("::",ENMHlslToken::ColonColon);
        addToken(":",ENMHlslToken::Colon);
        addToken(",",ENMHlslToken::Comma);

        addToken("true",ENMHlslToken::BoolConstantTrue);
        addToken("false",ENMHlslToken::BoolConstantFalse);


        addToken(".",ENMHlslToken::Dot);
        addToken("struct",ENMHlslToken::Struct);
        addToken("cbuffer",ENMHlslToken::CBuffer);
        addToken("register",ENMHlslToken::Register);

    }

} GTrieTreeInitializer;


struct HlslTokenizer
{
    String fileName_;
    const char * current_;
    const char * end_;
    const char * current_line_start_;
    int line_;

    HlslTokenizer(const String & inString , const String & fileName = "") : 
        fileName_(fileName),current_(nullptr) ,end_(nullptr) ,current_line_start_(nullptr),
        line_(0)
    {
        if(inString.length() > 0)
        {
            current_ = & inString[0];
            end_ = &inString[0] + inString.length();
            line_ = 1;
            current_line_start_ = current_;
        }
    }
    bool hasAvailableChars()
    {
        return current_ < end_;
    }

    char peek()
    {
        if(hasAvailableChars())
        {
            return * current_;
        }

        return 0;
    }
    char peek(int delta)
    {
        if(hasAvailableChars() && current_ + delta < end_)
        {
            return * (current_+ delta);
        }
        return 0;

    }
    void skipToNextLine()
    {
        while(hasAvailableChars())
        {
            char ch = peek();
            ++current_;
            if(ch == '\r' && peek() == '\n')
            {
                ++current_;
                break;
            }
            else if(ch == '\n')
            {
                break;
            }
        }
        ++line_;
        current_line_start_ = current_;
    }
    bool isWhiteSpace(char ch)
    {
        //char ch = peek();

        return ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n';
    }
    void skipWhiteSpaceAndLines()
    {
        while(hasAvailableChars())
        {
            char ch = peek();
            if(!isWhiteSpace(ch))
            {
                break;
            }
            ++current_;
            if(ch == '\r' && peek() == '\n') // windows next line
            {
                ++line_;
                ++current_;
                current_line_start_ = current_;
            }
            else if(ch == '\n') // linux next line
            {
                ++line_;
                current_line_start_ = current_;
            }

        }

    }
    void skipWhiteSpaceInLine()
    {
        char ch;
        while( (ch = peek()) && (ch == ' ' || ch == '\t' )  )
        {
            ++current_;
        }
    }

    bool matchWord(const String & word )
    {
        int len = word.length();
        for(int i = 0 ;i < len ; ++ i)
        {
            if(peek(i) != word[i])
            {
                return false;
            }
        }
        current_ += len;
        return true;
    }
    bool match(char ch)
    {
        if(peek() == ch)
        {
            ++current_;
            return true;
        }
        return false;
    }

    bool matchQuotedString(String & outString)
    {
        if(!match ('"'))
        {
            return false;
        }
        outString = "";
        while(peek() != '"')
        {
            outString.push_back(peek());
            ++current_;
        }
        if(match('"'))
        {
            return true;
        }

        return false;
    }

    bool matchIncludeHeaderFile(String & outFileName)
    {
        const char * origin = current_;
        if(peek() != '#')
        {
            return false;
        }
        ++current_;
        skipWhiteSpaceInLine();
        if(matchWord(String("include")))
        {
            skipWhiteSpaceInLine();
            return matchQuotedString(outFileName);
        }
        else 
        {
            current_ = origin;
            return false;
        }



    }
    bool isDigit(char ch)
    {
        return ch >='0' && ch <='9';

    }
    bool isAlpha(char ch)
    {
        return (ch >= 'a' && ch <= 'z') || ( ch >= 'A' && ch <= 'Z');
    }
    bool matchAndSkipDigits()
    {

        if(!isDigit(peek()))
        {
            return false;
        }

        while(isDigit(peek()) )
        {
            ++current_;
        }
        return true;

    }
    bool matchFloatNumber(String & outNumber)
    {
        //simple
        // [0-9]+[fF]
        const char * origin = current_;

        char ch = peek();
        if(!isDigit(ch) && ch != '.')
        {
            return false;
        }
        if(match('.') && matchAndSkipDigits())
        {
            match('f');
            outNumber = String(origin , current_);
            // .[0-9]f
            return true;
        }

        if(matchAndSkipDigits() && match('.') && matchAndSkipDigits() )
        {
            match('f');
            outNumber = String(origin,current_);

            return true;
        }

        return false;

    }

    bool matchDecimalInteger(uint32_t & outValue)
    {
        // [1-9][0-9]*
        char ch = peek();
        if( ! (ch >='1' && ch <= '9') )
        {
            return false;
        }
        outValue = 0;

        while(isDigit (peek() ))
        {
            outValue = outValue * 10 + (int)(peek()-'0');
            ++current_;
        }

        return true;
        //return matchAndSkipDigits();
    }

    bool matchInteger(uint32_t & outValue)
    {

        return matchDecimalInteger(outValue);
    }
    bool matchIdentifier(String & outValue)
    {
        char ch = peek();
        const char * origin = current_;
        if(ch != '_' && ! isAlpha(ch))
        {
            return false;
        }
        ++current_ ;

        while( isAlpha(peek()) || isDigit(peek()) || peek() == '_')
        {
            ++current_;
        }

        outValue =String(origin , current_);
        return true;
    }
    bool matchSymbol(String & outValue, ENMHlslToken &  token)
    {
        //ENMHlslToken token;

        if(StaticTrieTree.find(current_ ,token  ,outValue) ) 
        {
            current_ += outValue.length();
            return true;
        }
        return false;
    }
    bool isSymbol(const String & inValue,ENMHlslToken & token  )
    {
        return StaticTrieTree.isSymbol(inValue,token);
    }

};


HlslParser ::HlslParser()
{

}

inline void HlslParser::addToken(const HlslToken & token  ,const HlslTokenizer & tokenizer)
{
    int32_t index =  tokens_.add(token);
    tokens_[index].info_.lineNum_ = tokenizer.line_;
}

bool HlslParser::parse(String & inSource , HlslCompileInfo & info ) 
{
    HlslTokenizer tokenizer(inSource );
    
    while(tokenizer.hasAvailableChars())
    {
        tokenizer.skipWhiteSpaceAndLines();
        char ch = tokenizer.peek();
        if(ch == '#') 
        {
            String includeFile ;
            if(tokenizer.matchIncludeHeaderFile(includeFile))
            {
                PLOG()<<"parse include File " << includeFile <<PEND ;

            }

        }
        else 
        {
            String identifier ;
            ENMHlslToken symbolToken;
            uint32_t integer;
            if(tokenizer.matchFloatNumber(identifier))
            {
                addToken(HlslToken(ENMHlslToken::FloatConstant ,identifier),tokenizer);
            }
            else if(tokenizer.matchInteger(integer))
            {
                addToken(HlslToken(integer),tokenizer);
            }
            else if(tokenizer.matchIdentifier(identifier)) // identifier may contain keyword
            {
                if(tokenizer.isSymbol(identifier , symbolToken))
                {
                    addToken(HlslToken(symbolToken , identifier ),tokenizer);
                }
                else 
                {
                    addToken(HlslToken(identifier),tokenizer);
                }
            }
            else if(tokenizer.matchSymbol(identifier , symbolToken)) // keyword may not identifier
            {
                addToken(HlslToken(symbolToken,identifier),tokenizer);
            }
            else if(tokenizer.matchQuotedString(identifier))
            {
                addToken(HlslToken(ENMHlslToken::StringConstant,identifier),tokenizer);
            }
            else if(tokenizer.hasAvailableChars())
            {


            }



        }

    


    }




}

#define ArrayLen(ArrayName) sizeof(ArrayName)/sizeof(ArrayName[0])
// google test begin 
TEST(tokenizerTest , IntNumTest)
{
    String testIntNumbers[] ={
        "12345",
        "34567",
        "98474"
    };
    uint32_t testIntValues[] = {
        12345,
        34567,
        98474
    };
    String testnotIntNumbers[] ={
        "012345",
        "ab23456"
    };
    PLOG() << "---------------test for int number---------------" <<PEND;
    int len = sizeof(testIntNumbers)/ sizeof(testIntNumbers[0]);
    for(int i = 0 ; i < len ; ++i)
    {
        uint32_t tmp;
        HlslTokenizer tokenizer(testIntNumbers[i]) ;
        bool res = tokenizer.matchInteger(tmp);
        EXPECT_EQ(res , true );
        EXPECT_EQ(tmp , testIntValues[i]);
    }

    len = ArrayLen(testnotIntNumbers);
    for(int i = 0 ;i <len ;++ i)
    {
        uint32_t tmp;
        HlslTokenizer tokenizer(testnotIntNumbers[i]);
        bool res = tokenizer.matchInteger(tmp);
        EXPECT_EQ(res,false);
    }

}

TEST(tokenizerTest , IdentifierTest)
{
    String testIdentifier[] = {
        String("_123abc"),
        String("abcdD_e"),
        String("ABCDE_"),
        String("__")
    };

    String testNotIdentifier[] =
    {
        String("12abcde"),
        String("#abcde"),
        String("*123"),
        String("\0ef"),
        String("\n2123")
    };
    int len = ArrayLen(testIdentifier);
    for(int i = 0 ;i < len ; ++i)
    {
        String tmp;
        HlslTokenizer tokenizer(testIdentifier[i]);
        bool res = tokenizer.matchIdentifier(tmp);
        EXPECT_EQ( res , true);
        EXPECT_EQ(tmp==testIdentifier[i], true);
    }
    len = ArrayLen(testNotIdentifier);
    for(int i = 0 ;i <len ; ++ i)
    {
        String tmp;
        HlslTokenizer tokenizer(testNotIdentifier[i]);
        bool res = tokenizer.matchIdentifier(tmp) ;
        EXPECT_EQ(res , false);
    }


}


TEST(tokenizerTest ,SymbolTest)
{
    String testSymbol[] = {
        String("float4") ,
        String("texture2D"),
        String("half4"),
        String("cbuffer")
    };
    ENMHlslToken testTokens []= {
        ENMHlslToken::Float4,
        ENMHlslToken::Texture2D,
        ENMHlslToken::Half4,
        ENMHlslToken::CBuffer
    };

    int len = ArrayLen(testSymbol);

    for(int i = 0 ;i < len ; ++ i)
    {
        String tmp ;
        ENMHlslToken token;
        HlslTokenizer tokenizer(testSymbol[i]);
        bool res = tokenizer.matchSymbol(tmp , token);
        EXPECT_EQ(res , true);
        EXPECT_EQ(token , testTokens[i]);
        EXPECT_EQ(tmp, testSymbol[i] );

    }
    String testNotSymbol[] = {
        String("floaT"),
        String("Sample"), 
        String("Bool")
    };


    len = ArrayLen(testNotSymbol);
    for(int i = 0 ;i < len ; ++ i)
    {
        String tmp;
        ENMHlslToken token;
        HlslTokenizer tokenizer(testNotSymbol[i]);
        bool res = tokenizer.matchSymbol(tmp, token);
        EXPECT_EQ(res, false);
    }


}

TEST(tokenizerTest ,FloatNumberTest )
{

    String testfloatNumber[] = {
        String(".1224565f"),
        String("1243.2456"),
        String("23456.1234f"),
    };
    String notfloatNumber []=
    {
        String("12abc"),
        String("abc.789a"),
        String("12a.345")
    };



    PLOG() <<"-----------[test for float number] ------------" <<PEND;
    int len = sizeof(testfloatNumber) / sizeof(testfloatNumber[0]);
    for(int i = 0 ; i < len ; ++i)
    {
        String tmp;
        HlslTokenizer tokenizer(testfloatNumber[i]);
        PLOG() << "test for "  << testfloatNumber[i]  << PEND;
        EXPECT_EQ(tokenizer.matchFloatNumber(tmp) , true);
        EXPECT_EQ(testfloatNumber[i] == tmp , true);
    }

    len = sizeof(notfloatNumber) / sizeof(notfloatNumber[0]);

    for(int i = 0 ; i< len ;++ i)
    {
        String tmp;
        HlslTokenizer tokenizer(notfloatNumber[i]);
        PLOG() << "test for" << notfloatNumber[i] <<PEND;
        EXPECT_EQ(tokenizer.matchFloatNumber(tmp),false);
    }

}

    
}




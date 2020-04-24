#include "HlslToken.hpp"
#include "HlslParser.hpp"
#include <FrameWork/Common/String.hpp>
#include <FrameWork/Common/Logger.hpp>
namespace Persist
{

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



};


HlslParser ::HlslParser()
{

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

        }

    


    }




}



    
}
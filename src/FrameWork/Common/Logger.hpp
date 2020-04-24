#pragma once
#include <iostream>
#include "String.hpp"

namespace Persist
{



#define PLOG(...) Logger::instance().print(__FILE__ , __LINE__,__VA_ARGS__)

#define PEND std::endl

class Logger 
{
    public:
    static Logger &  instance () ;


    virtual Logger &  print(const char * strFile , int lineNum , const char * format = nullptr, ...) = 0  ;


    virtual Logger & operator<<(int value) = 0  ;
    virtual Logger & operator<< (const char * ) = 0 ;
    // for std:: endl
    virtual Logger & operator << (std::ostream & (*op) (std::ostream &) ) = 0;
    virtual Logger & operator << (const String & str) = 0;



};

}
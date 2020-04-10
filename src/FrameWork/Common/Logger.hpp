#pragma once
namespace Persist
{

#define PLOG(...) Logger::instance().print(__VA_ARGGS__)

class Logger 
{
    public:
    static Logger &  instance () ;


    //virtual void print(const char * format, ...) = 0  ;


    //virtual Logger & operator<<(int value) = 0  ;
    //virtual Logger & operator<< (const char * ) = 0 ;



};

}
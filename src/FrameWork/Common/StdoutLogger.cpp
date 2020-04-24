#include "Logger.hpp"
#include <string>
#include <stdarg.h>
#include <iostream>

namespace Persist
{

class StdoutLogger : public Logger
{
    public :
    StdoutLogger() {}

    Logger &  print(const char * strFile , int lineNum  ,const char * format = nullptr ,...) override;
    Logger & operator << (const char * ) override;
    Logger & operator << (int value) override;
    Logger & operator << (std::ostream  & (*op) (std::ostream & )) override ;
    Logger & operator <<  (const String & str) override ;

    protected:


};


Logger &  StdoutLogger::print(const char * strFile , int lineNum , const char * format , ... ) 
{
    if(format == nullptr)
    {
        std::cout << "[" << strFile << " :" <<lineNum <<"] " ;
        return *this;
    }
    std::string strbuffer;

    va_list ap;
    va_start(ap ,format);
    int len = _vscprintf(format , ap);
    if(len > 0)
    {
        char  * buf = new char[len +1];
        vsprintf(buf , format, ap);
        strbuffer.assign(buf , buf+len );

    }
    va_end(ap);
    std::cout <<"[" << strFile  << " :" << lineNum << "]" <<  strbuffer <<std::endl;

    return *this;

}


Logger & StdoutLogger::operator<<(const char * str)
{
    std::cout << str ;
    return * this;
}

Logger & StdoutLogger::operator<< (int value)
{
    std::cout << value ;
    return *this;
}
/// std::endl is a function 
Logger & StdoutLogger::operator<< (std::ostream &  (*op) (std:: ostream & ) )
{
    std::cout << op;
    return *this;
}

Logger & StdoutLogger :: operator<<(const String & str)
{
    std::cout << str.toStdString();
    return *this;

}

Logger & Logger::instance()
{
    static StdoutLogger logger;
    return logger;

}


}
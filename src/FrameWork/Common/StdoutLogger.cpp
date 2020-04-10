#include "Logger.hpp"

namespace Persist
{

class StdoutLogger : public Logger
{
    public :
    StdoutLogger() {}
    protected:


};


Logger & Logger::instance()
{
    static StdoutLogger logger;
    return logger;

}


}
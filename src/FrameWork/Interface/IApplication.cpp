#include "IApplication.hpp"
#include <Platform/Windows/Application_win32.hpp>


namespace Persist
{

    IApplication *IApplication::current_application_ = nullptr;

    IApplication * IApplication::currentApplication()
    {

        if(current_application_ == nullptr)
        {
            static Application_win32 s_local  = Application_win32();
            current_application_ = & s_local;
        }
        return current_application_;

    }



}
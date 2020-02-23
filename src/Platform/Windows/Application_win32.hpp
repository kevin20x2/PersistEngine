#pragma once
#include <FrameWork/Interface/IApplication.hpp>
#include <windows.h>

namespace Persist
{
    
    class Application_win32 : extends IApplication
    {
        public :

        static LRESULT CALLBACK WindowProc(HWND hWnd , UINT message , WPARAM wParam , LPARAM lParam);

        virtual ~Application_win32() {}

        virtual Status init() override;

        virtual void destroy() override;

        virtual void tick() override ;

        virtual bool isQuit() override;
        protected:

        bool is_quit_  = false;

        HWND hWnd_ ;

        MSG msg_ ;



    };




}
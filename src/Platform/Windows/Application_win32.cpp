#include "Application_win32.hpp"
#include <windows.h>

#include <tchar.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include <FrameWork/RHIContext/RHIContext.hpp>
#include <RHI/D3D11/RHIContext_D3D11.hpp>
#include <FrameWork/Scene/World.hpp>


namespace Persist
{

Status Application_win32 :: init()
{

    std::cout << "init win32 application" ;
    HINSTANCE hInstance = GetModuleHandle(NULL);
    WNDCLASSEX wc;

    ZeroMemory(&wc , sizeof(WNDCLASSEX));


    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL ,IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

    wc.lpszClassName = L"PersistEngine";

    DWORD ErrCode ;

    if(!  RegisterClassEx(&wc) )
    {
        ErrCode = GetLastError();
        //MessageBoxW(NULL , _T("error"), L"PersistEngine" ,MB_ICONERROR);
        return Status::Error("Register window Error");
    }

    hWnd_ = CreateWindowEx(0, L"PersistEngine",
            L"PersistEngine",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            600,800,
            NULL,NULL,
            hInstance ,NULL
    );

    RHIContext_D3D11 * RHIContext = dynamic_cast<RHIContext_D3D11 *>( IRHIContext ::RHIContext() );
    RHIContext->setHWND(hWnd_);
    RHIContext->init();


    ShowWindow(hWnd_ , SW_SHOW);
    std::cout << "init win32 application over";
    return Status::Ok();
}

void Application_win32 :: tick()
{


    if(PeekMessage(&msg_ , NULL , 0 , 0 , PM_REMOVE )  )
    {
        TranslateMessage(&msg_);

        DispatchMessage(&msg_);
    }
    else 
    {
        World::thisWorld()->tick();
        //IRHIContext::RHIContext()->render();
    }

    //std::cout << " tick in win32" << std::endl;

}

void Application_win32 :: destroy()
{

}
bool Application_win32 :: isQuit()
{
    return is_quit_;
}

LRESULT CALLBACK Application_win32 :: WindowProc(HWND hWnd , UINT message , WPARAM wPram , LPARAM lParam)
{

    switch (message)
    {
    case WM_PAINT/* constant-expression */:
    {
        //std::cout << "paint" <<std::endl;
        //std::flush(std::cout);

    }
    break;
    case WM_DESTROY:
    {
        Application_win32 * app = dynamic_cast<Application_win32 *>( IApplication :: currentApplication());
        IRHIContext::RHIContext()->destroy();
        app->is_quit_ = true;

        PostQuitMessage(0);
        return 0;

    }
    case WM_SIZE :
    {
    //    std::cout << "resize" << std::endl;
        RECT rect;
        GetWindowRect(hWnd , &rect);
        IRHIContext::RHIContext()->resize(rect.right - rect.left , rect.bottom - rect.top);

    }

    }

    return DefWindowProc(hWnd , message ,wPram,lParam);
}

}
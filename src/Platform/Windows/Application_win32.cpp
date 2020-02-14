#include "Application_win32.hpp"
#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
namespace Persist
{

int Application_win32 :: init()
{

    std::cout << "init win32 application" ;
    HINSTANCE hInstance = GetModuleHandle(NULL);
    HWND hWnd ;
    WNDCLASSEX wc;

    ZeroMemory(&wc , sizeof(WNDCLASSEX));


    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL ,IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = _T("PersistEngine");

    DWORD ErrCode ;

    if(!  RegisterClassEx(&wc) )
    {
        ErrCode = GetLastError();
        //MessageBoxW(NULL , _T("error"), L"PersistEngine" ,MB_ICONERROR);
        return -1;
    }

    hWnd = CreateWindowEx(0, L"PersistEngine",
            L"PersistEngine",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            600,800,
            NULL,NULL,
            hInstance ,NULL
    );

    ShowWindow(hWnd , SW_SHOW);
    std::cout << "init win32 application over";
    return 0;
}

void Application_win32 :: tick()
{

    if(GetMessage(&msg_ , NULL , 0 , 0 ) )
    {
        TranslateMessage(&msg_);

        DispatchMessage(&msg_);

    }

    std::cout << " tick in win32" << std::endl;

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
    }
    break;
    case WM_DESTROY:
    {
        Application_win32 * app = dynamic_cast<Application_win32 *>( IApplication :: currentApplication());
        app->is_quit_ = true;

        PostQuitMessage(0);
        return 0;

    }

    }

    return DefWindowProc(hWnd , message ,wPram,lParam);
}

}
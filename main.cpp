#include <cstdio>
#include <iostream>
#include <Persist.hpp>
#include <windows.h>
using namespace std;
int main()
//int WINAPI WinMain(HINSTANCE hInstance , HINSTANCE hPrevInstance ,
//    LPTSTR lpCmdLine , int nCmdShow
//)
{

    std::cout << "hello engine";
    Persist::IApplication * application = 
    Persist::IApplication::currentApplication();

    application->init();

    while(!application->isQuit()) 
    {
        application->tick();
    }

    std::cout << " exit";

    return 0;
}
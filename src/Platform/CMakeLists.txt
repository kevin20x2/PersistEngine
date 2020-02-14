

add_library(Platform Windows/Application_win32.cpp)

target_compile_definitions(Platform PUBLIC  _UNICODE UNICODE WIN32 _WINDOWS )
target_link_libraries(Platform user32.lib)
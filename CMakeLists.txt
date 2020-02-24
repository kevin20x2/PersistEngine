cmake_minimum_required(VERSION 3.1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

project(PersistEngine)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
)

set(RHI_Platform DX11)

add_subdirectory(src/FrameWork)
add_subdirectory(src/Platform)
add_subdirectory(src/RHI)




add_executable(app main.cpp)

if(${RHI_Platform} STREQUAL "DX11")
    target_link_directories(app PUBLIC $ENV{DXSDK_DIR}\\Lib\\x64)
    add_compile_definitions(RHI_DX11)
    add_compile_definitions(DATA_TYPE_DX)
endif()

target_link_libraries(app FrameWork Platform RHI )



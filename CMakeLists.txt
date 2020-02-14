cmake_minimum_required(VERSION 3.1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

project(PersistEngine)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
)

add_subdirectory(src/FrameWork)
add_subdirectory(src/Platform)
add_subdirectory(src/RHI)




add_executable(app main.cpp)

target_link_directories(app PUBLIC $ENV{DXSDK_DIR}\\Lib\\x64)
target_link_libraries(app FrameWork Platform RHI )



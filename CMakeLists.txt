cmake_minimum_required(VERSION 3.1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

project(PersistEngine)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    $ENV{FBX_DIR}/include
)

set(RHI_Platform DX11)


if(MSVC)
    string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
    string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
    string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
endif(MSVC)



add_executable(app main.cpp)

add_custom_command(TARGET app 
                PRE_BUILD
                COMMAND ${CMAKE_SOURCE_DIR}/HeadPraserTool/build/HeadPraserTool.exe 

)

if(${RHI_Platform} STREQUAL "DX11")
    link_directories(app PUBLIC $ENV{DXSDK_DIR}\\Lib\\x64)
    target_compile_definitions(app PUBLIC RHI_DX11)
    target_compile_definitions(app PUBLIC DATA_TYPE_DX)
endif()

add_subdirectory(src/FrameWork)
add_subdirectory(src/Platform)
add_subdirectory(src/RHI)
add_subdirectory(src/ShaderCompiler)
#add_subdirectory(src/ThirdParty/googletest)

target_link_libraries(app FrameWork Platform RHI )



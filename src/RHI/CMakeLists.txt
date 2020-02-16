


add_library(RHI D3D11/Renderer_D3D11.cpp  D3D11/RHIVertexBuffer_D3D11.cpp)


message($ENV{DXSDK_DIR})
target_link_directories(RHI PUBLIC $ENV{DXSDK_DIR}\\Lib\\x64)

target_link_libraries(RHI dxgi.lib d3d11.lib  d3dx11.lib  "C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.17134.0\\um\\x64\\D3DCompiler.lib")


add_library(RHI_D3D11 
GpuProgram_D3D11.cpp 
RHIConstantBuffer_D3D11.cpp 
RHIContext_D3D11.cpp 
RHIShader_D3D11.cpp 
RHIVertexBuffer_D3D11.cpp 
RHIVertexIndexBuffer_D3D11.cpp 
RHIVertexLayout_D3D11.cpp 
RHIResource_D3D11.cpp
)

target_link_directories(RHI_D3D11 PUBLIC $ENV{DXSDK_DIR}\\Lib\\x64)
target_link_libraries(RHI_D3D11 dxgi.lib d3d11.lib  d3dx11.lib  "C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.17134.0\\um\\x64\\D3DCompiler.lib")


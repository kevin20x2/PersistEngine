

add_subdirectory(D3D11)

add_library(RHI RHI.cpp)

target_link_libraries(RHI RHI_D3D11)






add_subdirectory(Serialize)
add_subdirectory(Math)

add_library(FrameWork Interface/IApplication.cpp RHIContext/RHIContext.cpp )
target_link_libraries(FrameWork Serialize Math)
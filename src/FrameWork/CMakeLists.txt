
add_subdirectory(Serialize)

add_library(FrameWork Interface/IApplication.cpp Renderer/Renderer.cpp )
target_link_libraries(FrameWork Serialize)
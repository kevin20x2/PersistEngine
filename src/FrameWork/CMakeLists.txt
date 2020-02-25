
add_subdirectory(Serialize)
add_subdirectory(Math)

add_library(FrameWork Interface/IApplication.cpp Renderer/Renderer.cpp )
target_link_libraries(FrameWork Serialize Math)
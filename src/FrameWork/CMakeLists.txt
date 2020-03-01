
add_subdirectory(Serialize)
add_subdirectory(Math)
add_subdirectory(Scene)
add_subdirectory(Components)

add_library(FrameWork Interface/IApplication.cpp  )
target_link_libraries(FrameWork Serialize Math Scene Components)
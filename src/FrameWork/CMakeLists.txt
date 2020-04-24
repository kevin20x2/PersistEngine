
add_subdirectory(Serialize)
add_subdirectory(Math)
add_subdirectory(Scene)
add_subdirectory(Components)
add_subdirectory(ResourceImporter)
add_subdirectory(IO)

add_library(FrameWork 
Interface/IApplication.cpp 
Interface/TypeManager.cpp 
Engine.cpp 
Interface/IObject.cpp 
Unit/Unit.cpp  
Unit/SceneUnit.cpp
Geometry/Mesh.cpp 
Common/StdoutLogger.cpp 
 )
target_link_libraries(FrameWork Serialize Math Scene Components ResourceImporter IO)


add_subdirectory(FbxImporter)

add_library(ResourceImporter 
BaseImporter.cpp

)
target_link_libraries(ResourceImporter FbxImporter)
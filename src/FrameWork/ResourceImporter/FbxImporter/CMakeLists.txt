

add_library(FbxImporter 
FbxImporter.cpp)

#target_include_directories(FbxImporter PUBLIC $ENV{FBX_DIR}\\include )
target_link_directories(FbxImporter PUBLIC $ENV{FBX_DIR}\\lib\\vs2017\\x64\\debug)
target_link_libraries(FbxImporter libfbxsdk-md.lib libxml2-md.lib zlib-md.lib)
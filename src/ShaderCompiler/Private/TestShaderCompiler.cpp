#include <FrameWork/Common/Array.hpp>
#include <FrameWork/Common/Logger.hpp>
#include "../Public/ShaderCompileCommon.hpp"
#include "gtest/gtest.h"

using namespace Persist;
int main(int argc , char ** argv)
{
    
    ::testing::InitGoogleTest(&argc,argv);
    ShaderParameterInfo info;
    ShaderCompile::CompileShader(String("copy.vs"),info);

    //PLOG() << "test1234" ;
    return RUN_ALL_TESTS();
}
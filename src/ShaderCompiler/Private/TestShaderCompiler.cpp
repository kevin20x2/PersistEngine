#include <FrameWork/Common/Array.hpp>
#include <FrameWork/Common/Logger.hpp>
#include "../Public/ShaderCompileCommon.hpp"

using namespace Persist;
int main()
{
    
    ShaderParameterInfo info;
    ShaderCompile::CompileShader(String("copy.vs"),info);

    PLOG() << "test1234" ;
    return 0;
}
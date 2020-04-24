#pragma once

#include <FrameWork/Common/Status.hpp>
#include <FrameWork/Shaders/Public/ShaderParameterInfo.hpp>



namespace Persist
{


namespace ShaderCompile
{

extern Status CompileShader(const String & fileName , ShaderParameterInfo & info   );

}





}

#include "../Public/ShaderCompileCommon.hpp"
#include <FrameWork/IO/Public/FileReader.hpp>
#include "HlslParser.hpp"


namespace Persist
{

namespace ShaderCompile
{
    Status CompileShader(const String & fileName , ShaderParameterInfo & info)
    {
        PLOG()<<fileName<<PEND;
        FileReader reader(fileName);
        String inShaderText;
        reader.read(inShaderText);

        PLOG() << inShaderText << PEND;

        HlslParser parser;
        HlslCompileInfo compileInfo;

       // parser.parse(inShaderText ,compileInfo );

        parser.Debug_Print();





        return Status::Ok();

    }

}


}
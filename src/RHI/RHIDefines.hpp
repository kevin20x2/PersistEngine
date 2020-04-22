#pragma once
#include <FrameWork/Common/Common.hpp>

namespace Persist
{

enum class ENMRHIShaderPlatformType : uint8_t
{
    RHI_PT_DX11 = 0 ,
    RHI_PT_OPENGL = 1 
};


enum ENMBufferUsageFlags
{
    Buf_None = 0x0000,

    Buf_Static = 0x0001,

    Buf_Dynamic = 0x0002

};

enum ENMBufferFormatType
{
    BFT_R8G8B8_Float ,
    BFT_R32G32B32_Float 
};

enum ENMCompareFunctionType
{
    CFT_Less ,
    CFT_LessEqual,
    CFT_Greater,
    CFT_GreaterEqual,
    CFT_Equal,
    CFT_NotEqual,
    CFT_Always
};

enum ENMVertexFormatType
{
    VFT_None,
    VFT_Float1,
    VFT_Float2,
    VFT_Float3,
    VFT_Float4,
    VFT_PackedNormal,
    VFT_UByte4,
    VFT_Color ,

    VFT_MAX
};
enum ENMVertexUsageType
{
    VUT_None,
    VUT_POSITION,
    VUT_COLOR,
    VUT_NORMAL,
    VUT_TANTENT,

    VUT_MAX
};

template <typename EnumType>
class EnumAsByte
{
    public :
        EnumAsByte(EnumType value) 
        {
            if(value > 0xff)
            {
                throw Status:: Error(Status::InvalidArg);
            }
            byte_ = static_cast<uint8_t>(value);
        }
        uint8_t value()const { return byte_;}
        operator  EnumType() const  {
            return static_cast <EnumType>(byte_);
        }

private :
    uint8_t byte_;
};

}



#pragma once
#include <FrameWork/Common/Common.hpp>

namespace Persist
{
enum ENMBufferUsageFlags
{
    Buf_None = 0x0000,

    Buf_Static = 0x0001,

    Buf_Dynamic = 0x0002

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
            return byte_;
        }

private :
    uint8_t byte_;
};

}


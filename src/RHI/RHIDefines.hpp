#pragma once

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
    VFT_NONE,
    VFT_Float1,
    VFT_Float2,
    VFT_Float3,
    VFT_Float4,
    VFT_PackedNormal,
    VFT_UByte4,
    VFT_Color ,

    VFT_MAX
};

}



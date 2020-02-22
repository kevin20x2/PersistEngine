#pragma once
#include <FrameWork/Serialize/Serializeable.hpp>
#include <FrameWork/Common/Array.hpp>
#include <FrameWork/Serialize/Transfer.hpp>


namespace Persist
{
    using ArrayBuffer = Array <uint8_t>;

    struct SerializedGpuProgram  : public  ISerializeable
    {
        SERIALIZE(SerializedGpuProgram)

        template <typename TransferFunc>
        Status transfer(TransferFunc & transfer)
        {
            TRANSFER(buffer_);
            return Status::Ok();
        }
        ArrayBuffer buffer_;

    };



}
#include "../RHIResource.hpp"
#include "RHIResourceD3D11.hpp"


namespace Persist
{
IRHIResourceArray * IRHIResourceArray:: create(uint8_t * buffer, uint32_t size)
{
    return  new RHIBufferDataArrayD3D11(buffer , size);
}

}


#include "TransferContext.hpp" 
#include "Transfer.hpp"
#include <FrameWork/Shaders/SerializeShaderData.hpp>
#include <fstream>
namespace Persist
{
template <typename Type> 
Status TransferContext ::addReadRequest( const String & path , Type & dst )
{
    // default do nothing
    return Status::Error("unkown transfer Type");
}
template <>
Status TransferContext::addReadRequest <SerializedGpuProgram>
(const String & path , SerializedGpuProgram & dst)
{
    // must use binary otherwise shader will get error
    ReadTransferBase::byte_ifstream *  ifs = new ReadTransferBase::byte_ifstream(path.toCharArray() ,std::ios::binary);
    if(!ifs->is_open())
    {
        throw Status::Error("open file error");

    }
    ReadTransferBase Trans(ifs);
    

    dst.transfer(Trans);

    ifs->close();
    delete ifs;


    return Status::Ok();



}






}
#include "MeshRenderer.hpp"
#include <FrameWork/Shaders/SerializeShaderData.hpp>
#include <FrameWork/Serialize/TransferContext.hpp>
#include <FrameWork/Shaders/GpuProgram.hpp>
#include <FrameWork/RHIContext/RHIContext.hpp>
namespace Persist
{

void MeshRenderer::initShader()
{
    SerializedGpuProgram vs;
    TransferContext::addReadRequest("copy.vso", vs);

    GpuProgram * vs_pro = GpuProgram::createFromSerializedProgram(vs ,GpuProgram::PT_Vertex);
    IRHIContext::RHIContext()->createVertexShader(*vs_pro);

    SerializedGpuProgram ps;
    TransferContext::addReadRequest("copy.pso",ps);

    GpuProgram * ps_pro = GpuProgram::createFromSerializedProgram(ps , GpuProgram::PT_Pixel);
    IRHIContext::RHIContext()->createPixelShader(*ps_pro);

    RHIVertexFormatElementList eleList =
    {
        {VUT_POSITION , VFT_Float3 , 16} , 
        {VUT_COLOR,VFT_Float3 , 16}
    };
    layout_ = IRHIContext::RHIContext()->createVertexLayout(eleList,*vs_pro);

}
void MeshRenderer::commitMesh()
{
    Mesh * mesh = meshComp_->mesh();
    if(mesh != nullptr)
    {
       uint32_t vertex_size =  layout_->vertexSize();
       uint32_t vertex_count = mesh->vertices()->size();

       uint8_t * buffer = new uint8_t [vertex_size * vertex_count]  ;
       Array <Vector3f> & vertice = * ( mesh->vertices());
       Array <Vector4f> & colors = *( mesh->color());
       Array <int> & triangles = *(mesh->triangles());
       uint8_t offset = 0;

       for(int i = 0 ;i < vertex_count ; ++ i)
       {
           Vector3f & pos = vertice[i];
           Vector4f && color = colors.size() > i ? colors[i] : Vector4f(1.0,1.0,1.0,1.0);
           memcpy(buffer+ offset , reinterpret_cast<void *>(&pos),sizeof(Vector3f));
           offset += sizeof(Vector3f);
           memcpy(buffer + offset ,reinterpret_cast<void *>(& color),sizeof(Vector4f) );
           offset+= sizeof(Vector4f);
       }

       IRHIResourceArray * vertex_data = IRHIResourceArray::create(buffer, offset);
       RHIResourceCreateInfo info (vertex_data);
       IRHIContext::RHIContext()->createVertexBuffer(offset ,Buf_Dynamic , info);




    }

}

void MeshRenderer:: _commit()
{

}


}
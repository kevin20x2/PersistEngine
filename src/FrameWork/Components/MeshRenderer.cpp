#include "MeshRenderer.hpp"
#include <FrameWork/Shaders/SerializeShaderData.hpp>
#include <FrameWork/Serialize/TransferContext.hpp>
#include <FrameWork/Shaders/GpuProgram.hpp>
#include <FrameWork/RHIContext/RHIContext.hpp>
#include <FrameWork/Math/Matrix.hpp>
#include <FrameWork/Scene/World.hpp>
#include <FrameWork/Unit/CameraUnit.hpp>
namespace Persist
{

void MeshRenderer::initShader()
{
    SerializedGpuProgram vs;
    TransferContext::addReadRequest("copy.vso", vs);

    vs_= GpuProgram::createFromSerializedProgram(vs ,GpuProgram::PT_Vertex);
    IRHIContext::RHIContext()->createVertexShader(*vs_);

    SerializedGpuProgram ps;
    TransferContext::addReadRequest("copy.pso",ps);

    ps_= GpuProgram::createFromSerializedProgram(ps , GpuProgram::PT_Pixel);
    IRHIContext::RHIContext()->createPixelShader(*ps_);

    RHIVertexFormatElementList eleList =
    {
        {VUT_POSITION , VFT_Float3 , 16} , 
        {VUT_COLOR,VFT_Float4 , 16}
    };
    layout_ = IRHIContext::RHIContext()->createVertexLayout(eleList,*vs_);

    depthState_ = IRHIContext::RHIContext()->createDepthStencilState(RHIDepthStencilStateInitializer());

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
       uint32_t offset = 0;

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
       vertexBuffer_ = IRHIContext::RHIContext()->createVertexBuffer(offset ,Buf_Dynamic , info);

       IRHIResourceArray *index_data =
       IRHIResourceArray::create(reinterpret_cast<uint8_t *>(triangles.data()), triangles.size() * sizeof(int));
       RHIResourceCreateInfo index_info(index_data);
       indexBuffer_ = IRHIContext::RHIContext()->createIndexBuffer(triangles.size()*sizeof(int), Buf_Dynamic, index_info);

       RHIResourceCreateInfo constant_info;
       // MVP
       uint32_t size = sizeof(Matrix4x4f) * 3;
       constant_buffer_ =IRHIContext::RHIContext()->createConstantBuffer(size ,Buf_Dynamic , constant_info);

        IRHIContext::RHIContext()->setDepthStencilState(depthState_);



    }

}
void MeshRenderer::commitConstant()
{
    IRHIContext::RHIContext()->setVertexLayout(layout_);
    IRHIContext::RHIContext()->setVertexShader(*vs_);
    IRHIContext::RHIContext()->setPixelShader(*ps_);

    IRHIContext::RHIContext()->setVertexBuffer(vertexBuffer_ , layout_);
    IRHIContext::RHIContext()->setIndexBuffer(indexBuffer_);
    //set mvp 
    CameraUnit * camera = World::thisWorld()->activeLevel()->currentCamera();
    CameraComponent * com = camera->camera();

    Matrix4x4f && worldMat = (getComponent<TransformComponent>()->worldMat()).Transpose();
    Matrix4x4f && viewMat = (com->viewMat()).Transpose();
    Matrix4x4f && projMat = (com->projectionMat()).Transpose();

    uint8_t matBuffer [sizeof(Matrix4x4f) * 3];
    uint32_t size = sizeof(Matrix4x4f) ;
    memcpy(matBuffer, & worldMat  ,sizeof(Matrix4x4f));
    memcpy(matBuffer+ size, & viewMat  ,sizeof(Matrix4x4f));
    memcpy(matBuffer + 2*size, & projMat  ,sizeof(Matrix4x4f));


    IRHIResourceArray * array = IRHIResourceArray::create(matBuffer, sizeof(Matrix4x4f)*3);
    IRHIContext::RHIContext()->setConstantBufferValue(constant_buffer_,array);


    IRHIContext::RHIContext()->setConstantBuffer(constant_buffer_);




    //IRHIContext::RHIContext()->drawTriangleListRip(indexBuffer_->indexNum(), 0, 0);
    IRHIContext::RHIContext()->drawTriangleList(vertexBuffer_->vertexCount(),0);

}

void MeshRenderer:: _commit()
{
    if(!inited_)
    {
        initShader();
        commitMesh();
        inited_ =true;
    }
    commitConstant();

}


}
#pragma once
#include <FrameWork/Interface/IObject.hpp>
#include <FrameWork/Memory/SharePtr.hpp>
#include <FrameWork/Common/Array.hpp>
#include <FrameWork/Math/Vectors.hpp>
#include <FrameWork/Components/MeshRenderer.hpp>

namespace Persist
{
    PERSIST_OBJECT()
    class Mesh : public IObject
    {

        public :
        REGISTER_CLASS(Mesh);

        friend class MeshRenderer;
        Mesh():
            vertices_(new Array <Vector3f>),
            uv_(new Array <Vector2f>) , 
            color_(new Array <Vector4f>),
            triangles_(new Array <int>())
        {

        }

        void setVertice(Array <Vector3f> * vertice) 
        {
            vertices_.reset(vertice) ;
        }

        void setUV(Array <Vector2f> * uv)
        {
            uv_.reset(uv);
        }
        void setTriangles(Array <int> * triangles)
        {
            triangles_.reset(triangles);
        }
        void setColor(Array <Vector4f> * color )
        {
            color_ .reset( color ) ;
        }

        Array <Vector3f> * vertices()  { return vertices_.get();}
        Array <Vector4f> * color() { return color_.get();}
        Array <int> * triangles() {return triangles_.get();}




        
        protected:
        // TODO : need buffer class to keep MeshData

        SharePtr <Array <Vector3f> > vertices_ = nullptr;
        SharePtr <Array <Vector2f> > uv_ = nullptr;
        /// TODO : need a Color class
        SharePtr <Array <Vector4f>> color_ = nullptr;
        SharePtr <Array <int> > triangles_ = nullptr;




    };
}



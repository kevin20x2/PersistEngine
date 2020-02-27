#pragma once
#include <FrameWork/Interface/IObject.hpp>
#include <FrameWork/Memory/SharePtr.hpp>
#include <FrameWork/Common/Array.hpp>
#include <FrameWork/Math/Vectors.hpp>

namespace Persist
{
    class Mesh : public IObject
    {

        public :
        Mesh()
        {

        }

        void setVertice(Array <Vector3f> * vertice) 
        {
            vertices_ = vertice;
        }

        void setUV(Array <Vector2f> * uv)
        {
            uv_ = uv;
        }
        void setTriangles(Array <int> * triangles)
        {
            triangles_ = triangles;
        }
        void setColor(Array <Vector4f> * color )
        {
            color_ = color;
        }



        
        protected:
        // TODO : need buffer class to keep MeshData

        SharePtr <Array <Vector3f> > vertices_ = nullptr;
        SharePtr <Array <Vector2f> > uv_ = nullptr;
        /// TODO : need a Color class
        SharePtr <Array <Vector4f>> color_ = nullptr;
        SharePtr <Array <int> > triangles_ = nullptr;


    };
}




#pragma once
#include <FrameWork/Common/String.hpp>


namespace Persist
{

    namespace AST
    {
        struct CBufferDeclaration ;


        struct Node 
        {

        };

        struct CBufferDeclaration : public Node
        {
            CBufferDeclaration() {}

            const char * name_;
            Array <Node *> declarations_;

        };


    }


}
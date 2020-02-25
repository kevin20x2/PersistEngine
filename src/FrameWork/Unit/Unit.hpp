#pragma once
#include <FrameWork/Interface/IObject.hpp>
#include <FrameWork/Common/Array.hpp>
#include <FrameWork/Memory/SharePtr.hpp>
#include <FrameWork/Components/BaseComponent.hpp>

namespace Persist
{
    // base class of object in game world
    class Unit : extends IObject
    {

        public : 
        // TODO : need a object system 
        template <typename T > 
        T * getComponent() {
            for(int i = 0 ;i < components_.size() ; ++ i)
            {
                T * tmp = dynamic_cast<T*>(components_[i]);
                if(tmp != nullptr)
                {
                    return tmp;
                }
            }
            return nullptr;
        } 

        protected : 
        //T * queryComponentByType()




        protected : 
        Array <SharePtr < BaseComponent> > components_;
    };

}
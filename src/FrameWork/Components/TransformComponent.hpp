#pragma once
#include "BaseComponent.hpp"
#include <FrameWork/Scene/Transform.hpp>


namespace Persist
{
// Component with transform 
class TransformComponent : public BaseComponent
{
    public :
        TransformComponent(Unit *unit ) : 
        BaseComponent(unit),
        transform_()
        {
        }

        void setLocalPosition(Vector3f pos)
        {
            transform_.setLocalPosition(pos);
        }
        
        Transform & transform() { return transform_;}
        TransformComponent * addChild(TransformComponent * com)
        {
            if(com->parent_)
            {
                com->parent_->removeChild(com);
            }
            com->parent_ = this;
            childList_.push_back(com);
            return com;
        }
        TransformComponent * getChildAt(int index)
        {
            return childList_[index];
        }
        uint32_t childNum() { return childList_.size();}
        TransformComponent * removeChild(TransformComponent * com)
        {
            for(auto it = childList_.begin(); it != childList_.end(); ++it)
            {
                if(com == *it)
                {
                    childList_.erase(it);
                    return com;
                }
            }
            return com;
        }
        const Matrix4x4f & worldMat() { return transform_.worldMatrix();}
    private : 
    Array <TransformComponent * > childList_;
    TransformComponent * parent_ = nullptr;
    Transform transform_;

};

}
#pragma once
#include "Unit.hpp"
#include <FrameWork/Components/TransformComponent.hpp>

namespace Persist
{
PERSIST_OBJECT()
class SceneUnit : public Unit
{

    public : 
    REGISTER_CLASS(SceneUnit);
        SceneUnit( ) : 
        transform_comp_( new TransformComponent(this))
        {
            addComponent<TransformComponent>(transform_comp_);
        }


        TransformComponent * getTransformComponent()
        {
            return getComponent<TransformComponent>();
            //return tranform_comp_;
        }

        SceneUnit * getChildAt(int index) 
        {
            TransformComponent * comp =  transform_comp_->getChildAt(index) ;
            Unit * pUnit = comp->unit();
            if(comp != nullptr && isTypeOf<SceneUnit>(pUnit))
            {
                return dynamic_cast <SceneUnit * >(comp->unit());
            }
            return nullptr;
        }

        uint32_t getChildNum()
        {
            return transform_comp_->childNum();
        }
        
        SceneUnit * addChild( SceneUnit * unit)
        {
            TransformComponent * comp = unit->getTransformComponent();
            if(comp != nullptr && transform_comp_ != nullptr)
            {
                transform_comp_->addChild(comp);
                return unit;
            }
            else 
            {
                return nullptr;
            }

        }


    protected:

        TransformComponent * transform_comp_;



};

}
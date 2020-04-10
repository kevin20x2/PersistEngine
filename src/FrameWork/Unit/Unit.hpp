#pragma once
#include <FrameWork/Interface/IObject.hpp>
#include <FrameWork/Common/Array.hpp>
#include <FrameWork/Memory/SharePtr.hpp>
#include <FrameWork/Common/String.hpp>
//#include <FrameWork/Components/BaseComponent.hpp>



namespace Persist
{
    class BaseComponent;
    // base class of object in game world
    PERSIST_OBJECT()
    class Unit : extends IObject
    {


        public : 
        REGISTER_CLASS(Unit);
        // TODO : need a object system 
        template <typename T > 
        T * getComponent() 
        {

            if(type_component_map_.find(typeOf<T>()) != type_component_map_.end() )
            {
                return dynamic_cast <T*> (type_component_map_[typeOf<T>()].get() );
            }

            return nullptr;
        } 

        template <typename T>
        T * addComponent( T * comp = nullptr) 
        {
            if(comp == nullptr )
            {
                comp = new T(this);

            }
            else {
                comp->unit_ = this;
            }
            SharePtr<T> ptr(comp);
            type_component_map_[typeOf<T>()] = ptr;
            return comp;
        }

        String getName()
        {
            return name_;
        }
        void setName(const String & name)
        {
            name_ = name;
        }






    protected:
        //T * queryComponentByType()

    protected:
        //Array <SharePtr < BaseComponent> > components_;
        HashMap<const Type *, SharePtr<BaseComponent>> type_component_map_;
        String name_;
    };
}
#pragma once
#include <FrameWork/Interface/IObject.hpp>
#include <FrameWork/Common/Array.hpp>
#include <FrameWork/Memory/SharePtr.hpp>
//#include <FrameWork/Components/BaseComponent.hpp>



namespace Persist
{
    class BaseComponent;
    // base class of object in game world
    class Unit : extends IObject
    {

        public : 
        // TODO : need a object system 
        template <typename T > 
        T * getComponent() {

            if(type_component_map_.find(typeOf<T>()) != type_component_map_.end() )
            {
                return dynamic_cast <T*> (type_component_map_[typeOf<T>()].get() );
            }

            /*
            for(int i = 0 ;i < components_.size() ; ++ i)
            {
                //SharePtr <BaseComponent> base = components_[i];
                SharePtr<T> tmp = std::dynamic_pointer_cast<T>(components_[i]);
                if(tmp != nullptr)
                {
                    return tmp.get();
                }
            }
            */
            return nullptr;
        } 
        template <typename T>
        T * addComponent( T * comp = nullptr) {
            if(comp == nullptr )
            {
                comp = new T(this);
            }
            else {
                comp->unit_ = this;
            }
            SharePtr <T > ptr (comp);
            //components_.push_back(ptr);
            type_component_map_[typeOf<T>()] = ptr; 
            return comp;
        }

        protected : 
        //T * queryComponentByType()




        protected : 
        //Array <SharePtr < BaseComponent> > components_;
        HashMap <const Type * , SharePtr < BaseComponent > > type_component_map_;
    };

}
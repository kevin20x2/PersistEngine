#pragma once
#include <FrameWork/Interface/IRunTimeModule.hpp>
#include "Level.hpp"
#include <FrameWork/Common/Array.hpp>
#include <FrameWork/Memory/SharePtr.hpp>
#include <functional>


namespace Persist
{
class World : public IRunTimeModule
{
    public : 
    World () 
    {
        levelList_.push_back( SharePtr<Level>( new Level() ));
    }


    static World * thisWorld() { 
        if(thisWorld_ == nullptr)
        {
            thisWorld_ = new World();
        }
        return thisWorld_ ;

    }

    virtual Status init() override;

    virtual void tick() override ;

    void destroy() override;

    Level * activeLevel() {
        return levelList_[activeLevelIdx].get();
    }

    //template < typename T >
        void frameTick( std::function <void( ) > &&  func)
        {
            tickList_.push_back(std::move(func));
        }

    protected:
    int activeLevelIdx = 0 ;
    Array <SharePtr <Level> > levelList_;
    Array <std::function <void ()>> tickList_;


    static World * thisWorld_;


};

}
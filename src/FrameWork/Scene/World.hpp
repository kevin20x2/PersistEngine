#pragma once
#include <FrameWork/Interface/IRunTimeModule.hpp>
#include "Level.hpp"
#include <FrameWork/Common/Array.hpp>
#include <FrameWork/Memory/SharePtr.hpp>


namespace Persist
{
class World : public IRunTimeModule
{
    public : 
    World () 
    {
        levelList_.push_back( SharePtr<Level>( new Level() ));
    }


    virtual Status init() override;

    virtual void tick() override ;

    void destroy() override;

    Level * activeLevel() {
        return levelList_[activeLevelIdx].get();
     }



    protected:
    int activeLevelIdx = 0 ;
    Array <SharePtr <Level> > levelList_;


};

}
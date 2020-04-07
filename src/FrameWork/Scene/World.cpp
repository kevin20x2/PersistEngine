#include "World.hpp"

namespace Persist
{
World * World::thisWorld_ = nullptr;

Status World::init()
{
	return Status::Ok();
}
void World::tick()
{
    for(auto it = tickList_.begin(); it != tickList_.end();++it)
    {
        (*it)();
    }
    activeLevel()->tick();

}
void World::destroy()
{
}
}
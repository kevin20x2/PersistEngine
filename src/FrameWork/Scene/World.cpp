#include "World.hpp"

namespace Persist
{
World * World::thisWorld_ = nullptr;

Status World::init()
{
}
void World::tick()
{
    activeLevel()->tick();

}
void World::destroy()
{
}
}
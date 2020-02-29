#include "World.hpp"

namespace Persist
{
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
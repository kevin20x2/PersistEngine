#include "Level.hpp"
namespace Persist
{


void Level::tick()
{
    currentCamera_->render();

}

}
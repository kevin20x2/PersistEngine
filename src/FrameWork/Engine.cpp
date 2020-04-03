#include "Engine.hpp"
#include <FrameWork/Interface/TypeManager.hpp>
namespace Persist
{

void Engine::Init()
{
    TypeManager::Get()->registerAllClass();
}


}
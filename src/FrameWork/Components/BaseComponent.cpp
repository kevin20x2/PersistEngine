#include  "BaseComponent.hpp"
#include <FrameWork/Unit/Unit.hpp>
namespace Persist
{
    template <typename T>
    T * BaseComponent::getComponent()
    {
        return unit_->getComponent<T>();
    }


}

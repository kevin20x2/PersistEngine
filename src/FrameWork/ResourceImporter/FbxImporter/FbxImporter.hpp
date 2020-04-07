#pragma once
#include "../BaseImporter.hpp"

namespace Persist
{
class FbxImporter : public BaseImporter
{
    public :
    FbxImporter() = default ;

    SceneUnit * loadFromDisk(const String & path) override ; 

};

}
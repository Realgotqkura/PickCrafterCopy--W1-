#include "loader.h"
#include "verteces.h"

void loadObjects(){
    const std::vector<float> floatVec(triangleVerteces, triangleVerteces + triangleVertexesSize);
    RawObject rawObj(floatVec);
    Engine::rawObjects.emplace_back(rawObj);
}

namespace Engine{
    std::vector<RawObject> rawObjects;
}
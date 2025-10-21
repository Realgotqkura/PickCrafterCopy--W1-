#pragma once
#include <vector>
#include "raw_object.h"

void loadObjects();

namespace Engine{
    extern std::vector<RawObject> rawObjects;
}
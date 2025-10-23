#pragma once
#include "texture.h"
#include <memory>

namespace GameData{

    extern unsigned short blockBreakStage;
    extern Texture* currentBlockBreakTexture;
};

void initGameData();
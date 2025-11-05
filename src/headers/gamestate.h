#pragma once
#include "texture.h"
#include <memory>

namespace GameData{

    extern unsigned short blockBreakStage;
    extern unsigned int xp;
    extern Texture* currentBlockBreakTexture;
};

void initGameData();
#include "gamestate.h"


namespace GameData {
    unsigned short blockBreakStage = 1;
    Texture* currentBlockBreakTexture = nullptr;
}


void initGameData(){
    GameData::currentBlockBreakTexture = TextureManager::textureObjectsList["blockbreak_stage4"].get();
}
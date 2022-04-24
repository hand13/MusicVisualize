#include "player.h"
bool Player::init() {
    ALFWInit();
    if(!ALFWInitOpenAL()) {
        ALFWShutdown();
        return false;
    }
    alGenBuffers(1,&uiBuffer);
    alGenSources(1,&uiSource);
    return true;
}
void Player::play(const char * path) {
    if(!ALFWLoadWaveToBuffer(path,uiBuffer)) {
        return;
    }
    alSourcei(uiSource,AL_BUFFER,uiBuffer);
    alSourcePlay(uiSource);
    ALint state;
    do{
        Sleep(100);
        alGetSourcei(uiSource,AL_SOURCE_STATE,&state);
    }while(state == AL_PLAYING && !stopped);
}
void Player::cleanup() {
    if(uiSource != 0){
        alSourceStop(uiSource);
        alDeleteSources(1,&uiSource);
    }
    if(uiBuffer != 0){
        alDeleteBuffers(1,&uiBuffer);
    }
}
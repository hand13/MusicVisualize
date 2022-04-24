#pragma once
#include "Framework.h"
class Player {
    private:
    ALuint uiBuffer = 0;
    ALuint uiSource = 0;
    volatile bool stopped = false;
    public:
    Player() = default;
    bool init();
    void play(const char * path);
    inline void stop() {
        stopped = true;
    }
    void cleanup();
    ~Player(){cleanup();}
};
#pragma once
#include "player.h"
#include "freq.h"
#include <string>
#include <thread>
#include "imgui.h"
class MusicViewer {
    private:
    Player player;
    Freq freq;
    std::thread thr;
    std::string path;
    int startCount;
    public:
    MusicViewer();
    bool init(const char * path);
    void play();
    inline SF_INFO getInfo()const {
        return freq.getInfo();
    }
    void draw(float w,float h,int size,int freq_min,int freq_max);
    ~MusicViewer() {
        player.stop();
        if(thr.joinable()) {
            thr.join();
        }
    }
};
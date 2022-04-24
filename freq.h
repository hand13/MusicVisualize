#pragma once
#include <sndfile.h>
class Freq {
    private:
    SNDFILE * file = nullptr;
    SF_INFO info;
    public:
    Freq() = default;
    bool init(const char * path);
    void calcEnergy(int time,int frame_range,int freq_range,int * freq,float * freq_energy,int freq_size);
    void cleanup();
};
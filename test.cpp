#include "freq.h"
#include <iostream>
int main() {
    int freq_min = 500;
    int freq_max = 8000;
    int size = 20;
    int delta = (8000-500)/size;
    int *freq = new int[size];
    int start_second = 3;
    int frame_range = 4000;
    int freq_range = 40;
    float * ene = new float[size];
    for(int i = 0;i<size;i++) {
        freq[i] = freq_min + delta * i;
    }
    Freq fr;
    fr.init("resource/blackair.wav");
    fr.calcEnergy(1000 * start_second,frame_range,freq_range,freq,ene,size);
    for(int n = 0;n<size;n++) {
        std::cout<<ene[n]<<std::endl;
    }
    return 0;
}
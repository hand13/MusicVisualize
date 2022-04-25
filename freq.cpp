#include "freq.h"
#include <fftw3.h>
#include <sndfile.h>
#include <cmath>
#include <cmath>
#include <memory>

bool Freq::init(const char * path) {
    file = sf_open(path,SFM_READ,&info);
    if(file == nullptr) {
        return false;
    }
    return true;
}


void Freq::calcEnergy(int time,int frame_range,int freq_range,int * freq,float * freq_energy,int freq_size) {

    if(freq_size <= 0) {
        return;
    }

    int shift = static_cast<int>(static_cast<float>(info.samplerate) * (static_cast<float>(time)/1000.f));
    if(shift >= info.frames) {
        for(int i = 0;i<freq_size;i++) {
            freq_energy[i] = 0.f;
        }
        return;
    }
    sf_seek(file,shift,SF_SEEK_SET);
    double * buffer = new double[info.channels * frame_range];
    frame_range = static_cast<int>(sf_readf_double(file,buffer,frame_range));
    fftw_complex * fi;
    fftw_complex* fo;
    fftw_plan p;
    int n = frame_range;

    fi = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * n);

    for(int i = 0;i<n;i++) {
        fi[i][0] = buffer[info.channels*i];//one channel
        fi[i][1] = 0;
    }
    fo = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * n);
    p = fftw_plan_dft_1d(n,fi,fo,FFTW_FORWARD,FFTW_ESTIMATE);
    fftw_execute(p);
    int f_delta = (info.samplerate)/frame_range;

    for(int i = 0;i<freq_size;i++) {
        int f = freq[i];
        int f_min = f - (freq_range/2);
        if (f_min<0) {
            f_min = 0;
        }
        int f_max = f + (freq_range/2);
        int f_min_i = f_min / f_delta;
        int f_max_i = f_max /f_delta;

        float total_energy = 0.f;
        int count = 0;
        for(int y = f_min_i;y<=f_max_i && y < frame_range;y++) {
            total_energy += static_cast<float>(abs(fo[y][0]));
            count++;
        }
        freq_energy[i] = total_energy == 0 ? 0 : total_energy / static_cast<float>(count);
    }

    fftw_destroy_plan(p);
    fftw_free(fi);
    fftw_free(fo);
    delete buffer;
}

void Freq::cleanup() {
    if(file != nullptr){
        sf_close(file);
    }
}
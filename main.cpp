#include <fftw3.h>
#include <iostream>
int main() {
    fftw_complex * fi;
    fftw_complex* fo;
    fftw_plan p;
    int n = 100;
    fi = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * n);
    for(int i = 0;i<100;i++) {
        fi[i][0] = 1.0;
        fi[i][1] = 2.0;
    }
    fo = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * n);
    p = fftw_plan_dft_1d(n,fi,fo,FFTW_FORWARD,FFTW_ESTIMATE);
    fftw_execute(p);
    for(int i= 0;i<n;i++) {
        std::cout<<fo[n][0]<<"---"<<fo[n][1]<<std::endl;
    }
    fftw_destroy_plan(p);
    fftw_free(fi);
    fftw_free(fo);
    return 0;
}
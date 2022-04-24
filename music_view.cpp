#include "music_view.h"
#include <thread>

MusicViewer::MusicViewer() {
}

bool MusicViewer::init(const char * path) {
    this->path = path;

    return player.init() && freq.init(path);
}
void MusicViewer::play() {
    startCount = GetTickCount();
    thr = std::thread([&](){
        player.play(path.c_str());
    });
}
void MusicViewer::draw(float w,float h,int size,int freq_min,int freq_max,const ImColor& color) {
    // ImVec2 pos= ImGui::GetCursorPos() + ImGui::GetWindowPos();
    float x_shift = ImGui::GetCursorPos().x + ImGui::GetWindowPos().x;
    float y_shift = ImGui::GetCursorPos().y + ImGui::GetWindowPos().y;
    int time = GetTickCount() - startCount;
    float maxHeight = 80.0;
    float margin_v = 0.1f;
    int frame_range = 4000;
    int freq_range = (freq_max - freq_min)/size;//todo

    int delta = (freq_max-freq_min)/size;
    int * freqs = new int[size];
    for(int j = 0;j<size;j++) {
        freqs[j] = freq_min + delta * j;
    }
    float* ene = new float[size];
    freq.calcEnergy(time,frame_range,freq_range,freqs,ene,size);

    float height = h + y_shift;
    float width = (w/size) * (1-margin_v);
    float margin = (w/size) * margin_v;

    for(int i = 0;i<size;i++) {
        float x = (width + 2 * margin)*i + margin + x_shift;
        float div = ene[i]/maxHeight;
        if(div >= 1.f) {
            div = 1.f;
        }
        float y = div * h;
        ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(x,height),ImVec2(x + width,height - y),color);
    }
    delete ene;
    delete freqs;
}
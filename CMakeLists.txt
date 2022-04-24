project(Music)
cmake_minimum_required(VERSION 3.18)
include_directories(
    "E:\\usr\\OpenAL 1.1 SDK\\include"
    "third_party/fftw-3.3.5-dll64"
    "third_party/sndfile/include" 
    "E:\\usr\\OpenAL 1.1 SDK\\include"
)
link_directories("third_party/fftw-3.3.5-dll64" "third_party/sndfile/lib" "E:\\usr\\OpenAL 1.1 SDK\\libs\\Win64")

set(IMGUI_SRC imgui_demo.cpp imgui_draw.cpp 
	imgui_impl_dx12.cpp imgui_impl_win32.cpp imgui_tables.cpp imgui_widgets.cpp imgui.cpp)

set(OPAL_FRAMEWORK_SRC aldlist.cpp cWaves.cpp Framework.cpp LoadOAL.cpp)
add_library(al_framework STATIC ${OPAL_FRAMEWORK_SRC})

add_library(imgui_dx12 STATIC ${IMGUI_SRC})
add_executable(main main.cpp player.cpp freq.cpp music_view.cpp)

add_executable(test test.cpp player.cpp freq.cpp)
target_link_libraries(test al_framework OpenAL32 sndfile libfftw3-3.lib)

target_link_libraries(main libfftw3-3.lib sndfile imgui_dx12 d3d12 dxgi sndfile OpenAL32 al_framework libfftw3-3.lib)

add_custom_command(TARGET main PRE_BUILD
 COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/third_party/fftw-3.3.5-dll64/libfftw3-3.dll $<TARGET_FILE_DIR:main>/libfftw3-3.dll)
add_custom_command(TARGET main PRE_BUILD
 COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/third_party/sndfile/bin/sndfile.dll $<TARGET_FILE_DIR:main>/sndfile.dll)
add_custom_command(TARGET main PRE_BUILD
 COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resource $<TARGET_FILE_DIR:main>/resource)
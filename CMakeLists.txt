project(Music)
cmake_minimum_required(VERSION 3.18)
include_directories(
    "E:\\usr\\OpenAL 1.1 SDK\\include",
    "third_party/fftw-3.3.5-dll64"
)
link_directories("third_party/fftw-3.3.5-dll64")
add_executable(main main.cpp)
target_link_libraries(main libfftw3-3.lib)
add_custom_command(TARGET main PRE_BUILD
 COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/third_party/fftw-3.3.5-dll64/libfftw3-3.dll $<TARGET_FILE_DIR:main>/libfftw3-3.dll)
cmake_minimum_required(VERSION 3.18)
project(Guxt LANGUAGES CXX)

add_executable(pxGame 
    src/Draw.cpp
    src/Game.cpp
    src/Input.cpp
    src/Mutex.cpp
    src/Sound.cpp
    src/WinMain.cpp
    src/pxGame.rc
)

if(MSYS OR MINGW)
    target_link_libraries(pxGame -static-libgcc -static-libstdc++)
endif()
target_link_libraries(pxGame ddraw)
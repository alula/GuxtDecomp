cmake_minimum_required(VERSION 3.18)
project(Guxt LANGUAGES CXX)
ENABLE_LANGUAGE(RC)
    
if(MINGW)
    set(CMAKE_RC_COMPILER_INIT i686-w64-mingw32-windres)
    SET(CMAKE_RC_COMPILE_OBJECT "<CMAKE_RC_COMPILER> <FLAGS> -O coff <DEFINES> -i <SOURCE> -o <OBJECT>")
endif(MINGW)

add_executable(pxGame 
    src/Bullet.cpp
    src/Caret.cpp
    src/Draw.cpp
    src/Event.cpp
    src/Fade.cpp
    src/Game.cpp
    src/GameAct.cpp
    src/GameAttr.cpp
    src/Input.cpp
    src/KeyConfig.cpp
    src/Map.cpp
    src/Menu.cpp
    src/Mutex.cpp
    src/NpcAct000.cpp
    src/NpcAct020.cpp
    src/Object.cpp
    src/PixFile.cpp
    src/PlayRecord.cpp
    src/Random.cpp
    src/Ship.cpp
    src/Sound.cpp
    src/Stage.cpp
    src/Text.cpp
    src/TrigFuncs.cpp
    src/WinDebugDrag.cpp
    src/WinMain.cpp
    src/pxGame.rc

    src/pxtone/pxtoneNoise.cpp
    src/pxtone/pxtnDescriptor.cpp
    src/pxtone/pxtnMem.cpp
    src/pxtone/pxtnPulse_Frequency.cpp
    src/pxtone/pxtnPulse_Oscillator.cpp
    src/pxtone/pxtnPulse_PCM.cpp
    src/pxtone/pxtnPulse_Noise.cpp
    src/pxtone/pxtnPulse_NoiseBuilder.cpp
)

target_link_directories(pxGame PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/lib/pxtone.dll" DESTINATION "${CMAKE_BINARY_DIR}/")
# wine wrapper
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/pxGame" DESTINATION "${CMAKE_BINARY_DIR}/")

if(MSYS OR MINGW)
    target_link_libraries(pxGame -static-libgcc -static-libstdc++)
endif()
target_link_libraries(pxGame gdi32 imm32 comctl32 shlwapi dsound ddraw dinput8 dxguid version pxtone)
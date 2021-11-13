cmake_minimum_required(VERSION 3.18)
project(Guxt LANGUAGES CXX)

add_executable(pxGame 
    src/Caret.cpp
    src/Draw.cpp
    src/Game.cpp
    src/GameAttr.cpp
    src/Input.cpp
    src/Mutex.cpp
    src/Text.cpp
    src/Ship.cpp
    src/Sound.cpp
    src/Stage.cpp
    src/WinDebugDrag.cpp
    src/WinMain.cpp
    src/pxGame.rc
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
target_link_libraries(pxGame gdi32 imm32 comctl32 shlwapi dsound ddraw dinput8 dxguid pxtone)
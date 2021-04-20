#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <wsjcpp_core.h>
#include <ctime>
#include <cstdlib>

#include "render_window.h"
#include "main_controller.h"

int main(int argc, char* args[]) {
    std::srand(std::time(nullptr));

    MainController *pMainController = new MainController("ns18");

    if (!pMainController->initRenderWindow()) {
        return -1;
    }

    if (!pMainController->initObjects()) {
        return -1;
    }

    CoordXY coordCenter = pMainController->getCoordCenter();
    
    // player
    bool gameRunning = true;

    long nNumberOfFrames = 0;
    long nStartTime = getCurrentTimeInMilliseconds();
    long nElapsed = 0;
    pMainController->getGameState()->init();
    pMainController->getWindow()->sortObjectsByPositionZ();

    while (gameRunning) {
        pMainController->getGameState()->updateElapsedTime();
        pMainController->getWindow()->clear();
        pMainController->modifyObjects();
        pMainController->getWindow()->drawObjects();

        SDL_Event event;
        const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);

        // Get our controls and events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                gameRunning = false;
            }
        }

        // FPS
        nNumberOfFrames++;
        nElapsed = getCurrentTimeInMilliseconds() - nStartTime;
        if (nElapsed > 3000) {
            double nFPS = nNumberOfFrames;
            nFPS /= nElapsed;
            nFPS *= 1000;
            pMainController->updateFpsValue(nFPS);
            nStartTime = getCurrentTimeInMilliseconds();
            nNumberOfFrames = 0;
        }
    }

    pMainController->getWindow()->cleanUp();
    // Mix_FreeMusic(music);
    SDL_Quit();
    return 0;
}
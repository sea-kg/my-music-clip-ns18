
#include "main_controller.h"
#include <iostream>
#include "render.h"
#include "render_ns18zoid.h"
#include "render_background.h"
#include <fstream>
#include "wsjcpp_core.h"

// MainController
MainController::MainController(const std::string &sWindowName) {
    m_sWindowName = sWindowName;
    m_nWindowWidth = 1280;
    m_nWindowHeight = 720;
    m_pRenderWindow = nullptr;
    TAG = "MainController";
}

bool MainController::initSDL2() {
    if (SDL_Init(SDL_INIT_VIDEO) > 0) {
        std::cerr << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG))) {
        std::cerr << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        return false;
    }
    
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("Failed to init SDL\n");
        exit(1);
    }
    int result = 0;
    int flags = MIX_INIT_MP3;
    if (flags != (result = Mix_Init(flags))) {
        printf("Could not initialize mixer (result: %d).\n", result);
        printf("Mix_Init: %s\n", Mix_GetError());
        exit(1);
    }
    return true;
}

bool MainController::initRenderWindow() {
    
    if (!this->initSDL2()) {
        return false;
    }

    m_pRenderWindow = new RenderWindow(
        m_sWindowName.c_str(),
        m_nWindowWidth,
        m_nWindowHeight
    );
    m_pGameState = new GameState(
        m_nWindowWidth,
        m_nWindowHeight
    );
    return true;
}

RenderWindow *MainController::getWindow() {
    return m_pRenderWindow;
}

GameState *MainController::getGameState() {
    return m_pGameState;
}

CoordXY MainController::getCoordCenter() {
    return CoordXY(
        m_nWindowWidth/2,
        m_nWindowHeight/2
    );
}

bool MainController::initObjects() {

    m_pTextureBackground = m_pRenderWindow->loadTexture("./img/background.png");

    // background
    m_nBackgroundsInRow = 0;
    for (int x = -500; x <= m_nWindowWidth; x += 500) {
        m_nBackgroundsInRow++;
        for (int y = -500; y <= m_nWindowHeight; y += 500) {
            auto pState = new StateBackground(CoordXY(x, y));
            m_vBackgrounds.push_back(pState);
            m_pRenderWindow->addObject(new RenderBackground(pState, m_pTextureBackground, -10));        
        }
    }

    m_vZoidTextures.push_back(
        m_pRenderWindow->loadTexture("./img/ns18zoid.png")
    );
    m_vZoidTextures.push_back(
        m_pRenderWindow->loadTexture("./img/ns18zoid_red.png")
    );
    m_vZoidTextures.push_back(
        m_pRenderWindow->loadTexture("./img/ns18zoid_green.png")
    );
    m_vZoidTextures.push_back(
        m_pRenderWindow->loadTexture("./img/ns18zoid_blue.png")
    );

    for (int i = 0; i < 199; i++) {
        SDL_Texture* pTextureNs18ziod = m_vZoidTextures[i % m_vZoidTextures.size()];

        auto pStateNs18zoid = new StateNs18zoid(CoordXY(m_nWindowWidth/2,m_nWindowHeight/2));
        m_vStates.push_back(pStateNs18zoid);
        int nTextRand = std::rand() % 4;
        m_pRenderWindow->addObject(
            new RenderNs18zoid(
                pStateNs18zoid,
                pTextureNs18ziod,
                1000
            )
        );
    }
    return true;
}

CoordXY MainController::randomDirection() {
    int nSpeed = std::rand() % 15;
    int nSpeed2 = nSpeed*2 + 1;

    int nX = (std::rand() % nSpeed2) - nSpeed;
    int nY = (std::rand() % nSpeed2) - nSpeed;
    
    int iter = 0;
    while (nX == 0 && nY == 0 && iter < 100) {
        nX = (std::rand() % nSpeed2) - nSpeed;
        nY = (std::rand() % nSpeed2) - nSpeed;
        iter++;
    }
    return CoordXY(nX, nY);
}

void MainController::modifyObjects() {
    for (int i0 = 0; i0 < m_vStates.size(); i0++) {
        CoordXY p0 = m_vStates[i0]->getPosition();
        for (int i1 = 0; i1 < m_vStates.size(); i1++) {
            if (i0 == i1) {
                continue;
            }
            CoordXY p1 = m_vStates[i1]->getPosition();
            double dx = p0.x() - p1.x();
            double dy = p0.y() - p1.y();
            double nDistance = sqrt(dx * dx + dy * dy);
            if (nDistance < 20.0) {
                m_vStates[i0]->changeDirection();
                m_vStates[i1]->changeDirection();
            }
        }
    }

    CoordXY step(-10,0); // = randomDirection();
    for (int i = 0; i < m_vBackgrounds.size(); i++) {
        m_vBackgrounds[i]->setStep(step);
        CoordXY pos = m_vBackgrounds[i]->getPosition();
        if (pos.x() + 500 < 0) {
            CoordXY pos1(
                pos.x() + 500*m_nBackgroundsInRow,
                pos.y()
            );
            m_vBackgrounds[i]->setPosition(pos1);
        }
    }
    m_pRenderWindow->modifyObjects(*m_pGameState);
}

void MainController::updateFpsValue(int nFps) {
    std::cout << "FPS: ~" << nFps << std::endl;
}

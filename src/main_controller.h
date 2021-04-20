#pragma once
#include <string>
#include <map>
#include "render_window.h"
#include "render.h"
#include "state_ns18zoid.h"
#include "state_background.h"

class MainController {
    public:
        MainController(const std::string &sWindowName);
        bool initSDL2();
        bool initRenderWindow();
        bool initObjects();
        RenderWindow *getWindow();
        GameState *getGameState();
        CoordXY getCoordCenter();
        CoordXY randomDirection();

        // window
        void modifyObjects();

        void updateFpsValue(int nFps);

    private:
        std::string TAG;

        std::string m_sWindowName;
        int m_nWindowWidth;
        int m_nWindowHeight;
        int m_nBackgroundsInRow;
        RenderWindow *m_pRenderWindow;
        GameState *m_pGameState;

        SDL_Texture* m_pTextureBackground;

        std::vector<StateNs18zoid *> m_vStates;
        std::vector<StateBackground *> m_vBackgrounds;
        std::vector<SDL_Texture*> m_vZoidTextures;
};
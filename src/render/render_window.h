#pragma once

#include <vector>
#include <algorithm>
#include "render_base.h"

class RenderWindow : public IRenderWindow {

    public:
        RenderWindow(const char* p_title, int p_w, int p_h);
        ~RenderWindow();
        virtual void addObject(RenderObject *pObject) override;
        void removeObject(RenderObject *pObject);
        void sortObjectsByPositionZ();

        SDL_Texture* loadTexture(const std::string &sFilePath);
        void cleanUp();
        void clear();
        void modifyObjects(const GameState& state);
        void drawObjects();
        SDL_Renderer* getRenderer();

        void getWindowSize(int* w, int* h);
        
    private:
        bool m_bFullsreeen;
        SDL_Window* m_pWindow;
        SDL_Renderer* m_pRenderer;
        SDL_DisplayMode m_displayMode;
        std::vector<RenderObject *> m_vObjects;
        SDL_Texture* m_pTextureRocket;
        SDL_Texture* m_pTextureBioplast;
};
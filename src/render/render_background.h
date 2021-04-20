
#pragma once
#include "render.h"
#include "state_background.h"

class RenderBackground : public RenderObject {

    public:
        RenderBackground(
            StateBackground *pState,
            SDL_Texture* tex,
            int nPositionZ = 0
        );
        virtual ~RenderBackground();

        virtual void modify(const GameState& state, IRenderWindow* pRenderWindow) override;
        virtual void draw(SDL_Renderer* renderer) override;

    private:
        CoordXY m_coordRender;
        CoordXY m_coordReal;
        long m_nPrevPosition;
        int m_nLifeTime;
        int m_nMaxLifeTime;
        long m_nSpeedAnimation;
        StateBackground *m_pState;

        SDL_Rect m_currentFrame;
        SDL_Texture* m_pTexture;
};
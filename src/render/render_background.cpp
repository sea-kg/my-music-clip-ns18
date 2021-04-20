

#include "render_background.h"
#include <iostream>

// ---------------------------------------------------------------------
// RenderBackground

RenderBackground::RenderBackground(StateBackground *pState, SDL_Texture* tex,  int nPositionZ) 
: RenderObject(nPositionZ) {
    m_pState = pState;
    m_pTexture = tex;
    m_coordReal = m_pState->getPosition();
    m_currentFrame.x = 0;
    m_currentFrame.y = 0;
    m_currentFrame.w = 500;
    m_currentFrame.h = 500;
    m_nPrevPosition = 0;
    m_nLifeTime = 0;
    m_nMaxLifeTime = 10;
    m_nSpeedAnimation = 80;
}

RenderBackground::~RenderBackground() {
    delete m_pState;
}

void RenderBackground::modify(const GameState& state, IRenderWindow* pRenderWindow) {
    long position = state.getElapsedTime() / m_nSpeedAnimation;
    if (m_nPrevPosition == position) {
        m_coordRender = m_pState->getPosition();
        return; // skip - already desition done
    }
    m_pState->move();
    m_nPrevPosition = position;
    m_coordRender = m_pState->getPosition();
};

void RenderBackground::draw(SDL_Renderer* renderer) {
    RenderColor emptyColor(0, 0, 0, 0);
    emptyColor.changeRenderColor(renderer);

    SDL_Rect dst;
    dst.x = m_coordRender.x();
    dst.y = m_coordRender.y();
    dst.w = m_currentFrame.w;
    dst.h = m_currentFrame.h;

    SDL_RenderCopy(renderer, m_pTexture, &m_currentFrame, &dst);
};
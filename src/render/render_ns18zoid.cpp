

#include "render_ns18zoid.h"
#include <iostream>

// ---------------------------------------------------------------------
// RenderNs18zoid

RenderNs18zoid::RenderNs18zoid(StateNs18zoid *pState, SDL_Texture* tex,  int nPositionZ) 
: RenderObject(nPositionZ) {
    m_pState = pState;
    m_pTexture = tex;
    m_coordReal = m_pState->getPosition();
    m_currentFrame.x = 0;
    m_currentFrame.y = 0;
    m_currentFrame.w = 50;
    m_currentFrame.h = 50;
    m_nPrevPosition = 0;
    m_nLifeTime = 0;
    m_nMaxLifeTime = 10;
    m_nSpeedAnimation = 80;
}

RenderNs18zoid::~RenderNs18zoid() {
    delete m_pState;
}

void RenderNs18zoid::modify(const GameState& state, IRenderWindow* pRenderWindow) {
    long position = state.getElapsedTime() / m_nSpeedAnimation;

    if (m_nPrevPosition == position) {
        m_coordRender = m_pState->getPosition();
        return; // skip - already desition done
    }

    m_nPrevPosition = position;

    m_currentFrame.y = (m_nPrevPosition % 10) * 50;

    m_pState->move(
        state.getWindowWidth(),
        state.getWindowHeight()
    );
    m_coordRender = m_pState->getPosition();
    // if (m_coordRender.x() < 0)
};

void RenderNs18zoid::draw(SDL_Renderer* renderer) {
    RenderColor emptyColor(0, 0, 0, 0);
    emptyColor.changeRenderColor(renderer);

    SDL_Rect dst;
    dst.x = m_coordRender.x() - 25;
    dst.y = m_coordRender.y() - 25;
    dst.w = m_currentFrame.w;
    dst.h = m_currentFrame.h;

    SDL_RenderCopy(renderer, m_pTexture, &m_currentFrame, &dst);
};
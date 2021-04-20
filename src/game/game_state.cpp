#include "game_state.h"
#include <SDL.h>
#include <chrono>

long getCurrentTimeInMilliseconds() {
    long nTimeStart = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    return nTimeStart;
}

// ---------------------------------------------------------------------
// GameState

GameState::GameState(int windowWidth, int windowHeight) {
    m_nStartTime = 0;
    m_nElapsedTime = 0;
    m_nWindowWidth = windowWidth;
    m_nWindowHeight = windowHeight;
}

void GameState::init() {
    m_nStartTime = getCurrentTimeInMilliseconds();
}

void GameState::updateElapsedTime() {
    m_nElapsedTime = getCurrentTimeInMilliseconds() - m_nStartTime;
}

long GameState::getElapsedTime() const {
    return m_nElapsedTime;
}

const CoordXY &GameState::getCoordLeftTop() const {
    return m_coordLeftTop;
}

void GameState::setCoordLeftTop(const CoordXY &newCoordLeftTop) {
    m_coordLeftTop = newCoordLeftTop;
}

const int GameState::getWindowWidth() const {
    return m_nWindowWidth;
}

const int GameState::getWindowHeight() const {
    return m_nWindowHeight;
}
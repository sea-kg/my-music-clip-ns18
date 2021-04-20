#pragma once
#include <vector>
#include "coordxy.h"
#include <cstdlib>
#include <iostream>

long getCurrentTimeInMilliseconds();

class GameState {

    public:
        GameState(int windowWidth, int windowHeight);
        void init();
        void updateElapsedTime();
        long getElapsedTime() const;
        const CoordXY &getCoordLeftTop() const;
        void setCoordLeftTop(const CoordXY &);

        const int getWindowWidth() const;
        const int getWindowHeight() const;

    private:
        long m_nElapsedTime;
        long m_nStartTime;
        CoordXY m_coordLeftTop;
        int m_nWindowWidth;
        int m_nWindowHeight;
};

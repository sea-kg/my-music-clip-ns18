#pragma once
#include <vector>
#include "coordxy.h"

class StateNs18zoid {
    public:
        StateNs18zoid(const CoordXY &p0);
        const CoordXY &getPosition();
        void move(
            int nWidth,
            int nHeight
        );
        void changeDirection();

    private:
        CoordXY m_p0;
        CoordXY m_step;
};

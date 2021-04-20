#pragma once
#include <vector>
#include "coordxy.h"

class StateBackground {
    public:
        StateBackground(const CoordXY &p0);
        const CoordXY &getPosition();
        void move();
        void setStep(const CoordXY &step);
        void setPosition(const CoordXY &p0);
    private:
        CoordXY m_p0;
        CoordXY m_step;
};

#include "state_background.h"
#include <cmath>
#include <cstdlib>

// ---------------------------------------------------------------------
// StateBackground

StateBackground::StateBackground(const CoordXY &p0) {
    m_p0 = p0;
}

const CoordXY &StateBackground::getPosition() {
    return m_p0;
}

void StateBackground::move() {
    m_p0 += m_step;
}

void StateBackground::setStep(const CoordXY &step) {
    m_step = step;
}

void StateBackground::setPosition(const CoordXY &p0) {
    m_p0 = p0;
}
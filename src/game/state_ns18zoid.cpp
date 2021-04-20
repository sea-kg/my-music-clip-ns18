#include "state_ns18zoid.h"
#include <cmath>
#include <cstdlib>

// ---------------------------------------------------------------------
// StateNs18zoid

StateNs18zoid::StateNs18zoid(const CoordXY &p0) {
    m_p0 = p0;
    changeDirection();
}

const CoordXY &StateNs18zoid::getPosition() {
    return m_p0;
}

void StateNs18zoid::move(
    int nWidth,
    int nHeight
) {
    CoordXY p0 = m_p0 + m_step;
    int iter = 0;
    while (p0 == m_p0 && iter < 100) {
        changeDirection();
        p0 = m_p0 + m_step;
        iter++;
    }

    iter = 0;
    while ((p0.x() <= 0 || p0.x() >= nWidth || p0.y() <= 0 || p0.y() >= nHeight) && iter < 100) {
        changeDirection();
        p0 = m_p0 + m_step;
        iter++;
    }
    
    m_p0 = p0;
}

void StateNs18zoid::changeDirection() {
    int nSpeed = std::rand() % 15;
    int nSpeed2 = nSpeed*2 + 1;

    int nX = (std::rand() % nSpeed2) - nSpeed;
    int nY = (std::rand() % nSpeed2) - nSpeed;
    
    int iter = 0;
    while (nX == 0 && nY == 0 && iter < 100) {
        nX = (std::rand() % nSpeed2) - nSpeed;
        nY = (std::rand() % nSpeed2) - nSpeed;
        iter++;
    }
    m_step = CoordXY(nX, nY);
}
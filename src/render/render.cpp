#include "render.h"
#include <cmath>
#define PI 3.14159265

// ---------------------------------------------------------------------
// RenderLine

RenderLine::RenderLine(const CoordXY &p1, const CoordXY &p2, const RenderColor &color, int nPositionZ) 
: RenderObject(nPositionZ), m_color(color) {
    m_coord1 = p1;
    m_coord2 = p2;
    m_startCoord1 = p1;
    m_startCoord2 = p2;
}

void RenderLine::modify(const GameState& state, IRenderWindow* pRenderWindow) {
    m_coord1 = m_startCoord1 - state.getCoordLeftTop();
    m_coord2 = m_startCoord2 - state.getCoordLeftTop() ;
}

void RenderLine::draw(SDL_Renderer* renderer) {
    m_color.changeRenderColor(renderer);
    SDL_RenderDrawLine(renderer, m_coord1.x(), m_coord1.y(), m_coord2.x(), m_coord2.y());
}

const CoordXY &RenderLine::getAbsoluteCoord1() {
    return m_startCoord1;
}

const CoordXY &RenderLine::getAbsoluteCoord2() {
    return m_startCoord2;
}

const CoordXY &RenderLine::getCoord1() {
    return m_coord1;
}

const CoordXY &RenderLine::getCoord2() {
    return m_coord2;
}

void RenderLine::updateAbsoluteCoords(const CoordXY &p1, const CoordXY &p2) {
    m_startCoord1 = p1;
    m_startCoord2 = p2;
}

// ---------------------------------------------------------------------
// RenderTriangle

RenderTriangle::RenderTriangle(
    const CoordXY &p1,
    const CoordXY &p2,
    const CoordXY &p3,
    int nPositionZ
) : RenderObject(nPositionZ),
    m_color(255,255,255,255),
    m_line1(p1,p2, m_color),
    m_line2(p2,p3, m_color),
    m_line3(p3,p1, m_color)
{
    // nothing
}

void RenderTriangle::modify(const GameState& state, IRenderWindow* pRenderWindow) {
    m_line1.modify(state, pRenderWindow);
    m_line2.modify(state, pRenderWindow);
    m_line3.modify(state, pRenderWindow);
}

void RenderTriangle::draw(SDL_Renderer* renderer) {
    m_line1.draw(renderer);
    m_line2.draw(renderer);
    m_line3.draw(renderer);
}

// ---------------------------------------------------------------------
// RenderRectTexture

RenderRectTexture::RenderRectTexture(
    const CoordXY &p0, 
    SDL_Texture* tex,
    int nTextureWidth, 
    int nTextureHeight,
    int nPositionZ
) : RenderObject(nPositionZ) {
    m_pTexture = tex;
    m_coordCenter = p0;
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = nTextureWidth;
    currentFrame.h = nTextureHeight;
}

void RenderRectTexture::modify(const GameState& state, IRenderWindow* pRenderWindow) {
    m_coordReal = m_coordCenter - state.getCoordLeftTop();

};

void RenderRectTexture::draw(SDL_Renderer* renderer) {
    SDL_Rect dst;
    // 4 is scale
    dst.x = m_coordReal.x();
    dst.y = m_coordReal.y();
    dst.w = currentFrame.w;
    dst.h = currentFrame.h;

    SDL_RenderCopy(renderer, m_pTexture, &currentFrame, &dst);
};

// ---------------------------------------------------------------------
// RenderTextBlock

RenderAbsoluteTextBlock::RenderAbsoluteTextBlock(const CoordXY &p0, const std::string &sText, int nPositionZ)
: RenderObject(nPositionZ) {
    m_coordCenter = p0;
    m_sText = sText;
    m_sUpdateText = m_sText;
    m_pFont = TTF_OpenFont("./fonts/roboto/Roboto-Black.ttf", 16);
    m_color = {255, 255, 255};
    if (!m_pFont) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        // handle error
    }

    // SDL_Rect currentFrame;
}

void RenderAbsoluteTextBlock::modify(const GameState& state, IRenderWindow* pRenderWindow) {
    // nothing i think
    if (m_sUpdateText != m_sText) {
        m_sText = m_sUpdateText;
    }
};

void RenderAbsoluteTextBlock::draw(SDL_Renderer* renderer) {
    // int w,h;
    // if (TTF_SizeText(font,"Hello World!",&w,&h)) {
        // perhaps print the current TTF_GetError(), the string can't be rendered...
    // } else {
    //    printf("width=%d height=%d\n",w,h);
    // }

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(m_pFont, m_sText.c_str(), m_color);
     // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture
    
    SDL_Rect Message_rect; //create a rect
    Message_rect.x = m_coordCenter.x();  //controls the rect's x coordinate 
    Message_rect.y = m_coordCenter.y(); // controls the rect's y coordinte
    Message_rect.w = surfaceMessage->w; // controls the width of the rect
    Message_rect.h = surfaceMessage->h; // controls the height of the rect

    //Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understand

    //Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

    SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

    //Don't forget to free your surface and texture
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
};

void RenderAbsoluteTextBlock::updateText(const std::string &sNewText) {
    m_sUpdateText = sNewText;
}

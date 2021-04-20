#pragma once
#include "render_window.h"

#include "game_state.h"

#include <vector>
#include <string>
#include <iostream>

class RenderLine : public RenderObject {

    public:
        RenderLine(
            const CoordXY &p1,
            const CoordXY &p2,
            const RenderColor &color,
            int nPositionZ = 0
        );
        virtual void modify(const GameState& state, IRenderWindow* pRenderWindow) override;
        virtual void draw(SDL_Renderer* renderer) override;

        const CoordXY &getAbsoluteCoord1();
        const CoordXY &getAbsoluteCoord2();
        const CoordXY &getCoord1();
        const CoordXY &getCoord2();
        void updateAbsoluteCoords(const CoordXY &p1, const CoordXY &p2);

    private:
        CoordXY m_startCoord1;
        CoordXY m_startCoord2;
        CoordXY m_coord1;
        CoordXY m_coord2;
        RenderColor m_color;
};

class RenderTriangle : public RenderObject {

    public:
        RenderTriangle(
            const CoordXY &p1,
            const CoordXY &p2,
            const CoordXY &p3,
            int nPositionZ = 0
        );
        virtual void modify(const GameState& state, IRenderWindow* pRenderWindow) override;
        virtual void draw(SDL_Renderer* renderer) override;

    private:
        RenderLine m_line1;
        RenderLine m_line2;
        RenderLine m_line3;
        RenderColor m_color;
};

class RenderRectTexture : public RenderObject {

    public:
        RenderRectTexture(
            const CoordXY &p0,
            SDL_Texture* tex,
            int nTextureWidth, 
            int nTextureHeight,
            int nPositionZ = 0
        );
        virtual void modify(const GameState& state, IRenderWindow* pRenderWindow) override;
        virtual void draw(SDL_Renderer* renderer) override;

    private:
        CoordXY m_coordCenter;
        CoordXY m_coordReal;

        SDL_Rect currentFrame;
        SDL_Texture* m_pTexture;
};

class RenderAbsoluteTextBlock : public RenderObject {

    public:
        RenderAbsoluteTextBlock(
            const CoordXY &p0,
            const std::string &sText,
            int nPositionZ = 0
        );
        virtual void modify(const GameState& state, IRenderWindow* pRenderWindow) override;
        virtual void draw(SDL_Renderer* renderer) override;
        void updateText(const std::string &sNewText);

    private:
        CoordXY m_coordCenter;
        std::string m_sText;
        std::string m_sUpdateText;
        TTF_Font* m_pFont;
        SDL_Color m_color;

        SDL_Rect currentFrame;
};


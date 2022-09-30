//
// Created by delmwin on 9/27/22.
//
#pragma once

#include "Component.h"
#include "SDL.h"

class SpriteComponent : public Component {
public:
    explicit SpriteComponent(class Actor *owner, int drawOrder = 100);

    ~SpriteComponent();

    virtual void Draw(SDL_Renderer *renderer);

    virtual void SetTexture(SDL_Texture *texture);

    // Getters
    int GetDrawOrder() const { return _drawOrder; }

    int GetTexHeight() const { return _texHeight; }

    int GetTexWidth() const { return _texWidth; }

protected:
    SDL_Texture *_texture; // Texture that is drawn

    int _drawOrder; // Draw order for painter algorithm

    // Texture dimensions
    int _texWidth;
    int _texHeight;
};
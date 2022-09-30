//
// Created by delmwin on 9/27/22.
//

#pragma once

#include <vector>
#include "SpriteComponent.h"
#include "Math.h"

class BGSpriteComponent : public SpriteComponent {
public:
    explicit BGSpriteComponent(class Actor *owner, int drawOrder = 10);

    void Update(float deltaTime) override;

    void Draw(SDL_Renderer *renderer) override;

    void SetBGTextures(const std::vector<SDL_Texture *> &textures);

    // Getters/Setters
    void SetScreenSize(const Vector2 &size) { _screenSize = size; }

    void SetScrollSpeed(float speed) { _scrollSpeed = speed; }

    float GetScrollSpeed() const { return _scrollSpeed; }

private:
    struct BGTexture {
        SDL_Texture *_texture;
        Vector2 _offset;
    };

    std::vector<BGTexture> _BGTextures;

    Vector2 _screenSize;

    float _scrollSpeed;
};
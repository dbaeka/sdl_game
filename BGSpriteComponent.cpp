//
// Created by delmwin on 9/27/22.
//

#include "BGSpriteComponent.h"
#include "Actor.h"

BGSpriteComponent::BGSpriteComponent(class Actor *owner, int drawOrder) :
        SpriteComponent(owner, drawOrder),
        _scrollSpeed(0.0f) {

}

void BGSpriteComponent::Update(float deltaTime) {
    SpriteComponent::Update(deltaTime);
    for (auto &bg: _BGTextures) {
        // Update x offset
        bg._offset.x += _scrollSpeed * deltaTime;

        // Check if bg x is at a screen size left of the screen x
        // At this point bg would have moved to the left by screen width (-screensize.x)
        // Meaning that if it goes one more left of that, then right of bg is no longer visible
        // Reset to the right of the last bg texture
        if (bg._offset.x < -_screenSize.x) {
            bg._offset.x = (_BGTextures.size() - 1) * _screenSize.x - 1;
        }
    }
}

void BGSpriteComponent::Draw(SDL_Renderer *renderer) {
    if (!_BGTextures.empty() && _owner->GetState() != Actor::EInvisible) {
        SDL_Rect r;
        r.w = static_cast<int>(_screenSize.x * _owner->GetScale());
        r.h = static_cast<int>(_screenSize.y * _owner->GetScale());

        for (auto &bg: _BGTextures) {
            // Center around actor
            r.x = static_cast<int>(_owner->GetPosition().x - r.w / 2 + bg._offset.x);
            r.y = static_cast<int>(_owner->GetPosition().y - r.h / 2 + bg._offset.y);

            // Draw
            SDL_RenderCopyEx(renderer, bg._texture, nullptr, &r,
                             -Math::ToDegrees(_owner->GetRotation()), nullptr,
                             SDL_FLIP_NONE);
        }
    }
}

void BGSpriteComponent::SetBGTextures(const std::vector<SDL_Texture *> &textures) {
    int count = 0;

    for (auto texture: textures) {
        BGTexture temp;
        temp._texture = texture;

        // Each texture is screen width offset
        temp._offset.x = count * _screenSize.x;
        temp._offset.y = 0;
        _BGTextures.emplace_back(temp);
        count++;
    }
}

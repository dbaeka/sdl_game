//
// Created by delmwin on 9/27/22.
//

#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Math.h"

SpriteComponent::SpriteComponent(Actor *owner, int drawOrder) :
        _drawOrder(drawOrder),
        Component(owner),
        _texture(nullptr),
        _texHeight(0),
        _texWidth(0) {
    _owner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent() {
    _owner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::SetTexture(SDL_Texture *texture) {
    _texture = texture;

    // Get width and height of texture
    SDL_QueryTexture(texture, nullptr, nullptr, &_texWidth, &_texHeight);
}

void SpriteComponent::Draw(SDL_Renderer *renderer) {
    if (_texture) {
        SDL_Rect r;
        r.w = static_cast<int>(_texWidth * _owner->GetScale());
        r.h = static_cast<int>(_texHeight * _owner->GetScale());

        // Center around actor
        r.x = static_cast<int>(_owner->GetPosition().x - r.w / 2);
        r.y = static_cast<int>(_owner->GetPosition().y - r.h / 2);

        // Draw
        SDL_RenderCopyEx(renderer, _texture, nullptr, &r,
                         -Math::ToDegrees(_owner->GetRotation()), nullptr,
                         SDL_FLIP_NONE);
    }
}

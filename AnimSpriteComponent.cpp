//
// Created by delmwin on 9/27/22.
//

#include "AnimSpriteComponent.h"

AnimSpriteComponent::AnimSpriteComponent(Actor *owner, int drawOrder) :
        SpriteComponent(owner, drawOrder),
        _currFrame(0.0f),
        _currentAnim("main"),
        _animFPS(24.0f) {
}

void AnimSpriteComponent::Update(float deltaTime) {
    SpriteComponent::Update(deltaTime);

    auto iter = _animations.find(_currentAnim);

    if (iter == _animations.end()) {
        return;
    }

    auto anim = iter->second;

    if (!_animTextures.empty() && anim.totalFrames > 0) {
        _currFrame += _animFPS * deltaTime;
    }

    while (_currFrame >= anim.totalFrames) {
        _currFrame -= anim.totalFrames;
    }

    SetTexture(_animTextures[static_cast<int>(_currFrame + anim.index)]);
}

void AnimSpriteComponent::AddAnimTextures(const std::vector<SDL_Texture *> &textures, const std::string &name) {
    ulong count = _animTextures.size();
    Animation temp = {
            static_cast<int>(textures.size()),
            count,
            name
    };
    _animations.emplace(name, temp);
    _animTextures.insert(_animTextures.end(), textures.begin(), textures.end());
    ResetAnimation(static_cast<int>(_animTextures.size()));
    _currentAnim = name;
}

void AnimSpriteComponent::RemoveAnimTextures(const std::string &name) {
    auto iter = _animations.find(name);
    if (iter != _animations.end()) {
        Animation anim = (*iter).second;
        auto firstIndex = _animTextures.begin() + anim.index;
        _animTextures.erase(firstIndex, firstIndex + anim.totalFrames);

        _animations.erase(name);
    }
}

void AnimSpriteComponent::FlushAnimTextures() {
    ResetAnimation(0);
    _animTextures.clear();
    _animations.clear();
}

void AnimSpriteComponent::ResetAnimation(int frame) {
    if (!_animTextures.empty() && frame < _animTextures.size()) {
        _currFrame = 0.0f;
        SetTexture(_animTextures[frame]);
    }
}

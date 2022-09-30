//
// Created by delmwin on 9/27/22.
//

#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include "SpriteComponent.h"

class AnimSpriteComponent : public SpriteComponent {
public:
    explicit AnimSpriteComponent(class Actor *owner, int drawOrder = 100);

    void Update(float deltaTime) override;

    void AddAnimTextures(const std::vector<SDL_Texture *> &textures, const std::string &name = "main");

    void RemoveAnimTextures(const std::string &name);

    void FlushAnimTextures();

    void ResetAnimation(int frame = 0);

    // Setters/Getters
    float GetAnimFPS() const { return _animFPS; }

    void SetAnimFPS(float fps) { _animFPS = fps; }

private:

    struct Animation {
        int totalFrames;
        ulong index;
        std::string name;
    };

    std::vector<SDL_Texture *> _animTextures;

    std::unordered_map<std::string, Animation> _animations;

    std::string _currentAnim;

    float _currFrame;

    float _animFPS;
};
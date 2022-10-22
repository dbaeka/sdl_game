//
// Created by delmwin on 9/27/22.
//
#pragma once

#include <cstdint>
#include "Actor.h"

class Ship : public Actor {
public:
    explicit Ship(class Game *game);

    void UpdateActor(float deltaTime) override;

    void ActorInput(const uint8_t *keyState) override;

    // Getters
    float GetRightSpeed() const { return _rightSpeed; };

    float GetDownSpeed() const { return _downSpeed; };

private:
    float _rightSpeed;

    float _downSpeed;
};
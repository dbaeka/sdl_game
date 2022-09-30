//
// Created by delmwin on 9/27/22.
//
#pragma once

#include <cstdint>
#include "Actor.h"

class Ship : public Actor {
public:
    Ship(class Game *game);

    void UpdateActor(float deltaTime) override;

    void ProcessKeyboard(const uint8_t *state);


    // Getters
    float GetRightSpeed() const { return _rightSpeed; };

    float GetDownSpeed() const { return _downSpeed; };

private:
    float _rightSpeed;

    float _downSpeed;
};
//
// Created by delmwin on 9/27/22.
//
#pragma once

#include <cstdint>
#include "Actor.h"

class Asteroid : public Actor {
public:
    explicit Asteroid(class Game *game);

    ~Asteroid();

    void UpdateActor(float deltaTime) override;

    class CircleComponent *GetCircle() const { return _circle; }

private:
    class CircleComponent *_circle;

    class MoveComponent *_move;
};
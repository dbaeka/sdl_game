//
// Created by delmwin on 10/20/22.
//

#pragma once

#include "Actor.h"

class Laser : public Actor {
public:
    explicit Laser(class Game *game);

    void UpdateActor(float deltaTime) override;

    class CircleComponent *GetCircle() const { return _circle; }

private:
    float _deathTimer;

    class MoveComponent *_move;

    class CircleComponent *_circle;
};
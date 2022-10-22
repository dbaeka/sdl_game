//
// Created by delmwin on 10/20/22.
//

#pragma once

#include "Actor.h"

class SpaceShip : public Actor {
public:
    explicit SpaceShip(class Game *game);

    void ActorInput(const uint8_t *keyState) override;

    void UpdateActor(float deltaTime) override;

    class CircleComponent *GetCircle() const { return _circle; }

private:
    float _laserCooldown, _respawnTimer;

    class CircleComponent *_circle;
};
//
// Created by delmwin on 10/20/22.
//

#include "Laser.h"
#include "CircleComponent.h"
#include "Game.h"
#include "Asteroid.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"

Laser::Laser(Game *game) :
        Actor(game),
        _deathTimer(2.0f) {
    auto sc = new SpriteComponent(this);
    auto texture = game->GetTexture("Assets/AsteroidsGame/Laser.png");
    sc->SetTexture(texture);

    _move = new MoveComponent(this);
    _move->SetMass(1.0f);

    _circle = new CircleComponent(this);
    _circle->SetRadius(14.0f);
}

void Laser::UpdateActor(float deltaTime) {
    if (GetState() == EActive) {
        _move->AddForce(GetForward() * 10000.0f * _move->GetMass());
    }

    // If we run out of time, laser is dead
    _deathTimer -= deltaTime;
    if (_deathTimer <= 0.0f) {
        SetState(EDead);
    }

    for (auto asteroid: GetGame()->GetAsteroids()) {
        if (Intersect(*_circle, *(asteroid->GetCircle()))) {
            SetState(EDead);
            asteroid->SetState(EDead);
            break;
        }
    }
}

//
// Created by delmwin on 10/13/22.
//

#include "Asteroid.h"
#include "Game.h"
#include "GameMath.h"
#include "Random.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "CircleComponent.h"

Asteroid::Asteroid(Game *game) : Actor(game) {
    // Init random position
    Vector2 pos = Random::GetVector(Vector2::Zero, Vector2(1024.0f, 768.0f));
    SetPosition(pos);
    SetRotation(Random::GetFloat(0.0f, Math::TwoPI));

    // Create sprite component
    auto sc = new SpriteComponent(this);
    sc->SetTexture(game->GetTexture("Assets/AsteroidsGame/Asteroid.png"));

    // Create move component
    _move = new MoveComponent(this);
    _move->SetMass(10.0f);

    _circle = new CircleComponent(this);
    _circle->SetRadius(40.0f);

    // Add to mAsteroids in game
    game->AddAsteroid(this);
}

Asteroid::~Asteroid() {
    GetGame()->RemoveAsteroid(this);
}

void Asteroid::UpdateActor(float deltaTime) {
    _move->AddForce(GetForward() * 1000.0f * _move->GetMass());

    // (Screen wrapping code only for asteroids)
    auto position = GetPosition();
    if (position.x <= 0.0f) {
        position.x = 1022.0f;
    } else if (position.x >= 1024.0f) {
        position.x = 2.0f;
    }

    if (position.y <= 0.0f) {
        position.y = 766.0f;
    } else if (position.y >= 768.0f) {
        position.y = 2.0f;
    }

    SetPosition(position);
}

//
// Created by delmwin on 10/20/22.
//

#include "SpaceShip.h"
#include "Game.h"
#include "InputComponent.h"
#include "SpriteComponent.h"
#include "CircleComponent.h"
#include "Laser.h"
#include "Asteroid.h"

SpaceShip::SpaceShip(Game *game) : Actor(game), _laserCooldown(0.0f), _respawnTimer(0.0f) {
    auto sprite = new SpriteComponent(this, 150);
    auto texture = game->GetTexture("Assets/AsteroidsGame/Ship.png");
    sprite->SetTexture(texture);

    auto ic = new InputComponent(this);
    ic->SetForwardKey(SDL_SCANCODE_W);
    ic->SetBackKey(SDL_SCANCODE_S);
    ic->SetClockwiseKey(SDL_SCANCODE_D);
    ic->SetCounterClockwiseKey(SDL_SCANCODE_A);

    ic->SetMaxAngularSpeed(Math::TwoPI);
    ic->SetMaxForwardAcceleration(1000.0f);
    ic->SetMass(100.0f);

    _circle = new CircleComponent(this);
    _circle->SetRadius(40.0f);
}

void SpaceShip::ActorInput(const uint8_t *keyState) {
    if (keyState[SDL_SCANCODE_SPACE] && _laserCooldown <= 0) {
        auto laser = new Laser(GetGame());
        laser->SetPosition(GetPosition());
        laser->SetRotation(GetRotation());

        // Reset cool down. Half a second
        _laserCooldown = 0.5f;
    }
}

void SpaceShip::UpdateActor(float deltaTime) {
    _laserCooldown -= deltaTime;
    _respawnTimer -= deltaTime;

    if (_respawnTimer <= 0) {
        SetState(EActive);
    }

    for (auto asteroid: GetGame()->GetAsteroids()) {
        if (GetState() == EActive && Intersect(*_circle, *(asteroid->GetCircle()))) {
            SetPosition(Vector2(1024.0 / 2, 768.0f / 2));
            SetRotation(0.0f);
            _respawnTimer = 2.0f;
            SetState(EInvisible);
            break;
        }
    }
}

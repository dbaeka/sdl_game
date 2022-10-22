//
// Created by delmwin on 9/27/22.
//

#include "Ship.h"
#include "AnimSpriteComponent.h"
#include "Game.h"

Ship::Ship(class Game *game) :
        Actor(game),
        _rightSpeed(0.0f),
        _downSpeed(0.0f) {
    auto *sprite = new AnimSpriteComponent(this);
    std::vector<SDL_Texture *> textures = {
            game->GetTexture("Assets/ShipGame/Ship01.png"),
            game->GetTexture("Assets/ShipGame/Ship02.png"),
            game->GetTexture("Assets/ShipGame/Ship03.png"),
            game->GetTexture("Assets/ShipGame/Ship04.png"),
    };
    sprite->AddAnimTextures(textures);
}

void Ship::UpdateActor(float deltaTime) {
    Actor::UpdateActor(deltaTime);

    // Update Position
    Vector2 pos = GetPosition();

    pos.x += _rightSpeed * deltaTime;
    pos.y += _downSpeed * deltaTime;

    // Restrict To Left Half Screen
    if (pos.x < 25.0f) {
        pos.x = 25.0f;
    } else if (pos.x > 500.0f) {
        pos.x = 500.0f;
    }

    if (pos.y < 25.0f) {
        pos.y = 25.0f;
    } else if (pos.y > 743.0f) {
        pos.y = 743.0f;
    }

    SetPosition(pos);
}

void Ship::ActorInput(const uint8_t *keyState) {
    _rightSpeed = _downSpeed = 0.0f;

    // Left / Right
    if (keyState[SDL_SCANCODE_A]) {
        _rightSpeed -= 250.0f;
    }

    if (keyState[SDL_SCANCODE_D]) {
        _rightSpeed += 250.0f;
    }

    // Up / Down
    if (keyState[SDL_SCANCODE_W]) {
        _downSpeed -= 250.0f;
    }

    if (keyState[SDL_SCANCODE_S]) {
        _downSpeed += 250.0f;
    }
}

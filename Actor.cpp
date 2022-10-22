//
// Created by delmwin on 9/26/22.
//

#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(struct Game *game) :
        _game(game),
        _state(EActive),
        _position(Vector2::Zero),
        _scale(1.0f),
        _rotation(0.0f) {
    game->AddActor(this);
}

Actor::~Actor() {
    _game->RemoveActor(this);

    // Delete Components
    while (!_components.empty()) {
        delete _components.back();
    }
}

void Actor::Update(float deltaTime) {
    if (_state == EActive || _state == EInvisible) {
        UpdateComponents(deltaTime);
        UpdateActor(deltaTime);
    }
}

void Actor::UpdateComponents(float deltaTime) {
    for (auto component: _components) {
        component->Update(deltaTime);
    }
}

void Actor::UpdateActor(float deltaTime) {
}

void Actor::AddComponent(Component *component) {
    // Insert component in right place
    int order = component->GetUpdateOrder();
    auto iter = _components.begin();
    for (; iter != _components.end(); ++iter) {
        if (order < (*iter)->GetUpdateOrder()) {
            break;
        }
    }
    // Insert elem before iter
    _components.insert(iter, component);
}

void Actor::RemoveComponent(Component *component) {
    auto iter = std::find(_components.begin(), _components.end(), component);
    if (iter != _components.end()) {
        _components.erase(iter);
    }
}

Vector2 Actor::GetForward() const {
    // Negate y-component for SDL
    return Vector2(Math::Cos(_rotation), -Math::Sin(_rotation));
}

void Actor::ProcessInput(const uint8_t *keyState) {
    if (_state == EActive) {
        for (auto comp: _components) {
            comp->ProcessInput(keyState);
        }
        ActorInput(keyState);
    }
}

void Actor::ActorInput(const uint8_t *keyState) {
}

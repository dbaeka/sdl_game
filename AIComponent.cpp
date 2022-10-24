//
// Created by delmwin on 10/22/22.
//

#include "AIComponent.h"
#include "Actor.h"
#include "AIState.h"
#include <SDL.h>

AIComponent::AIComponent(Actor *owner) : Component(owner), _currentState(nullptr) {
}

void AIComponent::Update(float deltaTime) {
    if (_currentState) {
        _currentState->Update(deltaTime);
    }
}

void AIComponent::RegisterState(struct AIState *state) {
    _stateMap.emplace(state->GetName(), state);
}

void AIComponent::ChangeState(const std::string &name) {
    if (_currentState) {
        _currentState->OnExit();
    }

    auto iter = _stateMap.find(name);
    if (iter != _stateMap.end()) {
        _currentState = iter->second;
        _currentState->OnEnter();
    } else {
        SDL_Log("Could not find AIState %s in state map", name.c_str());
        _currentState = nullptr;
    }
}

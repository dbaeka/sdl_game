//
// Created by delmwin on 10/22/22.
//

#pragma once

#include "Component.h"
#include <string>
#include <unordered_map>

class AIComponent : public Component {
public:
    explicit AIComponent(class Actor *owner);

    void Update(float deltaTime) override;

    void ChangeState(const std::string &name);

    // Add new state to map
    void RegisterState(class AIState *state);

private:
    std::unordered_map<std::string, class AIState *> _stateMap;

    class AIState *_currentState;
};
//
// Created by delmwin on 10/22/22.
//

#pragma once

class AIState {
public:
    explicit AIState(class AIComponent *owner) : _owner(owner) {};

    virtual void Update(float deltaTime) = 0;

    virtual void OnEnter() = 0;

    virtual void OnExit() = 0;

    // Getter
    virtual const char *GetName() const = 0;

protected:
    class AIComponent *_owner;
};
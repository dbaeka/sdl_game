//
// Created by delmwin on 10/20/22.
//

#include "InputComponent.h"
#include "Actor.h"

InputComponent::InputComponent(class Actor *owner) : MoveComponent(owner) {
}

void InputComponent::ProcessInput(const uint8_t *keyState) {
    float forwardAcceleration = 0.0f;

    if (keyState[_forwardKey]) {
        forwardAcceleration += _maxForwardAcceleration;
    }

    if (keyState[_backKey]) {
        forwardAcceleration -= _maxForwardAcceleration;
    }

    AddForce(_owner->GetForward() * GetMass() * forwardAcceleration);

    float angularSpeed = 0.0f;

    if (keyState[_clockwiseKey]) {
        angularSpeed += _maxAngularSpeed;
    }

    if (keyState[_counterClockwiseKey]) {
        angularSpeed -= _maxAngularSpeed;
    }

    SetAngularSpeed(angularSpeed);
}

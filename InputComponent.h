//
// Created by delmwin on 10/20/22.
//

#pragma once

#include "MoveComponent.h"

class InputComponent : public MoveComponent {
public:
    explicit InputComponent(class Actor *owner);

    void ProcessInput(const uint8_t *keyState) override;

    // Getters and setters
    float GetMaxForwardAcceleration() const { return _maxForwardAcceleration; }

    float GetMaxAngularSpeed() const { return _maxAngularSpeed; }

    int GetForwardKey() const { return _forwardKey; }

    int GetBackKey() const { return _backKey; }

    int GetClockwiseKey() const { return _clockwiseKey; }

    int GetCounterClockwiseKey() const { return _counterClockwiseKey; }

    void SetCounterClockwiseKey(int key) { _counterClockwiseKey = key; }

    void SetClockwiseKey(int key) { _clockwiseKey = key; }

    void SetForwardKey(int key) { _forwardKey = key; }

    void SetBackKey(int key) { _backKey = key; }

    void SetMaxAngularSpeed(float speed) { _maxAngularSpeed = speed; }

    void SetMaxForwardAcceleration(float acceleration) { _maxForwardAcceleration = acceleration; }

private:
    float _maxForwardAcceleration{}, _maxAngularSpeed{};

    int _forwardKey{}, _backKey{};

    int _clockwiseKey{}, _counterClockwiseKey{};
};
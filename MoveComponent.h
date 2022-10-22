//
// Created by delmwin on 10/13/22.
//

#pragma once

#include <GameMath.h>
#include "Component.h"

class MoveComponent : public Component {
public:
    explicit MoveComponent(class Actor *owner, int updateOrder = 10);

    void Update(float deltaTime) override;

    // Getters and setters
    float GetAngularSpeed() const { return _angularSpeed; }

    void SetAngularSpeed(float speed) { _angularSpeed = speed; }

    float GetMass() const { return _mass; }

    void SetMass(float mass) { _mass = mass; }

    const Vector2 &GetNetForce() const { return _netForce; }

    const Vector2 &GetVelocity() const { return _velocity; }

    void SetNetForce(const Vector2 &force) { _netForce = force; }

    void AddForce(const Vector2 &force) { _netForce += force; }

    void SetVelocity(const Vector2 &velocity) { _velocity = velocity; }

private:
    float _angularSpeed;

    float _mass;

    Vector2 _netForce, _velocity;
};

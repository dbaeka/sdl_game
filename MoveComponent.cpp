//
// Created by delmwin on 10/13/22.
//

#include "MoveComponent.h"
#include <GameMath.h>
#include "Actor.h"

MoveComponent::MoveComponent(class Actor *owner, int updateOrder) :
        Component(owner, updateOrder),
        _angularSpeed(0.0f),
        _mass(0.0f) {}

void MoveComponent::Update(float deltaTime) {
    if (!Math::NearZero(_angularSpeed)) {
        float rot = _owner->GetRotation();
        rot += _angularSpeed * deltaTime;
        _owner->SetRotation(rot);
    }

    if (!Math::NearZero(_mass)) {
        Vector2 acceleration = _netForce / _mass;
        _velocity = acceleration * deltaTime;
        Vector2 position = _velocity * deltaTime;
        position += _owner->GetPosition();

        _owner->SetPosition(position);

        _netForce = Vector2::Zero;
    }
}

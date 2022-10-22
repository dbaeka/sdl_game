//
// Created by delmwin on 10/20/22.
//

#include "CircleComponent.h"
#include "Actor.h"

CircleComponent::CircleComponent(Actor *owner) :
        Component(owner),
        _radius(0.0f) {
}

const Vector2 &CircleComponent::GetCenter() const {
    return _owner->GetPosition();
}

float CircleComponent::GetRadius() const {
    return _radius * _owner->GetScale();
}

bool Intersect(const CircleComponent &a, const CircleComponent &b) {
    // Calculate distance squared
    Vector2 distance = a.GetCenter() - b.GetCenter();
    float distanceSq = distance.LengthSquared();

    // Calculate radii squared
    float radiiSum = a.GetRadius() + b.GetRadius();
    float radiiSq = radiiSum * radiiSum;

    return distanceSq <= radiiSq;
}
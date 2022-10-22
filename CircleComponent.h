//
// Created by delmwin on 10/20/22.
//

#pragma once

#include <GameMath.h>
#include "Component.h"

class CircleComponent : public Component {
public:
    explicit CircleComponent(class Actor *owner);

    // Getters and Setters
    void SetRadius(float radius) { _radius = radius; }

    float GetRadius() const;

    const Vector2 &GetCenter() const;

private:
    float _radius;
};

bool Intersect(const CircleComponent &a, const CircleComponent &b);
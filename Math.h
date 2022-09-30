//
// Created by delmwin on 9/26/22.
//

#pragma once

class Vector2 {
public:
    float x;
    float y;

    Vector2() : x(0.0f), y(0.0f) {}

    explicit Vector2(float x, float y) : x(x), y(y) {}

    static const Vector2 Zero;
};

namespace Math {
    const float PI = 3.1415926535f;

    inline float ToDegrees(float radians) {
        return radians * 180.0f / PI;
    }
}



#pragma once

namespace p2d
{
    struct Vector2
    {
        float x {0}, y {0};

        Vector2() = default;
        Vector2(float _x,
                float _y);

        Vector2 operator+(const Vector2& _lhs);
        Vector2 operator-(const Vector2& _lhs);
        Vector2 operator*(float _scalar);
        Vector2 operator/(float _scalar);

        Vector2& operator+=(const Vector2& _lhs);
        Vector2& operator-=(const Vector2& _lhs);
        Vector2& operator*=(float _scalar);
        Vector2& operator/=(float _scalar);
    };
}



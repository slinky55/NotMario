#include <Physics/Math/Vector2.h>

namespace p2d
{
    Vector2::Vector2(float _x,
                     float _y)
                     :
                     x(_x),
                     y(_y)
    {
    }

    Vector2 Vector2::operator+(const Vector2& _lhs)
    {
        return {x + _lhs.x, y + _lhs.y};
    }

    Vector2 Vector2::operator-(const Vector2& _lhs)
    {
        return {x - _lhs.x, y - _lhs.y};
    }

    Vector2 Vector2::operator*(float _scalar)
    {
        return {x * _scalar, y * _scalar};
    }

    Vector2 Vector2::operator/(float _scalar)
    {
        return {x / _scalar, y / _scalar};
    }


    Vector2& Vector2::operator+=(const Vector2& _lhs)
    {
        x += _lhs.x;
        y += _lhs.y;
        return *this;
    }

    Vector2& Vector2::operator-=(const Vector2& _lhs)
    {
        x -= _lhs.x;
        y -= _lhs.y;
        return *this;
    }

    Vector2& Vector2::operator*=(float _scalar)
    {
        x *= _scalar;
        y *= _scalar;
        return *this;
    }

    Vector2& Vector2::operator/=(float _scalar)
    {
        x /= _scalar;
        y /= _scalar;
        return *this;
    }
}
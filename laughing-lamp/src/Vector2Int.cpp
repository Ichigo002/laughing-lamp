#include "Vector2Int.h"

Vector2Int::Vector2Int()
{
    x = 0;
    y = 0;
}

Vector2Int::Vector2Int(int x, int y)
{
    set(x, y);
}

void Vector2Int::set(int x, int y)
{
    this->x = x;
    this->y = y;
}

Vector2Int& operator+(Vector2Int& vec1, const Vector2Int& vec2)
{
    vec1.x += vec2.x;
    vec1.y += vec2.y;
    return vec1;
}
Vector2Int& operator-(Vector2Int& vec1, const Vector2Int& vec2)
{
    vec1.x -= vec2.x;
    vec1.y -= vec2.y;
    return vec1;
}
Vector2Int& operator*(Vector2Int& vec1, const Vector2Int& vec2)
{
    vec1.x *= vec2.x;
    vec1.y *= vec2.y;
    return vec1;
}
Vector2Int& operator/(Vector2Int& vec1, const Vector2Int& vec2)
{
    vec1.x /= vec2.x;
    vec1.y /= vec2.y;
    return vec1;
}

std::ostream& operator<<(std::ostream& stream, const Vector2Int& vec)
{
    stream << "(" << vec.x << ", " << vec.y << ")";
    return stream;

}
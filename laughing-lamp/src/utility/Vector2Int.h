#ifndef VECTOR2INT_H
#define VECTOR2INT_H

#include <iostream>

class Vector2Int
{
public:
    Vector2Int();
    Vector2Int(int x, int y);

    void set(int x, int y);

    friend Vector2Int operator+(const Vector2Int& vec1, const int& i);
    friend Vector2Int operator-(const Vector2Int& vec1, const int& i);
    friend Vector2Int operator*(const Vector2Int& vec1, const int& i);
    friend Vector2Int operator/(const Vector2Int& vec1, const int& i);

    friend Vector2Int operator+=(const Vector2Int& vec1, const int& i);
    friend Vector2Int operator-=(const Vector2Int& vec1, const int& i);
    friend Vector2Int operator*=(const Vector2Int& vec1, const int& i);
    friend Vector2Int operator/=(const Vector2Int& vec1, const int& i);

    friend Vector2Int operator+(const Vector2Int& vec1, const Vector2Int& vec2);
    friend Vector2Int operator-(const Vector2Int& vec1, const Vector2Int& vec2);
    friend Vector2Int operator*(const Vector2Int& vec1, const Vector2Int& vec2);
    friend Vector2Int operator/(const Vector2Int& vec1, const Vector2Int& vec2);

    friend bool operator==(const Vector2Int& vec1, const Vector2Int& vec2);
    
    friend Vector2Int operator+=(const Vector2Int& vec1, const Vector2Int& vec2);
    friend Vector2Int operator-=(const Vector2Int& vec1, const Vector2Int& vec2);
    friend Vector2Int operator*=(const Vector2Int& vec1, const Vector2Int& vec2);
    friend Vector2Int operator/=(const Vector2Int& vec1, const Vector2Int& vec2);
    
    friend std::ostream& operator<<(std::ostream& stream, const Vector2Int& vec);

    int x;
    int y;
};

#endif
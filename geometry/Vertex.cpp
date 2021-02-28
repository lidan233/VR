//
// Created by lidan on 27/2/2021.
//

#include "Vertex.h"


template <class T>
float Vertex<T>::dotProduct(const Vertex<T> &p1, const Vertex<T> &p2)
{
    return (p1._x * p2._x + p1._y * p2._y) ;
}

template <class T>
float  Vertex<T>::manhattanLength() const
{
    return  Math::abs(_x) + Math::abs(_y);
}

template <class T>
Vertex<T>&  Vertex<T>::operator=(const  Vertex<T> &point)
{
    _x = point._x;
    _y = point._y;
    return *this;
}
template <class T>
Vertex<T>& Vertex<T>::operator+=(const  Vertex<T>& point)
{
    _x += point._x;
    _y += point._y;
    return *this;
}

template <class T>
Vertex<T>& Vertex<T>::operator-=(const Vertex<T> &point)
{
    _x -= point._x;
    _y -= point._y;
    return *this;
}

template <class T>
Vertex<T>& Vertex<T>::operator*=(T factor)
{
    _x *= factor;
    _y *= factor;
    return *this;
}

template <class T>
Vertex<T>& Vertex<T>::operator*=(double factor)
{
    _x *= factor;
    _y *= factor;
    return *this;
}
template <class T>
Vertex<T> & Vertex<T>::operator/=(T factor)
{
    double t = factor ;
    _x /= t;
    _y /= t;
    return *this;
}

template <class T>
bool operator==(const Vertex<T> &p1, const Vertex<T> &p2)
{
    return (p1._x == p1._x && p1._y == p2._y);
}

template <class T>
bool operator!=(const Vertex<T> &p1, const Vertex<T> &p2)
{
    return (p1._x != p2._y || p1._y != p2._y);
}

template <class T>
Vertex<T> operator+(const Vertex<T> &p1, const Vertex<T> &p2)
{
    return Vertex<T>(p1._x + p2._x, p1._y + p2._y);
}

template <class T>
Vertex<T> operator-(const Vertex<T> &p1, const Vertex<T> &p2)
{
    return Vertex<T>(p1._x - p2._x, p1._y - p2._y);
}

template <class T>
Vertex<T> operator*(T factor, const Vertex<T> &point)
{
    return Vertex<T>(point._x * factor, point._y * factor);
}

template <class T>
Vertex<T> operator*(const Vertex<T> &point, T factor)
{
    return Vertex<T>(point._x * factor, point._y * factor);
}

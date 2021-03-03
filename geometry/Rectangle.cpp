//
// Created by lidan on 2021/2/28.
//

#include "Rectangle.h"

template <class T>
void Rectangle<T>::setTop(T pos)
{
    T diff = pos - _y;
    _y += diff;
    _h -= diff;
}

template <class T>
void Rectangle<T>::setLeft(T pos)
{
    T diff = pos - _x;
    _x += diff;
    _w -= diff;
}

template <class T>
void Rectangle<T>::setCenter(const Vertex<T> &point)
{
    _x = point.x() - (_w / 2);
    _y = point.y() - (_h / 2);
}

template <class T>
void Rectangle<T>::setRectangle(const Rectangle<T> &rect)
{
    _x = rect._x;
    _y = rect._y;
    _w = rect._w;
    _h = rect._h;
}

template <class T>
void Rectangle<T>::setRectangle(T x, T y, T w, T h)
{
    _x = x;
    _y = y;
    _w = w;
    _h = h;
}

template <class T>
bool Rectangle<T>::contains(const Rectangle<T> &rect) const
{
    return _x <= rect._x && _x + _w >= rect._x + rect._w &&
           _y <= rect._y && _y + _h >= rect._y + rect._h;
}

template <class T>
void Rectangle<T>::inflate(T width, T height)
{
    _x -= width;
    _y -= height;
    _w += 2.0f * width;
    _h += 2.0f * height;
}

template <class T>
Rectangle<T> Rectangle<T>::intersects(const Rectangle<T> &rect1, const Rectangle<T> &rect2)
{
    int x1 = Math::max(rect1._x, rect2._x);
    int x2 = Math::min(rect1._x + rect1._w, rect2._x + rect2._w);
    int y1 = Math::max(rect1._y, rect2._y);
    int y2 = Math::min(rect1._y + rect1._h, rect2._y + rect2._h);

    if (x2 >= x1 && y2 >= y1)
        return Rectangle<T>(x1, y1, x2 - x1, y2 - y1);
    else
        return Rectangle<T>(0.0f, 0.0f, 0.0f, 0.0f);
}

template <class T>
Rectangle<T> Rectangle<T>::unions(const Rectangle<T> &rect1, const Rectangle<T> &rect2)
{
    int x1 = Math::min(rect1._x, rect2._x);
    int x2 = Math::max(rect1._x + rect1._w, rect2._x + rect2._w);
    int y1 = Math::min(rect1._y, rect2._y);
    int y2 = Math::max(rect1._y + rect1._h, rect2._y + rect2._h);

    if (x2 >= x1 && y2 >= y1)
        return Rectangle<T>(x1, y1, x2 - x1, y2 - y1);
    else
        return Rectangle<T>(0.0f, 0.0f, 0.0f, 0.0f);
}

template <class T>
Rectangle<T> &Rectangle<T>::operator=(const Rectangle<T> &rect)
{
    _x = rect._x;
    _y = rect._y;
    _w = rect._w;
    _h = rect._h;
    return *this;
}

template <class T>
bool operator==(const Rectangle<T> &rect1, const Rectangle<T> &rect2)
{
    return (rect1._x == rect2._x &&
            rect1._y == rect2._y &&
            rect1._w == rect2._w &&
            rect1._h == rect2._h);
}

template <class T>
bool operator!=(const Rectangle<T> &rect1, const Rectangle<T> &rect2)
{
    return (rect1._x != rect2._x ||
            rect1._y != rect2._y ||
            rect1._w != rect2._w ||
            rect1._h != rect2._h);
}

//
// Created by lidan on 2021/2/28.
//

#include "Rectangle.h"

template <class T>
void RectangleF<T>::setTop(T pos)
{
    T diff = pos - _y;
    _y += diff;
    _h -= diff;
}

template <class T>
void RectangleF<T>::setLeft(T pos)
{
    T diff = pos - _x;
    _x += diff;
    _w -= diff;
}

template <class T>
void RectangleF<T>::setCenter(const Vertex<T> &point)
{
    _x = point.x() - (_w / 2);
    _y = point.y() - (_h / 2);
}

template <class T>
void RectangleF<T>::setRectangle(const RectangleF<T> &rect)
{
    _x = rect._x;
    _y = rect._y;
    _w = rect._w;
    _h = rect._h;
}

template <class T>
void RectangleF<T>::setRectangle(T x, T y, T w, T h)
{
    _x = x;
    _y = y;
    _w = w;
    _h = h;
}

template <class T>
bool RectangleF<T>::contains(const RectangleF<T> &rect) const
{
    return _x <= rect._x && _x + _w >= rect._x + rect._w &&
           _y <= rect._y && _y + _h >= rect._y + rect._h;
}

template <class T>
void RectangleF<T>::inflate(T width, T height)
{
    _x -= width;
    _y -= height;
    _w += 2.0f * width;
    _h += 2.0f * height;
}

template <class T>
RectangleF<T> RectangleF<T>::intersects(const RectangleF<T> &rect1, const RectangleF<T> &rect2)
{
    int x1 = Math::max(rect1._x, rect2._x);
    int x2 = Math::min(rect1._x + rect1._w, rect2._x + rect2._w);
    int y1 = Math::max(rect1._y, rect2._y);
    int y2 = Math::min(rect1._y + rect1._h, rect2._y + rect2._h);

    if (x2 >= x1 && y2 >= y1)
        return RectangleF<T>(x1, y1, x2 - x1, y2 - y1);
    else
        return RectangleF<T>(0.0f, 0.0f, 0.0f, 0.0f);
}

template <class T>
RectangleF<T> RectangleF<T>::unions(const RectangleF<T> &rect1, const RectangleF<T> &rect2)
{
    int x1 = Math::min(rect1._x, rect2._x);
    int x2 = Math::max(rect1._x + rect1._w, rect2._x + rect2._w);
    int y1 = Math::min(rect1._y, rect2._y);
    int y2 = Math::max(rect1._y + rect1._h, rect2._y + rect2._h);

    if (x2 >= x1 && y2 >= y1)
        return RectangleF<T>(x1, y1, x2 - x1, y2 - y1);
    else
        return RectangleF<T>(0.0f, 0.0f, 0.0f, 0.0f);
}

template <class T>
RectangleF<T> &RectangleF<T>::operator=(const RectangleF<T> &rect)
{
    _x = rect._x;
    _y = rect._y;
    _w = rect._w;
    _h = rect._h;
    return *this;
}

template <class T>
bool operator==(const RectangleF<T> &rect1, const RectangleF<T> &rect2)
{
    return (rect1._x == rect2._x &&
            rect1._y == rect2._y &&
            rect1._w == rect2._w &&
            rect1._h == rect2._h);
}

template <class T>
bool operator!=(const RectangleF<T> &rect1, const RectangleF<T> &rect2)
{
    return (rect1._x != rect2._x ||
            rect1._y != rect2._y ||
            rect1._w != rect2._w ||
            rect1._h != rect2._h);
}

//
// Created by lidan on 2021/2/28.
//

#include "Size.h"

template <class T>
Size<T>& Size<T>::operator=(const Size<T> &size)
{
    _width = size._width;
    _height = size._height;
    return *this;
}

template <class T>
Size<T>& Size<T>::operator+=(const Size<T> &size)
{
    _width += size._width;
    _height += size._height;
    return *this;
}

template <class T>
Size<T>& Size<T>::operator-=(const Size<T>& size)
{
    _width -= size._width;
    _height -= size._height;
    return *this;
}

template <class T>
 bool operator==(const Size<T> &s1, const Size<T>& s2)
{
    return (s1._width == s2._width && s1._height == s2._height);
}

template <class T>
 bool operator!=(const Size<T> &s1, const Size<T>& s2)
{
    return (s1._width != s2._width || s1._height != s2._height);
}

template <class T>
Size<T> operator+(const Size<T>& s1, const Size<T>& s2)
{
    return (s1._width != s2._width || s1._height != s2._height);
}

template <class T>
Size<T> operator-(const Size<T>& s1, const Size<T>& s2)
{
    return (s1._width != s2._width || s1._height != s2._height);
}



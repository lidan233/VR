//
// Created by lidan on 2021/2/28.
//

#ifndef VR_SIZE_H
#define VR_SIZE_H

#include "EigenLidan.h"

template <class T>
class Size {
private:
    T _height = 0 , _width = 0 ;
public:
    static_assert(is_for_Lvec<T>::value, "type parameter of this class must derive from basic");
    Size(): _height(0), _width(0) {}
    Size(T height, T width) { this->_height = height ; this->_width = width ; }
    ~Size() {}

    inline T width() { return _width; }
    inline T height() { return _height; }

    inline void setWidth(T width) { _width = width ;}
    inline void setHeight(T height) { _height = height ; }
    inline bool isEmpty() const { return _height * _width <= 0 || _height <= 0 || _width <= 0;}
    inline bool isValid() const { return _height >= 0 &&  _width >= 0 ; }

    inline T area() const { return _width * _height ;}
    inline void transpose() { T temp = _width; _width = _height ; _height = temp ; }

    Size& operator=(const Size &size) ;
    Size& operator+=(const Size &size) ;
    Size& operator-=(const Size& size) ;

    friend bool operator==(const Size &s1, const Size& s2) ;
    friend bool operator!=(const Size &s1, const Size& s2) ;

    friend Size operator+(const Size& s1, const Size& s2) ;
    friend Size operator-(const Size& s1, const Size& s2) ;
};


#endif //VR_SIZE_H

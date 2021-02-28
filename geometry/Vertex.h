//
// Created by lidan on 27/2/2021.
//

#ifndef VR_VERTEX_H
#define VR_VERTEX_H
#include "Lmath.h"

template <class T>
class Vertex {
private:
    T _x, _y ;
public:
    inline Vertex(): _x(0), _y(0)
    {}

    inline Vertex(T x, T y)
            : _x(x), _y(y)
    {}

    inline Vertex(const Vertex<T> &point)
            : _x(point._x), _y(point._y)
    {}

    ~Vertex()
    {}

    inline T x() const { return _x; }
    inline T y() const { return _y; }

    inline void setX(T x) { _x = x; }
    inline void setY(T y) { _y = y; }
    inline void translate(T dx, T dy) { _x += dx; _y += dy; }

    float dotProduct(const Vertex<T> &p1, const Vertex<T> &p2);
    float manhattanLength() const;


    Vertex<T> &operator=(const Vertex<T> &point);
    Vertex<T> &operator+=(const Vertex<T> &point);
    Vertex<T> &operator-=(const Vertex<T> &point);
    Vertex<T> &operator*=(T factor);
    Vertex<T> &operator*=(double factor);
    Vertex<T> &operator/=(T factor);

    friend bool operator==(const Vertex<T> &p1, const Vertex<T> &p2);
    friend bool operator!=(const Vertex<T> &p1, const Vertex<T> &p2);

    friend Vertex<T> operator+(const Vertex<T> &p1, const Vertex<T> &p2);
    friend Vertex<T> operator-(const Vertex<T> &p1, const Vertex<T> &p2);
    friend Vertex<T> operator*(T factor, const Vertex<T> &point);
    friend Vertex<T> operator*(const Vertex<T> &point, T factor);


};


#endif //VR_VERTEX_H

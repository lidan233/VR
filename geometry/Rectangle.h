//
// Created by lidan on 2021/2/28.
//

#ifndef VR_RECTANGLE_H
#define VR_RECTANGLE_H
#include "Vertex.h"
#include "Size.h"

template <class T> 
class RectangleF {
private:
    T _x,_y ;//start point 
    T _h,_w ;//size 

public:
    RectangleF()
            : _x(0.0f), _y(0.0f), _w(0.0f), _h(0.0f)
    {
    }

    RectangleF(T x, T y, T w, T h)
            : _x(x), _y(y), _w(w), _h(h)
    {
    }

    RectangleF(const RectangleF<T> &rect)
            : _x(rect._x), _y(rect._y), _w(rect._w), _h(rect._h)
    {
    }

    RectangleF(const Vertex<T> &startPoint, const Size<T> &size)
            : _x(point.x()),
              _y(point.y()),
              _w(size.width()),
              _h(size.height())
    {
    }

    RectangleF(const Size<T> &size, const Vertex<T> &point)
            : _x(point.x()),
              _y(point.y()),
              _w(size.width()),
              _h(size.height())
    {
    }

    RectangleF(const Vertex<T> &topleft, const Vertex<T> &bottomright)
            : _x(topleft.x()),
              _y(topleft.y()),
              _w(bottomright.x()),
              _h(bottomright.y())
    {
    }

    ~RectangleF()
    {
    }
    
    inline bool isEmpty() const { return (_w <= 0.0f || _h <= 0.0f); }
    inline bool isValid() const { return (_w > 0.0f && _h > 0.0f); }

    inline T x() const { return _x; }
    inline T y() const { return _y; }

    inline void setX(T x) { _x = x; }
    inline void setY(T y) { _y = y; }

    inline T width() const { return _w; }
    inline T height() const { return _h; }

    inline void setWidth(T w) { _w = w; }
    inline void setHeight(T h) { _h = h; }

    inline T top() const { return _y; }
    inline T bottom() const { return _y + _h; }
    inline T left() const { return _x; }
    inline T right() const { return _x + _w; }

    void setTop(T pos);
    void setLeft(T pos);

    inline void setBottom(T pos) { _h = pos - _y; }
    inline void setRight(T pos) { _w = pos - _x; }

    inline T area() const { return _w * _h; }
    inline T perimeter() const { return (_w + _h) * 2.0f; }

    inline Vertex<T> topLeft() const { return Vertex<T>(_x, _y); }
    inline Vertex<T> bottomLeft() const { return Vertex<T>(_x, _y + _h); }
    inline Vertex<T> topRight() const { return Vertex<T>(_x + _w, _y); }
    inline Vertex<T> bottomRight() const { return Vertex<T>(_x + _w, _y + _h); }
    inline Vertex<T> center() const { return Vertex<T>((_x + _w) / 2.0f, (_y + _h) / 2.0f); }

    inline void setTopLeft(const Vertex<T> &point) { setTop(point.y()); setLeft(point.x()); }
    inline void setBottomLeft(const Vertex<T> &point) { setBottom(point.y()); setLeft(point.x()); }
    inline void setTopRight(const Vertex<T> &point) { setTop(point.x()); setRight(point.y()); }
    inline void setBottomRight(const Vertex<T> &point) { setBottom(point.y()); setRight(point.x()); }

    void setCenter(const Vertex<T> &point);
    void setRectangle(const RectangleF<T> &Rectangle);
    void setRectangle(T x, T y, T w, T h);

    inline Size<T> size() const { return Size<T>(_w, _h); }
    inline void setSize(const Size<T> &s) { _w = s.width(); _h = s.height(); }

    inline void moveTop(T pos) { _y = pos; }
    inline void moveBottom(T pos) { _y = pos - _h; }
    inline void moveLeft(T pos) { _x = pos; }
    inline void moveRight(T pos) { _x = pos - _w; }

    inline void moveTopLeft(const Vertex<T> &point) { moveTop(point.x()); moveLeft(point.y()); }
    inline void moveBottomLeft(const Vertex<T> &point) { moveBottom(point.x()); moveLeft(point.y()); }
    inline void moveTopRight(const Vertex<T> &point) { moveTop(point.y()); moveRight(point.x()); }
    inline void moveBottomRight(const Vertex<T> &point) { moveBottom(point.y()); moveRight(point.x()); }
    inline void moveCenter(const Vertex<T> &point) { _x = point.x() - _w / 2; _y = point.y() - _h / 2; }

    inline bool contains(T x, T y) const { return x >= _x && x <= _x + _w && y >= _y && y <= _y + _h; }
    inline bool contains(const Vertex<T> &point) const { return contains(point.x(), point.y()); }
    inline void inflate(Size<T> &size) { inflate(size.width(), size.height()); }
    //inline void inflate(Rectangle<T> &rect) { inflate(rect.size()); }

    bool contains(const RectangleF<T> &rect) const;
    void inflate(T width, T height);

    static RectangleF<T> intersects(const RectangleF<T> &rect1, const RectangleF<T> &rect2);
    static RectangleF<T> unions(const RectangleF<T> &rect1, const RectangleF<T> &rect2);

    RectangleF<T> &operator=(const RectangleF<T> &rect);
 
    friend bool operator==(const RectangleF<T> &rect1, const RectangleF<T> &rect2);
    friend bool operator!=(const RectangleF<T> &rect1, const RectangleF<T> &rect2);
};


#endif //VR_RECTANGLE_H

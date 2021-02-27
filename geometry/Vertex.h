//
// Created by lidan on 27/2/2021.
//

#ifndef VR_VERTEX_H
#define VR_VERTEX_H


class Vertex {
private:
    float _x, _y ;
public:
    inline Vertex(): _x(0), _y(0)
    {}

    inline Vertex(int x, int y)
            : _x(x), _y(y)
    {}

    inline Vertex(const Vertex &point)
            : _x(point._x), _y(point._y)
    {}

    ~Vertex()
    {}

    inline int x() const { return _x; }
    inline int y() const { return _y; }

    inline void setX(int x) { _x = x; }
    inline void setY(int y) { _y = y; }
    inline void translate(int dx, int dy) { _x += dx; _y += dy; }

    int dotProduct(const Vertex &p1, const Vertex &p2);
    int manhattanLength() const;


    Vertex &operator=(const Vertex &point);
    Vertex &operator+=(const Vertex &point);
    Vertex &operator-=(const Vertex &point);
    Vertex &operator*=(int factor);
    Vertex &operator*=(double factor);

    friend bool operator==(const Vertex &p1, const Vertex &p2);
    friend bool operator!=(const Vertex &p1, const Vertex &p2);

    friend Vertex operator+(const Vertex &p1, const Vertex &p2);
    friend Vertex operator-(const Vertex &p1, const Vertex &p2);
    friend Vertex operator*(int factor, const Vertex &point);
    friend Vertex operator*(const Vertex &point, int factor);


};


#endif //VR_VERTEX_H

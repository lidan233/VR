//
// Created by lidan on 2021/2/28.
//

#ifndef VR_QUATERNION_H
#define VR_QUATERNION_H
#include "EigenLidan.h"
#include "EulerAngles.h"

class Quaternion {
private:
    float _w, _x, _y, _z;
public:
    Quaternion()
            : _w(1.0f), _x(0.0f), _y(0.0f), _z(0.0f)
    {
    }

    Quaternion(float w, float x, float y, float z)
            : _w(w), _x(x), _y(y), _z(z)
    {
    }

    Quaternion(float w, const Vec3 &vec3);

    explicit Quaternion(float arr[4])
            : _w(arr[0]),_x(arr[1]), _y(arr[2]), _z(arr[3])
    {
    }

    explicit Quaternion(const Vec4 &vec4);

    Quaternion(const Quaternion &q)
            : _w(q._w), _x(q._x), _y(q._y), _z(q._z)
    {
    }

    ~Quaternion()
    {
    }

    inline bool isNull() const
    {
        return _w == 0.0f && _x == 0.0f &&
               _y == 0.0f && _z == 0.0f;
    }

    inline bool isIdentity() const
    {
        return _w == 1.0f && _x == 0.0f &&
               _y == 0.0f && _z == 0.0f;
    }

    inline float x() const { return _x; }
    inline float y() const { return _y; }
    inline float z() const { return _z; }
    inline float scalar() const { return _w; }

    inline void setX(float x) { _x = x; }
    inline void setY(float y) { _y = y; }
    inline void setZ(float z) { _z = z; }
    inline void setScalar(float scalar) { _w = scalar; }

    void conjugate();
    void inverse();
    void normalize();

    Quaternion inversed() const;
    Quaternion normalized() const;

    inline Quaternion conjugated() const { return Quaternion(_w, -_x, -_y, -_z); }

    static float dot(const Quaternion &q1, const Quaternion &q2);
    inline float dotProduct(const Quaternion &quad) const { return dot(*this, quad); }

    Lmatrix<double> toRotationMatrix() const;
    EulerAngles toEulerAngles() const;

    static Quaternion fromAxes(const Vec3 &xAxis, const Vec3 &yAxis, const Vec3 &zAxis);
    static Quaternion fromRotationMatrix(const Lmatrix<double> &mat3);
    static Quaternion fromAxisAngle(const Vec3 &axis, float angle);
    static Quaternion fromEulerAngles(const EulerAngles &angles);
    static Quaternion fromDirection(const Vec3 &direction, const Vec3 &up);
    static Quaternion rotationTo(const Vec3 &from, const Vec3 &to);

    static Quaternion nlerp(const Quaternion &q1, const Quaternion &q2, float t);
    static Quaternion slerp(const Quaternion &q1, const Quaternion &q2, float t);

    static Quaternion add(const Quaternion &left, const Quaternion &right);
    static Quaternion subtract(const Quaternion &left, const Quaternion &right);
    static Quaternion multiply(float left, const Quaternion &right);
    static Quaternion multiply(const Quaternion &left, float right);
    static Quaternion multiply(const Quaternion &left, const Quaternion &right);

    Quaternion &operator=(const Quaternion &quad);
    Quaternion &operator+=(const Quaternion &quad);
    Quaternion &operator-=(const Quaternion &quad);
    Quaternion &operator*=(float factor);
    Quaternion &operator*=(const Quaternion &quad);
    Quaternion &operator/=(float divisor);


    friend bool operator==(const Quaternion &q1, const Quaternion &q2);
    friend bool operator!=(const Quaternion &q1, const Quaternion &q2);

    friend Quaternion operator+(const Quaternion &q1, const Quaternion &q2) { return add(q1, q2); }
    friend Quaternion operator-(const Quaternion &q1, const Quaternion &q2) { return subtract(q1, q2); }
    friend Quaternion &operator-(Quaternion &quad);
    friend Quaternion operator*(float factor, const Quaternion &quad) { return multiply(factor, quad); }
    friend Quaternion operator*(const Quaternion &quad, float factor) { return multiply(quad, factor); }
    friend Quaternion operator*(const Quaternion &q1, const Quaternion &q2) { return multiply(q1, q2); }
    friend Quaternion operator/(const Quaternion &quad, float divisor) { return multiply(quad, 1.0f / divisor); }
};


#endif //VR_QUATERNION_H

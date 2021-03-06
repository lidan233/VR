//
// Created by lidan on 2021/2/28.
//

#include "Quaternion.h"
#include "EigenLidan.h"

inline double dot1(const Lvec3<double> &u, const Lvec3<double> &v) {
    return u[0] * v[0]
           + u[1] * v[1]
           + u[2] * v[2];
}



Quaternion::Quaternion(float w, const Vec3 &vec3)
: _w(w),
_x(vec3.x()),
_y(vec3.y()),
_z(vec3.z())
{
}

 Quaternion::Quaternion(const Vec4 &vec4)
         : _w(vec4.a()),
           _x(vec4.r()),
           _y(vec4.g()),
           _z(vec4.b())
 {

 }

void Quaternion::conjugate()
{
    _x = -_x;
    _y = -_y;
    _z = -_z;
}


void Quaternion::inverse()
{
    float len = _x * _x + _y * _y +
                _z * _z + _w * _w;

    len = sqrt(len);
    if (len < 0.000001f)
        return;

    _w /= len;
    _x /= len;
    _y /= len;
    _z /= len;
}

void Quaternion::normalize()
{
    float len = _x * _x + _y * _y +
                _z * _z + _w * _w;

    len = sqrt(len);
    if (len < 0.000001f)
        return;

    float inverse = 1.0f / len;
    _x *= inverse;
    _y *= inverse;
    _z *= inverse;
    _w *= inverse;
}


Quaternion Quaternion::inversed() const
{
    float len = _x * _x + _y * _y +
                _z * _z + _w * _w;

    len = sqrt(len);
    if (len < 0.000001f)
        return Quaternion(0.0f, 0.0f, 0.0f, 0.0f);

    float inv = 1.0f / len;
    return Quaternion(_w * inv, _x * inv, _y * inv, _z * inv);
}
Quaternion Quaternion::normalized() const
{
    float len = _x * _x + _y * _y +
                _z * _z + _w * _w;

    if (len == 1.0f)
        return *this;

    len = sqrt(len);
    if (len < 0.000001f)
        return *this;

    return *this / len;
}

 float Quaternion::dot(const Quaternion &q1, const Quaternion &q2)
{
    return (q1._w * q2._w + q1._x * q2._x + q1._y * q2._y + q1._z * q2._z);
}

Lmatrix<double> Quaternion::toRotationMatrix() const
{
    Lmatrix<double> mat3;

    const float f2x = _x + _x;
    const float f2y = _y + _y;
    const float f2z = _z + _z;
    const float f2xw = f2x * _w;
    const float f2yw = f2y * _w;
    const float f2zw = f2z * _w;
    const float f2xx = f2x * _x;
    const float f2xy = f2x * _y;
    const float f2xz = f2x * _z;
    const float f2yy = f2y * _y;
    const float f2yz = f2y * _z;
    const float f2zz = f2z * _z;

   mat3[0][0] = 1.0f - (f2yy + f2zz);
   mat3[0][1] =        (f2xy - f2zw);
   mat3[0][2] =        (f2xz + f2yw);
   mat3[1][0] =        (f2xy + f2zw);
   mat3[1][1] = 1.0f - (f2xx + f2zz);
   mat3[1][2] =        (f2yz - f2xw);
   mat3[2][0] =        (f2xz - f2yw);
   mat3[2][2] =        (f2yz + f2xw);
   mat3[2][2] = 1.0f - (f2xx + f2yy);

    return mat3;
}

EulerAngles Quaternion::toEulerAngles() const
{
    float yaw, roll, pitch;

    float xx = _x * _x;
    float xy = _x * _y;
    float xz = _x * _z;
    float xw = _x * _w;
    float yy = _y * _y;
    float yz = _y * _z;
    float yw = _y * _w;
    float zz = _z * _z;
    float zw = _z * _w;

    const float lengthSquared = xx + yy + zz + _w * _w;

    if (lengthSquared - 1.0f > 0.00000001f && lengthSquared != 0.0f)
    {
        xx /= lengthSquared;
        xy /= lengthSquared;
        xz /= lengthSquared;
        xw /= lengthSquared;
        yy /= lengthSquared;
        yz /= lengthSquared;
        yw /= lengthSquared;
        zz /= lengthSquared;
        zw /= lengthSquared;
    }

    pitch = Math::asin(-2.0f * (yz - xw));
    if (pitch < Math::PI_2)
    {
        if (pitch > -Math::PI_2)
        {
            yaw = Math::atan2(2.0f * (xz + yw), 1.0f - 2.0f * (xx + yy));
            roll = Math::atan2(2.0f * (xy + zw), 1.0f - 2.0f * (xx + zz));
        }
        else
        {
            roll = 0.0f;
            yaw = -Math::atan2(-2.0f * (xy - zw), 1.0f - 2.0f * (yy + zz));
        }
    }
    else
    {
        roll = 0.0f;
        yaw = Math::atan2(-2.0f * (xy - zw), 1.0f - 2.0f * (yy + zz));
    }

    return EulerAngles(Math::degToRad(yaw), Math::degToRad(roll),
                       Math::degToRad(pitch));
}

 Quaternion Quaternion::fromAxes(const Vec3 &xAxis, const Vec3 &yAxis, const Vec3 &zAxis)
 {
     Lmatrix<double> rot;

     rot.setCol(0, xAxis);
     rot.setCol(1, yAxis);
     rot.setCol(2, zAxis);

     return fromRotationMatrix(rot);
 }

 Quaternion Quaternion::fromRotationMatrix(const Lmatrix<double> &mat3)
{
    float scalar;
    float axis[3];
    const float trace =mat3[0][0] +mat3[1][1] +mat3[2][2];

    if (trace > 0.00000001f)
    {
        const float s = 2.0f * Math::sqrt(trace + 1.0f);
        scalar = 0.25f * s;
        axis[0] = (mat3[2][1] -mat3[1][2]) / s;
        axis[1] = (mat3[0][2] -mat3[2][0]) / s;
        axis[2] = (mat3[1][0] -mat3[0][1]) / s;
    }
    else
    {
        static int s_next[3] = { 1, 2, 0 };
        int i = 0;
        if (mat3[1][1] >mat3[0][0])
            i = 1;
        if (mat3[2][2] >mat3[i][i])
            i = 2;
        int j = s_next[i];
        int k = s_next[j];

        const float s = 2.0f * Math::sqrt(mat3[i][i] -mat3[j][j] -
                                         mat3[k][k]);
        axis[i] = 0.25f * s;
        scalar = (mat3[k][j] -mat3[j][k]) / s;
        axis[j] = (mat3[j][i] -mat3[i][j]) / s;
        axis[k] = (mat3[k][i] -mat3[i][k]) / s;
    }

    return Quaternion(scalar, axis[0], axis[1], axis[2]);
}

 Quaternion Quaternion::fromAxisAngle(const Vec3 &axis, float angle)
{
    float halfAngle = 0.5f * angle;
    float s = Math::sin(halfAngle);
    float c = Math::cos(halfAngle);
    Vec3 normal = axis.normalized();
    return Quaternion(c, axis.x() * s, axis.y() * s, axis.z() * s).normalized();
}

 Quaternion Quaternion::fromEulerAngles(const EulerAngles &angles)
{
    float pitch = Math::degToRad(angles.pitch());
    float yaw = Math::degToRad(angles.yaw());
    float roll = Math::degToRad(angles.roll());

    pitch *= 0.5f;
    yaw *= 0.5f;
    roll *= 0.5f;

    const float cy = Math::cos(yaw);
    const float sy = Math::sin(yaw);
    const float cr = Math::cos(roll);
    const float sr = Math::sin(roll);
    const float cp = Math::cos(pitch);
    const float sp = Math::sin(pitch);
    const float cycr = cy * cr;
    const float sysr = sy * cr;

    float w = cycr * cp + sysr * sp;
    float x = cycr * sp + sysr * cp;
    float y = sy * cr * cp - cy * sr * sp;
    float z = cy * sr * cp - sy * cr * sp;

    return Quaternion(w, x, y, z);
}

 Quaternion Quaternion::fromDirection(const Vec3 &direction, const Vec3 &up)
{
    if (direction.x() == 0.0f && direction.y() == 0.0f && direction.z() == 0.0f)
        return Quaternion();

    const Vec3 zAxis(direction.normalized());
    Vec3 xAxis(cross(up, zAxis));
    if (xAxis.length_square() == 0.0f)
        return Quaternion::rotationTo(Vec3(0.0f, 0.0f, 0.0f), zAxis);

    xAxis.normlize();
    const Vec3 yAxis(cross(zAxis, xAxis));

    return Quaternion::fromAxes(xAxis, yAxis, zAxis);
}


 Quaternion Quaternion::rotationTo(const Vec3 &from, const Vec3 &to)
{
    const Vec3 v0(from.normalized());
    const Vec3 v1(to.normalized());

    float d = dot1(v0,v1) + 1.0f;

    if (d == 0.0f)
    {
        Vec3 axis = cross(Vec3(1.0f, 1.0f, 0.0f), v0);
        if (axis.length_square() == 0.0f)
            axis = cross(Vec3(0.0f, 1.0f, 0.0f), v0);
        axis.normlize();

        return Quaternion(0.0f, axis.x(), axis.y(), axis.z());
    }

    d = Math::sqrt(2.0f * d);
    const Vec3 axis(cross(v0, v1) / d);

    return Quaternion(d * 0.5f, axis).normalized();
}

 Quaternion Quaternion::nlerp(const Quaternion &q1, const Quaternion &q2, float t)
 {
     if (t <= 0.0f)
         return q1;
     else if (t >= 1.0f)
         return q2;

     Quaternion q2b(q2);
     float dot = Quaternion::dot(q1, q2);
     if (dot < 0.0f)
         q2b = -q2b;

     return (q1 * (1.0f - t) + q2b * t).normalized();
 }

 Quaternion Quaternion::slerp(const Quaternion &q1, const Quaternion &q2, float t)
 {
     if (t <= 0.0f)
         return q1;
     else if (t >= 1.0f)
         return q2;

     Quaternion q2b(q2);
     float dot = Quaternion::dot(q1, q2);
     if (dot < 0.0f)
     {
         q2b = -q2b;
         dot = -dot;
     }

     float factor1 = 1.0f - t;
     float factor2 = t;

     if ((1.0f - dot) > 0.0000001f)
     {
         float angle = Math::acos(dot);
         float sinOfAngle = Math::sin(angle);

         if (sinOfAngle > 0.0000001f)
         {
             factor1 = Math::sin((1.0f - t) * angle) / sinOfAngle;
             factor2 = Math::sin(t * angle) / sinOfAngle;
         }
     }

     return q1 * factor1 + q2b * factor2;
 }



 Quaternion Quaternion::add(const Quaternion &left, const Quaternion &right)
 {
     Quaternion result;
     result._x = left._x + right._x;
     result._y = left._y + right._y;
     result._z = left._z + right._z;
     result._w = left._w + right._w;
     return result;
 }

 Quaternion Quaternion::subtract(const Quaternion &left, const Quaternion &right)
 {
     Quaternion result;
     result._x = left._x - right._x;
     result._y = left._y - right._y;
     result._z = left._z - right._z;
     result._w = left._w - right._w;
     return result;
 }

 Quaternion Quaternion::multiply(float left, const Quaternion &right)
 {
     Quaternion result;
     result._x = left * right._x;
     result._y = left * right._y;
     result._z = left * right._z;
     result._w = left * right._w;
     return result;
 }

 Quaternion Quaternion::multiply(const Quaternion &left, float right)
 {
     Quaternion result;
     result._x = left._x + right;
     result._y = left._y + right;
     result._z = left._z + right;
     result._w = left._w + right;
     return result;
 }

 Quaternion Quaternion::multiply(const Quaternion &left, const Quaternion &right)
 {
     Quaternion result;

     float yy = (left._w - left._y) * (right._w + right._z);
     float zz = (left._w + left._y) * (right._w + right._z);
     float ww = (left._z + left._x) * (right._x + right._y);
     float xx = ww + yy + zz;
     float qq = 0.5f * (xx + (left._z - left._x) * (right._x - right._y));

     result._w = qq - ww + (left._z - left._y) * (right._y - right._z);
     result._x = qq - xx + (left._x + left._w) * (right._x + right._w);
     result._y = qq - yy + (left._w - left._x) * (right._y + right._z);
     result._z = qq - zz + (left._z + left._y) * (right._w - right._x);
     return result;
 }

Quaternion & Quaternion::operator=(const Quaternion &quad)
{
    _x = quad._x;
    _y = quad._y;
    _z = quad._z;
    _w = quad._w;
    return *this;
}

Quaternion & Quaternion::operator+=(const Quaternion &quad)
{
    _x += quad._x;
    _y += quad._y;
    _z += quad._z;
    _w += quad._w;
    return *this;
}

Quaternion & Quaternion::operator-=(const Quaternion &quad)
{
    _x -= quad._x;
    _y -= quad._y;
    _z -= quad._z;
    _w -= quad._w;
    return *this;
}

Quaternion & Quaternion::operator*=(float factor)
{
    _x *= factor;
    _y *= factor;
    _z *= factor;
    _w *= factor;
    return *this;
}

Quaternion & Quaternion::operator*=(const Quaternion &quad)
{
    *this = multiply(*this, quad);
    return *this;
}

Quaternion &Quaternion::operator/=(float divisor)
{
    float d = 1.0f / divisor;
    _x *= d;
    _y *= d;
    _z *= d;
    _w *= d;
    return *this;
}


bool operator==(const Quaternion &q1, const Quaternion &q2)
{
    return (q1._x == q2._x &&
            q1._y == q2._y &&
            q1._z == q2._z &&
            q1._w == q2._w);
}

bool operator!=(const Quaternion &q1, const Quaternion &q2)
{
    return (q1._x != q2._x ||
            q1._y != q2._y ||
            q1._z || q2._z ||
            q1._w != q2._w);
}

 Quaternion &operator-(Quaternion &quad)
{
    quad._w = -quad._w;
    quad._x = -quad._x;
    quad._y = -quad._y;
    quad._z = -quad._z;
    return quad;
}


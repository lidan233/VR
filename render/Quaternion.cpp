//
// Created by lidan on 2021/2/28.
//

#include "Quaternion.h"

void Quaternion::conjugate()
{

}


void Quaternion::inverse()
{

}

void Quaternion::normalize()
{

}


Quaternion Quaternion::inversed() const
{

}
Quaternion Quaternion::normalized() const
{

}

 float Quaternion::dot(const Quaternion &q1, const Quaternion &q2)
{

}

Lmatrix<double> Quaternion::toRotationMatrix() const
{

}

EulerAngles Quaternion::toEulerAngles() const
{

}

 Quaternion Quaternion::fromAxes(const Vec3 &xAxis, const Vec3 &yAxis, const Vec3 &zAxis)
 {

 }

 Quaternion Quaternion::fromRotationMatrix(const Lmatrix<double> &mat3)
{

}

 Quaternion Quaternion::fromAxisAngle(const Vec3 &axis, float angle)
{

}

 Quaternion Quaternion::fromEulerAngles(const EulerAngles &angles)
{

}

 Quaternion Quaternion::fromDirection(const Vec3 &direction, const Vec3 &up)
{

}

 Quaternion Quaternion::rotationTo(const Vec3 &from, const Vec3 &to)
{

}

 Quaternion Quaternion::nlerp(const Quaternion &q1, const Quaternion &q2, float t)
 {

 }

 Quaternion Quaternion::slerp(const Quaternion &q1, const Quaternion &q2, float t)
 {

 }

 Quaternion Quaternion::squad(const Quaternion &q1, const Quaternion &q2, float t)
 {

 }


 Quaternion Quaternion::add(const Quaternion &left, const Quaternion &right)
 {

 }

 Quaternion Quaternion::subtract(const Quaternion &left, const Quaternion &right)
 {

 }

 Quaternion Quaternion::multiply(float left, const Quaternion &right)
 {

 }

 Quaternion Quaternion::multiply(const Quaternion &left, float right)
 {

 }

 Quaternion Quaternion::multiply(const Quaternion &left, const Quaternion &right)
 {

 }

Quaternion & Quaternion::operator=(const Quaternion &quad)
{

}

Quaternion & Quaternion::operator+=(const Quaternion &quad)
{

}

Quaternion & Quaternion::operator-=(const Quaternion &quad)
{

}

Quaternion & Quaternion::operator*=(float factor)
{

}

Quaternion & Quaternion::operator*=(const Quaternion &quad)
{

}

Quaternion &Quaternion::operator/=(float divisor)
{

}


bool operator==(const Quaternion &q1, const Quaternion &q2)
{

}

bool operator!=(const Quaternion &q1, const Quaternion &q2)
{

}

 Quaternion &operator-(Quaternion &quad)
{

}


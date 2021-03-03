//
// Created by lidan on 2021/2/28.
//

#include "EulerAngles.h"

void EulerAngles::identity()
{
    m_yaw   = 0.0f;
    m_roll  = 0.0f;
    m_pitch = 0.0f;
}

void EulerAngles::fromQuaternion(const Quaternion& quat)
{

}

Quaternion EulerAngles::toQuaternion() const
{

}
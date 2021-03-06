//
// Created by lidan on 2021/2/23.
//

#ifndef VR_EULERANGLES_H
#define VR_EULERANGLES_H
class Quaternion;

class EulerAngles {
private:
    float _yaw, _roll, _pitch ;
public:
    EulerAngles()
    :_yaw(0.0f), _roll(0.0f), _pitch(0.0f)
    {}

    EulerAngles(const EulerAngles& other)
    :_yaw(other._yaw), _roll(other._roll), _pitch(other._roll)
    {}

    EulerAngles(float yaw, float roll, float pitch)
    :_yaw(yaw) , _roll(roll), _pitch(pitch)
    {}

    ~EulerAngles(){}

    inline float yaw() const { return _yaw ;}
    inline float roll() const { return _roll ; }
    inline float pitch() const { return _pitch  ; }

    inline void setYaw(float a) { _yaw = a ; }
    inline void setRoll(float b) { _roll = b ; }
    inline void setPitch(float c) { _pitch = c ; }

    void identity() ;
    void fromQuaternion(const Quaternion& quat) ;
    Quaternion toQuaternion() const ;
};


#endif //VR_EULERANGLES_H

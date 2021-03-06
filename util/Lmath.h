//
// Created by lidan on 2021/2/28.
//

#ifndef VR_LMATH_H
#define VR_LMATH_H
#include <cmath>
#include <limits>



class Math{
public:
    static constexpr float E            = 2.71828182845904523536f;
    static constexpr float Epsilon      = 0.000001f;
    static constexpr float LargeEpsilon = 0.00005f;
    static constexpr float Infinity     = std::numeric_limits<float>::infinity();
    static constexpr float NegInfinity  = -std::numeric_limits<float>::infinity();
    static constexpr float Log2E        = 1.442695040888963387f;
    static constexpr float Log10E       = 0.4342944819032518f;
    static constexpr float PI           = 3.14159265358979323846f;
    static constexpr float PI_2         = 6.28318530717958647693f;
    static constexpr float Half_Pi      = 1.57079632679489661923f;
    static constexpr float Tolerance    = 2e-37f;

    inline static float  fast_sqrt_inverse(float f) {
        float xhalf = 0.5f * f;
        int i = *(int *)&f ;
        i = 0x5f375a86 - (i >> 1);
        f = *(float *)&i;
        f = f * (1.5f - xhalf * f * f);
        return f;
    }

    inline static float acos(float radian) { return acosf(radian); }
    inline static float asin(float radian) { return asinf(radian); }
    inline static float atan(float radian) { return atanf(radian); }
    inline static float atan2(float r1, float r2) { return atan2f(r1, r2); }
    inline static float cos(float radian) { return cosf(radian); }
    inline static float sin(float radian) { return sinf(radian); }
    inline static float tan(float radian) { return tanf(radian); }
    inline static float cot(float radian) { return 1.0f / tanf(radian); }


    inline static float log(float n) { return log(n); }
    inline static float log10(float n) { return log10(n); }

    inline static float abs(float f) { return fabsf(f); }
    inline static float fabs(float f) { return fabsf(f); }
    inline static float exp(float f) { return expf(f); }
    inline static float fmod(float f1, float f2) { return fmodf(f1, f2); }
    inline static float ceil(float f) { return ceilf(f); }
    inline static float floor(float f) { return floorf(f); }
    inline static float pow(float n, float i) { return powf(n, i); }
    inline static float round(float f) { return roundf(f); }
    inline static float sqr(float f) { return f * f; }
    inline static float sqrt(float f) { return 1.0f /fast_sqrt_inverse(f); }

    inline static float radToDeg(float radian) { return radian * (180.0 / PI); }
    inline static float degToRad(float degree) { return degree * (PI * 180.0); }

    inline static int clamp(int value, int _min, int _max) { return fmax(fmin(value, _max), _min); }
    inline static float clamp(float value, float _min, float _max) { return fmax(fmin(value, _max), _min); }

};
#endif //VR_LMATH_H

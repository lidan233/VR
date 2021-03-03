//
// Created by lidan on 1/3/2021.
//

#ifndef VR_MATRIXCALCULATION_H
#define VR_MATRIXCALCULATION_H

#include "EigenLidan.h"
#include "Rectangle.h"
#include "Lmath.h"

class MatrixCalculation {
public:
    // 2D transform
    static void rotate2D(Lmatrix<double> &result, float angle);
    static void scale2D(Lmatrix<double> &result, float sx, float sy);
    static void shear2D(Lmatrix<double> &result, float x, float y);
    static void translate2D(Lmatrix<double> &result, float x, float y);

    static Lmatrix<double> rotate2D(float angle);
    static Lmatrix<double> scale2D(float sx, float sy);
    static Lmatrix<double> shearX2D(float x);
    static Lmatrix<double> shearY2D(float y);
    static Lmatrix<double> translate2D(float x, float y);

    // 3D transform
    static void ortho(Lmatrix<double> &result, const Rectangle<double> &rect);
    static void ortho(Lmatrix<double> &result, float left, float right, float bottom, float top, float zNear, float zFar);

    static void frustum(Lmatrix<double> &result, float left, float right, float bottom, float top, float zNear, float zFar);

    static void perspective(Lmatrix<double> &result, float fov, float ratio, float zNear, float zFar);

    static void lookAt(Lmatrix<double> &result, const Vec3 &eye, const Vec3 &center, const Vec3 &up);
    static void lookAt(Lmatrix<double> &result, float eyeX, float eyeY, float eyeZ,
                       float centerX, float centerY, float centerZ,
                       float upX, float upY, float upZ);

    static void viewport(Lmatrix<double> &result, const Rectangle<double> &rect);
    static void viewport(Lmatrix<double> &result, float left, float bottom, float width, float height, float zNear, float zFar);


    static void fromAxisAngle(Lmatrix<double> &mat4, float angle, float x, float y, float z);
    static void fromAxisAngle(Lmatrix<double> &mat4, float angle, const Vec3 &axis);
    static void rotateX(Lmatrix<double> &mat4, float angle);
    static void rotateY(Lmatrix<double> &mat4, float angle);
    static void rotateZ(Lmatrix<double> &mat4, float angle);
    static void scale(Lmatrix<double> &mat4, float sx, float sy, float sz);

    static void translate( Lmatrix<double> &mat4, float x, float y, float z);

    static Lmatrix<double> ortho(const Rectangle<double> &rect);
    static Lmatrix<double> ortho(float left, float right, float bottom, float top, float zNear, float zFar);
    static Lmatrix<double> frustum(float left, float right, float bottom, float top, float zNear, float zFar);
    static Lmatrix<double> perspective(float fov, float ratio, float zNear, float zFar);
    static Lmatrix<double> lookAt(const Vec3 &eye, const Vec3 &center, const Vec3 &up);
    static Lmatrix<double> lookAt(float eyeX, float eyeY, float eyeZ,
                            float centerX, float centerY, float centerZ,
                            float upX, float upY, float upZ);
    static Lmatrix<double> viewport(const Rectangle<double> &rect);
    static Lmatrix<double> viewport(float left, float bottom, float width, float height, float zNear, float zFar);

    static Lmatrix<double> fromAxisAngle(float angle, float x, float y, float z);
    static Lmatrix<double> fromAxisAngle(float angle, const Vec3 &axis);
    static Lmatrix<double> rotateX(float angle);
    static Lmatrix<double> rotateY(float angle);
    static Lmatrix<double> rotateZ(float angle);
    static Lmatrix<double> scale(float sx, float sy, float sz);
    static Lmatrix<double> translate(float x, float y, float z); 
};


#endif //VR_MATRIXCALCULATION_H

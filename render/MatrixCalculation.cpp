//
// Created by lidan on 1/3/2021.
//

#include "MatrixCalculation.h"


void MatrixCalculation::rotate2D(Lmatrix<double> &result, float angle)
{
    assert(result.mrows()==3 && result.ncols()==3) ;
    float s = Math::sin(angle) ;
    float c = Math::cos(angle) ;

    result.setIdentity() ;
    result[0][0] =  c;
    result[0][1] = -s;
    result[1][0] =  s;
    result[1][1] =  c;
}

void MatrixCalculation::scale2D(Lmatrix<double> &result, float sx, float sy)
{
    assert(result.mrows()==3 && result.ncols()==3) ;
    result.setIdentity() ;
    result[0][0] = sx ;
    result[0][1] = sy ;
}

void MatrixCalculation::shear2D(Lmatrix<double> &result, float x, float y)
{
    assert(result.mrows()==3 && result.ncols()==3) ;
    result.setIdentity() ;
    result[1][0] = x ;
    result[0][1] = y ;
}

void MatrixCalculation::translate2D(Lmatrix<double> &result, float x, float y)
{
    assert(result.mrows()==3 && result.ncols()==3) ;
    result.setIdentity();
    result[2][0] = x;
    result[2][1] = y;
}


Lmatrix<double> MatrixCalculation::rotate2D(float angle)
{
    Lmatrix<double> res(3,3) ;
    rotate2D(res,angle) ;
    return res ;
}

Lmatrix<double> MatrixCalculation::scale2D(float sx, float sy)
{
    Lmatrix<double> res(3,3) ;
    scale2D(res,sx,sy) ;
    return res ;
}

Lmatrix<double> MatrixCalculation::shearX2D(float x)
{
    Lmatrix<double> res(3,3) ;
    shear2D(res, x, 0.0f);
    return res ;
}

Lmatrix<double> MatrixCalculation::shearY2D(float y)
{
    Lmatrix<double> res(3,3) ;
    shear2D(res, 0.0f, y );
    return res ;
}

Lmatrix<double> MatrixCalculation::translate2D(float x, float y)
{
    Lmatrix<double> res(3,3) ;
    translate2D(res, x, y );
    return res;
}

// 3D transform
void MatrixCalculation::ortho(Lmatrix<double> &result, const Rectangle<double> &rect)
{
    
}

void MatrixCalculation::ortho(Lmatrix<double> &result, float left, float right, float bottom, float top, float zNear, float zFar)
{
    if (left == right || bottom == top || zNear == zFar)
        return;

    float width = right - left;
    float invheight = top - bottom;
    float clip = zFar - zNear;

    result[0][0] = 2.0f / width;
    result[1][0] = 0.0f;
    result[2][0] = 0.0f;
    result[3][0] = -(left + right) / width;
    result[0][1] = 0.0f;
    result[1][1] = 2.0f / invheight;
    result[2][1] = 0.0f;
    result[3][1] = -(top + bottom) / invheight;
    result[0][2] = 0.0f;
    result[1][2] = 0.0f;
    result[2][2] = -2.0f / clip;
    result[3][2] = -(zNear + zFar) / clip;
    result[0][3] = 0.0f;
    result[1][3] = 0.0f;
    result[2][3] = 0.0f;
    result[3][3] = 1.0f;
}

void MatrixCalculation::frustum(Lmatrix<double> &result, float left, float right, float bottom, float top, float zNear, float zFar)
{
    if (left == right || bottom == top || zNear == zFar)
        return;

    float width = right - left;
    float invheight = top - bottom;
    float clip = zFar - zNear;

    result[0][0] = 2.0f * zNear / width;
    result[1][0] = 0.0f;
    result[2][0] = (left + right) / width;
    result[3][0] = 0.0f;
    result[0][1] = 0.0f;
    result[1][1] = 2.0f * zNear / invheight;
    result[2][1] = (top + bottom) / invheight;
    result[3][1] = 0.0f;
    result[0][2] = 0.0f;
    result[1][2] = 0.0f;
    result[2][2] = -(zNear + zFar) / clip;
    result[3][2] = (-2.0f * zNear * zFar) / clip;
    result[0][3] = 0.0f;
    result[1][3] = 0.0f;
    result[2][3] = -1.0f;
    result[3][3] = 0.0f;
}

void MatrixCalculation::perspective(Lmatrix<double> &result, float fov, float ratio, float zNear, float zFar) 
{
    if (zNear == zFar || ratio == 0.0f)
        return;

    float radian = Math::degToRad(fov);
    float s = Math::sin(radian);

    if (s == 0.0f)
        return;

    float cotan = Math::cot(radian);
    float clip = zFar - zNear;

    result[0][0] = cotan / ratio;
    result[1][0] = 0.0f;
    result[2][0] = 0.0f;
    result[3][0] = 0.0f;
    result[0][1] = 0.0f;
    result[1][1] = cotan;
    result[2][1] = 0.0f;
    result[3][1] = 0.0f;
    result[0][2] = 0.0f;
    result[1][2] = 0.0f;
    result[2][2] = -(zNear + zFar) / clip;
    result[3][2] = -(2.0f * zNear * zFar) / clip;
    result[0][3] = 0.0f;
    result[1][3] = 0.0f;
    result[2][3] = -1.0f;
    result[3][3] = 0.0f;
}

void MatrixCalculation::lookAt(Lmatrix<double> &result, const Vec3 &eye, const Vec3 &center, const Vec3 &up) {
    Vec3 forward = center - eye;

    forward.normlize();

    Vec3 side = cross(forward,up);
    side.normlize() ;

    Vec3 upVector = cross(side, forward);

    result[0][0] = side.x();
    result[1][0] = side.y();
    result[2][0] = side.z();
    result[3][0] = 0.0f;
    result[0][1] = upVector.x();
    result[1][1] = upVector.y();
    result[2][1] = upVector.z();
    result[3][1] = 0.0f;
    result[0][2] = -forward.x();
    result[1][2] = -forward.y();
    result[2][2] = -forward.z();
    result[3][2] = 0.0f;
    result[0][3] = 0.0f;
    result[1][3] = 0.0f;
    result[2][3] = 0.0f;
    result[3][3] = 1.0f;
}

void MatrixCalculation::lookAt(Lmatrix<double> &result, float eyeX, float eyeY, float eyeZ,
                   float centerX, float centerY, float centerZ,
                   float upX, float upY, float upZ) {
    lookAt(result, Vec3(eyeX, eyeY, eyeZ),
           Vec3(centerX, centerY, centerZ),
           Vec3(upX, upY, upZ));
}

void MatrixCalculation::viewport(Lmatrix<double> &result, const Rectangle<double> &rect) {
    viewport(result, rect.left(), rect.bottom(), rect.width(), rect.height(), 1.0f, -1.0f);
}   

void MatrixCalculation::viewport(Lmatrix<double> &result, float left, float bottom, float width, float height, float zNear, float zFar) {
    const float w2 = width / 2.0f;
    const float h2 = height / 2.0f;

    result[0][0] = w2;
    result[1][0] = 0.0f;
    result[2][0] = 0.0f;
    result[3][0] = left + w2;
    result[0][1] = 0.0f;
    result[1][1] = h2;
    result[2][1] = 0.0f;
    result[3][1] = bottom + h2;
    result[0][2] = 0.0f;
    result[1][2] = 0.0f;
    result[2][2] = (zFar - zNear) / 2.0f;
    result[3][2] = (zNear + zFar) / 2.0f;
    result[0][3] = 0.0f;
    result[1][3] = 0.0f;
    result[2][3] = 0.0f;
    result[3][3] = 1.0f;
}



void MatrixCalculation::fromAxisAngle(Lmatrix<double> &mat4, float angle, float x, float y, float z) 
{
    float s = Math::sin(angle);
    float c = Math::cos(angle);
    float _c = 1.0f - c;

    mat4[0][0] = x * x * _c + c;
    mat4[1][0] = x * y * _c - z * s;
    mat4[2][0] = x * z * _c + y * s;
    mat4[3][0] = 0.0f;
    mat4[0][1] = y * x * _c + z * s;
    mat4[1][1] = y * y * _c + c;
    mat4[2][1] = y * z * _c - x * s;
    mat4[3][1] = 0.0f;
    mat4[0][2] = x * z * _c - y * s;
    mat4[1][2] = y * z * _c + x * s;
    mat4[2][2] = z * z * _c + c;
    mat4[3][2] = 0.0f;
    mat4[0][3] = 0.0f;
    mat4[1][3] = 0.0f;
    mat4[2][3] = 0.0f;
    mat4[3][3] = 1.0f;
}

void MatrixCalculation::fromAxisAngle(Lmatrix<double> &mat4, float angle, const Vec3 &axis) {
    fromAxisAngle(mat4, angle, axis.x(), axis.y(), axis.z());
}

void MatrixCalculation::rotateX(Lmatrix<double> &mat4, float angle) {
    float s = Math::sin(angle);
    float c = Math::cos(angle);

    mat4.setIdentity();
    mat4[1][1] =  c;
    mat4[1][2] =  s;
    mat4[2][1] = -s;
    mat4[2][2] =  c;
}

void MatrixCalculation::rotateY(Lmatrix<double> &mat4, float angle)
{
    float s = Math::sin(angle);
    float c = Math::cos(angle);

    mat4.setIdentity();
    mat4[0][0] =  c;
    mat4[0][2] = -s;
    mat4[2][0] =  s;
    mat4[2][2] =  c;
}

void MatrixCalculation::rotateZ(Lmatrix<double> &mat4, float angle) {
    float s = Math::sin(angle);
    float c = Math::cos(angle);

    mat4.setIdentity();
    mat4[0][0] =  c;
    mat4[0][1] =  s;
    mat4[1][0] = -s;
    mat4[1][1] =  c;
}

void MatrixCalculation::scale(Lmatrix<double> &mat4, float sx, float sy, float sz) 
{
    mat4.setIdentity();
    mat4[0][0] = sx;
    mat4[1][1] = sy;
    mat4[2][2] = sz;
}


void MatrixCalculation::translate( Lmatrix<double> &mat4, float x, float y, float z) {
    mat4.setIdentity();
    mat4[3][0] = x;
    mat4[3][1] = y;
    mat4[3][2] = z;
}

Lmatrix<double> MatrixCalculation::ortho(const Rectangle<double> &rect) {
    Lmatrix<double> result;
    ortho(result, rect.left(), rect.right(), rect.bottom(), rect.top(), -1.0f, 1.0f);
    return result;
}

Lmatrix<double> MatrixCalculation::ortho(float left, float right, float bottom, float top, float zNear, float zFar) {
    Lmatrix<double> result;
    ortho(result, left, right, bottom, top ,zNear, zFar);
    return result;
}

Lmatrix<double> MatrixCalculation::frustum(float left, float right, float bottom, float top, float zNear, float zFar)
{
    Lmatrix<double> result;
    frustum(result, left, right, bottom, top ,zNear, zFar);
    return result;
}

Lmatrix<double> MatrixCalculation::perspective(float fov, float ratio, float zNear, float zFar)
{
    Lmatrix<double> result;
    perspective(result, fov, ratio, zNear, zFar);
    return result;
}

Lmatrix<double> MatrixCalculation::lookAt(const Vec3 &eye, const Vec3 &center, const Vec3 &up)
{
    Lmatrix<double> result;
    lookAt(result, eye, center, up);
    return result;
}

Lmatrix<double> MatrixCalculation::lookAt(float eyeX, float eyeY, float eyeZ,
                              float centerX, float centerY, float centerZ,
                              float upX, float upY, float upZ)

{
    Lmatrix<double> result;
    lookAt(result, Vec3(eyeX, eyeY, eyeZ),
           Vec3(centerX, centerY, centerZ),
           Vec3(upX, upY, upZ));
    return result;
}

Lmatrix<double> MatrixCalculation::viewport(const Rectangle<double> &rect)
{
    Lmatrix<double> result;
    viewport(result, rect);
    return result;
}

Lmatrix<double> MatrixCalculation::viewport(float left, float bottom, float width, float height, float zNear, float zFar)
{
    Lmatrix<double> result;
    viewport(result, left, bottom, width, height ,zNear, zFar);
    return result;
}

Lmatrix<double> MatrixCalculation::fromAxisAngle(float angle, float x, float y, float z)
{
    Lmatrix<double> result;
    fromAxisAngle(result, angle, x, y, z);
    return result;
}

Lmatrix<double> MatrixCalculation::fromAxisAngle(float angle, const Vec3 &axis)
{
    Lmatrix<double> result;
    fromAxisAngle(result, angle, axis.x(), axis.y(), axis.z());
    return result;
}

Lmatrix<double> MatrixCalculation::rotateX(float angle)
{
    Lmatrix<double> result;
    rotateX(result, angle);
    return result;
}

Lmatrix<double> MatrixCalculation::rotateY(float angle)
{
    Lmatrix<double> result;
    rotateY(result, angle);
    return result;
}

Lmatrix<double> MatrixCalculation::rotateZ(float angle)
{
    Lmatrix<double> result;
    rotateZ(result, angle);
    return result;
}

Lmatrix<double> MatrixCalculation::scale(float sx, float sy, float sz)
{
    Lmatrix<double> result;
    scale(result, sx, sy, sz);
    return result;
}

Lmatrix<double> MatrixCalculation::translate(float x, float y, float z)
{
    Lmatrix<double> result;
    translate(result, x, y, z);
    return result;
}

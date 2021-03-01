//
// Created by lidan on 1/3/2021.
//

#include "MatrixCalculation.h"


void MatrixCalculation::rotate2D(Lmatrix<double> &result, float angle)
{
    
}

void MatrixCalculation::scale2D(Lmatrix<double> &result, float sx, float sy)
{
    
}

void MatrixCalculation::shear2D(Lmatrix<double> &result, float x, float y)
{
    
}

void MatrixCalculation::translate2D(Lmatrix<double> &result, float x, float y)
{
    
}


Lmatrix<double> MatrixCalculation::rotate2D(float angle)
{
    
}

Lmatrix<double> MatrixCalculation::scale2D(float sx, float sy)
{
    
}

Lmatrix<double> MatrixCalculation::shearX2D(float x)
{
    
}

Lmatrix<double> MatrixCalculation::shearY2D(float y)
{
    
}

Lmatrix<double> MatrixCalculation::translate2D(float x, float y)
{
    
}

// 3D transform
void MatrixCalculation::ortho(Lmatrix<double> &result, const Rectangle<double> &rect)
{
    
}

void MatrixCalculation::ortho(Lmatrix<double> &result, float left, float right, float bottom, float top, float zNear, float zFar)
{

}

void MatrixCalculation::frustum(Lmatrix<double> &result, float left, float right, float bottom, float top, float zNear, float zFar)
{

}

void MatrixCalculation::perspective(Lmatrix<double> &result, float fov, float ratio, float zNear, float zFar) {

}

void MatrixCalculation::lookAt(Lmatrix<double> &result, const Vec3 &eye, const Vec3 &center, const Vec3 &up) {

}

void MatrixCalculation::lookAt(Lmatrix<double> &result, float eyeX, float eyeY, float eyeZ,
                   float centerX, float centerY, float centerZ,
                   float upX, float upY, float upZ) {

}

void MatrixCalculation::viewport(Lmatrix<double> &result, const Rectangle<double> &rect) {

}

void MatrixCalculation::viewport(Lmatrix<double> &result, float left, float bottom, float width, float height, float zNear, float zFar) {

}



void MatrixCalculation::fromAxisAngle(Lmatrix<double> &mat4, float angle, float x, float y, float z) {

}

void MatrixCalculation::fromAxisAngle(Lmatrix<double> &mat4, float angle, const Vec3 &axis) {

}

void MatrixCalculation::rotateX(Lmatrix<double> &mat4, float angle) {

}

void MatrixCalculation::rotateY(Lmatrix<double> &mat4, float angle) {

}

void MatrixCalculation::rotateZ(Lmatrix<double> &mat4, float angle) {

}

void MatrixCalculation::scale(Lmatrix<double> &mat4, float sx, float sy, float sz) {

}


void MatrixCalculation::translate( Lmatrix<double> &mat4, float x, float y, float z) {

}

Lmatrix<double> MatrixCalculation::ortho(const Rectangle<double> &rect) {

}

Lmatrix<double> MatrixCalculation::ortho(float left, float right, float bottom, float top, float zNear, float zFar) {

}

Lmatrix<double> MatrixCalculation::frustum(float left, float right, float bottom, float top, float zNear, float zFar) {

}

Lmatrix<double> MatrixCalculation::perspective(float fov, float ratio, float zNear, float zFar) {

}

Lmatrix<double> MatrixCalculation::lookAt(const Vec3 &eye, const Vec3 &center, const Vec3 &up) {

}

Lmatrix<double> MatrixCalculation::lookAt(float eyeX, float eyeY, float eyeZ,
                              float centerX, float centerY, float centerZ,
                              float upX, float upY, float upZ) {

}

Lmatrix<double> MatrixCalculation::viewport(const Rectangle<double> &rect) {

}

Lmatrix<double> MatrixCalculation::viewport(float left, float bottom, float width, float height, float zNear, float zFar)
{

}

Lmatrix<double> MatrixCalculation::fromAxisAngle(float angle, float x, float y, float z)
{

}

Lmatrix<double> MatrixCalculation::fromAxisAngle(float angle, const Vec3 &axis)
{

}

Lmatrix<double> MatrixCalculation::rotateX(float angle)
{

}

Lmatrix<double> MatrixCalculation::rotateY(float angle)
{

}

Lmatrix<double> MatrixCalculation::rotateZ(float angle)
{

}

Lmatrix<double> MatrixCalculation::scale(float sx, float sy, float sz)
{

}

Lmatrix<double> MatrixCalculation::translate(float x, float y, float z)
{

}

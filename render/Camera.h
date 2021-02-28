//
// Created by lidan on 27/2/2021.
//

#ifndef VR_CAMERA_H
#define VR_CAMERA_H
#include "EigenLidan.h"

class Camera {
private:
    enum ViewCone{
        Perspective = 1 << 0 ,
        Orthographic = 1 << 1 ,
    };
    float _FieldOfView ;
    float _Zoom[2] ;
    float _AspectRatio ;
    float _NearPlane ;
    float _FarPlane ;

    mutable Lmatrix<double> _Model;
    mutable Lmatrix<double> _View;
    mutable Lmatrix<double> _Project;
    mutable Lmatrix<double> all ;
    mutable Lmatrix<double> inverseView ; // for normal vector
    mutable Lmatrix<double> inverseViewProject ; // for all
    mutable int mBits ;
public:

    Camera();

    float fieldOfView() const;

    float zoomX() const;
    float zoomY() const;

    float aspectRatio() const { return _AspectRatio; }
    float nearPlane() const { return _NearPlane; }
    float farPlane() const { return _FarPlane; }

    void setFieldOfView(float fov);

    void setZoomX(float x);
    void setZoomY(float y);

    void setAspectRatio(float ratio);
    void setNearPlane(float nearPlane);
    void setFarPlane(float farPlane);
};


#endif //VR_CAMERA_H

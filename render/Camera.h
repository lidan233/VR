//
// Created by lidan on 27/2/2021.
//

#ifndef VR_CAMERA_H
#define VR_CAMERA_H


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

    mutable M


public:


};


#endif //VR_CAMERA_H

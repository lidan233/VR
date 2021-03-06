//
// Created by lidan on 21/2/2021.
//

#ifndef VR_CAM_H
#define VR_CAM_H
#include "EigenLidan.h"
#include "MatrixCalculation.h"

//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>

enum NCamera_Movement {
    ZERO,
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float NYAW         = 180.0f;
const float NPITCH       =  0.0f;
const float NSPEED       =  2.5f;
const float NSENSITIVITY =  2.0f;
const float NZOOM        =  45.0f;


template <typename genType>
genType radians(genType degrees)
{
    return degrees * static_cast<genType>(0.01745329251994329576923690768489);
}


class Camera {

private:
    // camera Attributes
    Vec3 Position;
    Vec3 Front;
    Vec3 Up;
    Vec3 Right;
    Vec3 WorldUp;
    Vec3 Target ;

    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    float radius ;

public:
    Camera( Vec3 position = Vec3(0.0f, 0.0f, 3.0f),
            Vec3 up = Vec3(0.0f, 1.0f, 0.0f),
            Vec3 target = Vec3(0.0,0.0,0.0) ,
            float yaw = NYAW,
            float pitch = NPITCH)
            :MovementSpeed(NSPEED),
             MouseSensitivity(NSENSITIVITY),
             Zoom(NZOOM)
    {
        Front = (target-position).normalized() ;
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        Target = target ;
        radius = (Position-Target).length() ;

        updateCameraVectors();
    }

    Vec3 getFront() { return Front; }
    Vec3 getRight() { return Right; }
    Vec3 getUp() { return Up; }

    void setCenter(Vec3 center)
    {
        Vec3 dir = (center-Target).normalized() ;
        Target = center ;
        Position = Target + radius*dir ;
        Front = (Target-Position).normalized() ;
    }
    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    Lmatrix<double> GetViewMatrix()
    {
        return MatrixCalculation::lookAt(Position, Position + Front, Up);
    }



    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(NCamera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
            Pitch += 100*MouseSensitivity;
        if (direction == BACKWARD)
            Pitch -= 100*MouseSensitivity;
        if (direction == LEFT)
            Yaw   -= 100*MouseSensitivity;
        if (direction == RIGHT)
            Yaw   += 100*MouseSensitivity;
        updateCameraVectors();
//        log(INFO," " +std::to_string(Position[0]) +" " +std::to_string(Position[1])+" " +std::to_string(Position[2]));
    }

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw   -= xoffset;
        Pitch += yoffset;

        updateCameraVectors();
    }


    void ProcessMouseScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }

    float getZoom(){ return Zoom; }
    Vec3 getViewDir() { return Front ; }

private:

    void updateCameraVectors()
    {
        // calculate the new Front vector
        Vec3 front;
        front[0] = cos(radians(Yaw)) * cos(radians(Pitch));
        front[1] = sin(radians(Pitch));
        front[2] = sin(radians(Yaw)) * cos(radians(Pitch));
        Front = (front).normalized() ;
        Right = (cross(Front, WorldUp)).normalized() ;  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up    = (cross(Right, Front)).normalized() ;
        Position = Target - radius * Front ;

//        std::cout<<"Position "<< Position<<std::endl ;
//        std::cout<<"Front "<< Front<< std::endl ;
//        std::cout<<"Right "<< Right <<std::endl ;
//        std::cout<<"Up "<<Up<<std::endl ;
    }

};



#endif //VR_CAM_H

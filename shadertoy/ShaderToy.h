//
// Created by lidan on 2021/2/25.
//

#ifndef VR_SHADERTOY_H
#define VR_SHADERTOY_H
#include "util.h"
#include "Sample2D.h"


// https://www.shadertoy.com/view/XslGRr
//Shader Inputs
//uniform vec3      iResolution;           // viewport resolution (in pixels)
//uniform float     iTime;                 // shader playback time (in seconds)
//uniform float     iTimeDelta;            // render time (in seconds)
//uniform int       iFrame;                // shader playback frame
//uniform float     iChannelTime[4];       // channel playback time (in seconds)
//uniform vec3      iChannelResolution[4]; // channel resolution (in pixels)
//uniform vec4      iMouse;                // mouse pixel coords. xy: current (if MLB down), zw: click
//uniform samplerXX iChannel0..3;          // input channel. XX = 2D/Cube
//uniform vec4      iDate;                 // (year, month, day, time in seconds)
//uniform float     iSampleRate;           // sound sample rate (i.e., 44100)


class ShaderToyInput{
public:
    Vec3 iResolution ;

    float iTime ;
    float iTimeDelta ;
    float iChannelTime[4] ;

    Vec3 iChannelResolution[4] ;
    Vec4 iMouse ;
    Vec4 iDate ;

    int iFrame ;
    float iFrameRate ;
    float iSampleRate ;
    float iGlobalTime ;

    Sampler2D texture[3] ;
};
#endif //VR_SHADERTOY_H

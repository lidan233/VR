//
// Created by lidan on 2021/2/28.
//

#ifndef VR_TIMER_H
#define VR_TIMER_H
#include "util.h"

class Timer {
private:
    unsigned int _Frames ;
    float _rateticks ;
    unsigned int _basetick ;
    unsigned int _lasttick ;
    unsigned  int _rate ;
    unsigned int _globalTime ;

public:
    Timer() ;
    ~Timer() ;

    void init() ;
    int setFrameRate(unsigned int rate) ;


    unsigned int frameRate()  const { return _rate ; }
    unsigned int frameCount() const { return _Frames; }
    unsigned int globalTime() const { return _globalTime ; }

    unsigned int frameRateDelay() ;

};


#endif //VR_TIMER_H

//
// Created by lidan on 2021/2/28.
//

#include "Timer.h"


Timer::Timer()
:_Frames(0),
_rateticks(0.0f),
_basetick(0.0f),
_lasttick(0.0f),
_rate(30),
_globalTime(0)
{

}

Timer::~Timer()
{

}

inline static int getTicks()
{
    // calculate the initial time of SDL
    int ticks = SDL_GetTicks() ;
    return ticks == 0 ? 1: ticks ;
}

void Timer::init()
{
    _Frames = 0 ;
    _rate = 30 ;
    _rateticks = (1000.0f /(float)30) ;
    _globalTime = getTicks() ;
    _basetick = _globalTime ;
    _lasttick = _globalTime ;
}

int Timer::setFrameRate(unsigned int rate)
{
    if(rate >= 20 && rate <= 60)
    {
        _Frames = 0 ;
        _rate = rate ;
        _rateticks = (1000.0f / (float)rate);
        return 0;
    }
    else
        return -1;
}


unsigned int Timer::frameRateDelay()
{
    int currentTicks;
    int targetTicks;
    Uint32 theDelay;
    Uint32 timePassed = 0;

    if (_basetick == 0)
        init();

    _Frames++;

    currentTicks = getTicks();
    _globalTime = currentTicks;

    timePassed = currentTicks - _lasttick;
    _lasttick = currentTicks;
    targetTicks = _basetick + (int)((float)_Frames * _rateticks);

    if (currentTicks <= targetTicks)
    {
        theDelay = targetTicks - currentTicks;
        SDL_Delay(theDelay);
    }
    else
    {
        _Frames = 0;
        _basetick = getTicks();
    }

    return timePassed;
}
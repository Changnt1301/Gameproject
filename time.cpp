#include "time.h"

LTimer::LTimer()
{
    mStartTicks = 0;
    mPausedTicks = 0;
    mPaused = false;
    mStarted = false;
}

void LTimer::start()
{
    mStarted = true;
    mPaused = false;

    mStartTicks = SDL_GetTicks();
    mPausedTicks = 0;
}

void LTimer::stop()
{
    mStarted = false;
    mPaused = false;
    mStartTicks = 0;
    mPausedTicks = 0;
}

void LTimer::pause()
{
    if (mStarted && !mPaused)
    {
        mPaused = true;
        mPausedTicks = SDL_GetTicks() - mStartTicks;
        mStartTicks = 0;
    }
}

Uint32 LTimer::getTicks()
{
    Uint32 timer = 0;
    if (mStarted)
    {
        if (mPaused)
        {
            timer = mPausedTicks;
        }
        else {
            timer = SDL_GetTicks() - mStartTicks;
        }
    }
    return timer;
}

bool LTimer::isStarted()
{
    return mStarted;
}

bool LTimer::isPaused()
{
    return mPaused && mStarted;
}

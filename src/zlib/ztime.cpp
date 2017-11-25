#include "ztime.h"
#include "zassert.h"

#ifdef __linux__
#include <sys/time.h>
uint32_t timeGetTime() {
	struct timeval te;
	gettimeofday(&te, NULL);
	static uint32_t reference_sec = te.tv_sec - 1;
	return (te.tv_sec - reference_sec) * 1000 + te.tv_usec / 1000;
}
#else
# include <windows.h>
#endif // WIN32

#pragma message("Get rid of Time class and use std::chrono::steady_clock")

thread_local uint32_t Time::s_dwPauseStart;
thread_local uint32_t Time::s_dwNegativeOffset;

#ifdef _DEBUG_TRAINING
  thread_local uint32_t Time::s_dwLastTime;
  thread_local uint32_t Time::s_dwAccumulatedTime;
  thread_local  int32_t Time::s_iShift;
  thread_local uint32_t Time::s_dwLastClockTime;
#endif

void    Time::Pause (void)
{
    assert (! IsPaused ());

  #ifdef _DEBUG_TRAINING
    // save the current time as the clock
    s_dwPauseStart = s_dwAccumulatedTime;
  #else
    // save the current time as the clock
    s_dwPauseStart = timeGetTime ();
  #endif
}

bool    Time::IsPaused (void)
{
    // the clock is paused if s_dwPauseStart is non-zero
    return (s_dwPauseStart != 0) ? true : false;
}

void    Time::Continue (void)
{
    assert (IsPaused ());

  #ifdef _DEBUG_TRAINING
    // get the current time to see how long the system was paused,
    // and accumulate that into the clock offset.
    s_dwNegativeOffset += s_dwAccumulatedTime - s_dwPauseStart;
  #else
    // get the current time to see how long the system was paused,
    // and accumulate that into the clock offset.
    s_dwNegativeOffset += timeGetTime () - s_dwPauseStart;
  #endif

    // clear the pause counter
    s_dwPauseStart = 0;
}

Time Time::Now()
{
#ifdef _DEBUG_TRAINING
    // compute the amount of time elapsed since the last frame
    uint32_t   dwRealTime = timeGetTime ();
    assert (dwRealTime >= s_dwLastTime);
    uint32_t   dwDeltaTime = dwRealTime - s_dwLastTime;
    s_dwLastTime = dwRealTime;

    // compute a maximum allowable frame time
    uint32_t   dwMaxDeltaTime =  static_cast<uint32_t> (fResolution () * 0.25f); // 4 FPS
    dwDeltaTime = (dwDeltaTime > dwMaxDeltaTime) ? dwMaxDeltaTime : dwDeltaTime;

    // scale the elapsed time using the shift factor, and
    // accumulate it into the game clock
    uint32_t   dwShiftedTime = (s_iShift >= 0) ? (dwDeltaTime << s_iShift) : (dwDeltaTime >> -s_iShift);
    s_dwAccumulatedTime += dwShiftedTime;

    // compute the current time, accounting for whether or
    // not the clock is paused, and whether or not it has
    // been paused in the past.
    uint32_t   dwCurrentClockTime = ((s_dwPauseStart != 0) ? s_dwPauseStart : s_dwAccumulatedTime) - s_dwNegativeOffset;
    Time    now (dwCurrentClockTime);

    // check that time is strictly increasing
    if (s_dwLastClockTime != 0)
        assert (dwCurrentClockTime >= s_dwLastClockTime);
    s_dwLastClockTime = dwCurrentClockTime;
#else
    uint32_t   dwCurrentClockTime = ((s_dwPauseStart != 0) ? s_dwPauseStart : timeGetTime()) - s_dwNegativeOffset;
    Time    now (dwCurrentClockTime);
#endif

    return now;
}

#ifdef _DEBUG_TRAINING
int     Time::GetShift (void)
{
    // return the current shift value
    return s_iShift;
}

void    Time::SetShift (int iShift)
{
    // limit the amount of speed change
    if (iShift > 3)
        iShift = 3;
    else if (iShift < -3)
        iShift = -3;

    // set the shift value
    s_iShift = iShift;
}
#endif

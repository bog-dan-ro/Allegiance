#ifndef _time_h_
#define _time_h_

/////////////////////////////////////////////////////////////////////////////
// ztime.h : Declaration and implementation of the Time class.
//

#include <cmath>
#include <cstdint>

/////////////////////////////////////////////////////////////////////////////
//
// Time
//
/////////////////////////////////////////////////////////////////////////////

class Time {
private:
    uint32_t m_dwTime;
    friend class DTime;

    static  thread_local uint32_t s_dwPauseStart;
    static  thread_local uint32_t s_dwNegativeOffset;

#ifdef _DEBUG_TRAINING
    static  thread_local uint32_t s_dwLastTime;
    static  thread_local uint32_t s_dwAccumulatedTime;
    static  thread_local  int32_t s_iShift;
    static  thread_local uint32_t s_dwLastClockTime;
#endif

public:
    static  float   fResolution (void) {return 1000.f;}

    static  void    Pause (void);
    static  bool    IsPaused (void);
    static  void    Continue (void);

#ifdef _DEBUG_TRAINING
    static  int     GetShift (void);
    static  void    SetShift (int iShift);
#endif

    static Time Now(void);

    inline Time(void)
    {
    }

    inline Time(uint32_t  dwTime) :
        m_dwTime(dwTime)
    {
    }

    inline Time(const Time& t) :
        m_dwTime(t.m_dwTime)
    {
    }

    inline Time Before(void) const
    {
        return Time(m_dwTime - 1);
    }

    inline Time After(void) const
    {
        return Time(m_dwTime + 0x7fffffff);
    }

    inline bool    operator >  (const Time     t) const
    {
        return ((int)(m_dwTime - t.m_dwTime) > 0);
    }

    inline bool    operator >= (const Time     t) const
    {
        return ((int)(m_dwTime - t.m_dwTime) >= 0);
    }

    inline bool    operator <  (const Time     t) const
    {
        return ((int)(m_dwTime - t.m_dwTime) < 0);
    }

    inline bool    operator <= (const Time     t) const
    {
        return ((int)(m_dwTime - t.m_dwTime) <= 0);
    }

    inline bool    operator == (const Time     t) const
    {
        return m_dwTime == t.m_dwTime;
    }

    inline bool    operator != (const Time     t) const
    {
        return m_dwTime != t.m_dwTime;
    }

    inline Time    operator =  (uint32_t  tick)
    {
        this->m_dwTime = tick;

        return *this;
    }

    inline Time    operator +  (float  d) const
    {
        Time   t(m_dwTime + (int)floor(d * fResolution () + 0.5));

        return t;
    }

    inline Time    operator += (float    d)
    {
        m_dwTime += (int)floor((d * fResolution ()) + 0.5);
        return *this;
    }

    inline Time    operator -  (float    d) const
    {
        Time   t(m_dwTime - (int)floor((d * fResolution ()) + 0.5));

        return t;
    }

    inline Time    operator -= (float    d)
    {
        m_dwTime -= (int)floor((d * fResolution ()) + 0.5);
        return *this;
    }

    inline float    operator -  (const Time     t) const
    {
        return ((float)((int)(m_dwTime - t.m_dwTime))) / fResolution ();
    }

    inline uint32_t   clock(void) const
    {
        return m_dwTime;
    }

    inline void     clock(uint32_t c)
    {
        m_dwTime = c;
    }
};

#endif

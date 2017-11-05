#ifndef _WinTrekP_H__
#define _WinTrekP_H__

#include <igc.h>
namespace SoundEngine
{
    class ISoundPositionSource;
}


//////////////////////////////////////////////////////////////////////////////
//
// Wintrek Private Headers
//
//////////////////////////////////////////////////////////////////////////////

class ThingSitePrivate : public ThingSite {
public:
    virtual void UpdateScreenPosition(
        const Point& pointScreenPosition,
        float fScreenRadius,
        float distanceToEdge,
        unsigned char ucRadarState
    ) {
    }
    virtual TRef<SoundEngine::ISoundPositionSource> GetSoundSource(void) = 0;
};

#endif

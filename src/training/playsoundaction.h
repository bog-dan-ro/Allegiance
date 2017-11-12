/*
**  Copyright (C) 1999 Microsoft Corporation. All Rights Reserved.
**
**  File:	playsoundaction.h
**
**  Author:  
**
**  Description:
**      Header file for the training library "playsoundaction" interface.
**
**  History:
*/
#ifndef _PLAY_SOUND_ACTION_H_
#define _PLAY_SOUND_ACTION_H_

#include <igc.h>
#include <soundbase.h>

#include "Action.h"

namespace Training
{
    //------------------------------------------------------------------------------
    // class definitions
    //------------------------------------------------------------------------------
    class PlaySoundAction : public Action
    {
        public:
                    /* void */              PlaySoundAction (SoundID soundID);
            virtual /* void */              ~PlaySoundAction (void);
            virtual void                    Execute (void);
            virtual void                    Stop (void);
                    bool                    HasStarted (void) const;
                    bool                    HasStopped (void) const;

        protected:
                    SoundID                 m_soundID;
                    TRef<SoundEngine::ISoundInstance>    m_soundInstance;
                    bool                    m_bHasStarted;
    };

    //------------------------------------------------------------------------------
}

#endif  //_PLAY_SOUND_ACTION_H_

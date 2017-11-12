/*
**  File:	mission10.h
**
**  Description:
**      Header file for the training library "Mission FreeFlight" interface.
*/

#ifndef _MISSION_FREEFLIGHT_H_
#define _MISSION_FREEFLIGHT_H_

#include "trainingmission.h"

namespace Training
{
    //------------------------------------------------------------------------------
    // class definitions
    //------------------------------------------------------------------------------
    class Mission10 : public TrainingMission
    {
    public:
        virtual /* void */              ~Mission10(void);
        virtual int                     GetMissionID(void);
        virtual SectorID                GetStartSectorID(void);
        virtual bool                    RestoreShip(void);

    protected:
        virtual void                    CreateUniverse(void);
        virtual Condition*              CreateMission(void);
    };

    //------------------------------------------------------------------------------
}

#endif  //_MISSION_FREEFLIGHT_H_

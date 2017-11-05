/*
**  Copyright (C) 1999 Microsoft Corporation. All Rights Reserved.
**
**  File:	Mission6.h
**
**  Author:  
**
**  Description:
**      Header file for the training library "Mission6" interface.
**
**  History:
*/
#ifndef _MISSION_FIVE_H_
#define _MISSION_FIVE_H_

#include "trainingmission.h"

namespace Training
{
    //------------------------------------------------------------------------------
    // class definitions
    //------------------------------------------------------------------------------
    class Mission6 : public TrainingMission
    {
        public:
            virtual /* void */              ~Mission6 (void);
            virtual int                     GetMissionID (void);
            virtual SectorID                GetStartSectorID (void);
            virtual bool                    RestoreShip (void);

        protected:
            virtual void                    CreateUniverse (void);
            virtual Condition*              CreateMission (void);
    };

    //------------------------------------------------------------------------------
}

#endif  //_MISSION_FIVE_H_

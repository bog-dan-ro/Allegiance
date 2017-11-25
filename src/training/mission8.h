/*
**
**  File:	mission8.h
**
**  Author:  Adam Davison
**
**  Description:
**      Header file for the training library "Mission Nan" interface.
**
**  History:
*/

#ifndef _MISSION_NAN_H_
#define _MISSION_NAN_H_

#include "trainingmission.h"

namespace Training
{

	class Mission8 : public TrainingMission
	{
        public:
            virtual /* void */              ~Mission8 (void);
            virtual int                     GetMissionID (void);
            virtual SectorID                GetStartSectorID (void);
            //virtual bool                    RestoreShip (void);

        protected:
            virtual void                    CreateUniverse (void);
            virtual Condition*              CreateMission (void);

                    Goal*                   CreateGoal01 (void);
                    Goal*                   CreateGoal02 (void);
                    Goal*                   CreateGoal03 (void);
					IshipIGC*               pShip;
					ImissionIGC*			pMission;
					IstationIGC*			pStation;
                    Vector                  homeRedDoor;

    };
}

#endif

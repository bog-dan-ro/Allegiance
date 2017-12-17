/*
**  Copyright (C) 1999 Microsoft Corporation. All Rights Reserved.
**
**  File:	endmissionaction.cpp
**
**  Author:  
**
**  Description:
**      Implementation of the training library "endmissionaction" interface.
**
**  History:
*/
#include    "trainingmission.h"
#include    "endmissionaction.h"

namespace Training
{
    //------------------------------------------------------------------------------
    // global variabes
    //------------------------------------------------------------------------------
    extern TrainingMission*    g_pMission;

    //------------------------------------------------------------------------------
    // class methods
    //------------------------------------------------------------------------------
    /* void */  EndMissionAction::~EndMissionAction (void)
    {
    }

    //------------------------------------------------------------------------------
    void        EndMissionAction::Execute (void)
    {
        g_pMission->Terminate ();
    }

    //------------------------------------------------------------------------------
}

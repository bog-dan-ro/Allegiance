/*
**  Copyright (C) 1999 Microsoft Corporation. All Rights Reserved.
**
**  File:	ShowPaneAction.cpp
**
**  Author:  
**
**  Description:
**      Implementation of the training library "ShowPaneAction" interface.
**
**  History:
*/
#include "ShowPaneAction.h"

#include <Treki.h>

namespace Training
{
    //------------------------------------------------------------------------------
    // class methods
    //------------------------------------------------------------------------------
    /* void */  ShowPaneAction::ShowPaneAction (OverlayMask overlayMask) :
    m_overlayMask (overlayMask)
    {
    }

    //------------------------------------------------------------------------------
    /* void */  ShowPaneAction::~ShowPaneAction (void)
    {
    }

    //------------------------------------------------------------------------------
    void        ShowPaneAction::Execute (void)
    {
        TrekWindow* window = GetWindow ();
        window->TurnOffOverlayFlags (ofTeleportPane |
                                     ofInvestment |
                                     ofGameState |
                                     ofTeam |
                                     ofExpandedTeam |
                                     ofInventory |
                                     ofCommandPane |
                                     ofSectorPane);
        window->TurnOnOverlayFlags (m_overlayMask);
    }

    //------------------------------------------------------------------------------
}

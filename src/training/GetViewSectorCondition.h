/*
**  Copyright (C) 1999 Microsoft Corporation. All Rights Reserved.
**
**  File:	GetViewSectorCondition.h
**
**  Author:  
**
**  Description:
**      Header file for the training library "GetViewSectorCondition" interface.
**
**  History:
*/
#ifndef _GET_VIEW_SECTOR_CONDITION_H_
#define _GET_VIEW_SECTOR_CONDITION_H_

#include <igc.h>

#include "Condition.h"

namespace Training
{
    //------------------------------------------------------------------------------
    // class definitions
    //------------------------------------------------------------------------------
    class GetViewSectorCondition : public Condition
    {
        public:
                    /* void */          GetViewSectorCondition (SectorID sector);
            virtual /* void */          ~GetViewSectorCondition (void);
            virtual bool                Evaluate (void);

        protected:
                    SectorID            m_sector;
    };

    //------------------------------------------------------------------------------
}

#endif  //_GET_SECTOR_CONDITION_H_

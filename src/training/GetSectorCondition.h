/*
**  Copyright (C) 1999 Microsoft Corporation. All Rights Reserved.
**
**  File:	GetSectorCondition.h
**
**  Author:  
**
**  Description:
**      Header file for the training library "GetSectorCondition" interface.
**
**  History:
*/
#ifndef _GET_SECTOR_CONDITION_H_
#define _GET_SECTOR_CONDITION_H_

#include <igc.h>

#include "AbstractTarget.h"
#include "Condition.h"

namespace Training
{
    //------------------------------------------------------------------------------
    // class definitions
    //------------------------------------------------------------------------------
    class GetSectorCondition : public Condition
    {
        public:
                    /* void */          GetSectorCondition (ImodelIGC* pModel, SectorID sector);
                    /* void */          GetSectorCondition (ObjectType objectType, ObjectID objectID, SectorID sector);
                    /* void */          GetSectorCondition (AbstractTarget* pTarget, SectorID sector);
            virtual /* void */          ~GetSectorCondition (void);
            virtual bool                Evaluate (void);

        protected:
                    AbstractTarget*     m_pModel;
                    SectorID            m_sector;
    };

    //------------------------------------------------------------------------------
}

#endif  //_GET_SECTOR_CONDITION_H_

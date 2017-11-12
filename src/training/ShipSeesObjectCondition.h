/*
**  Copyright (C) 1999 Microsoft Corporation. All Rights Reserved.
**
**  File:	ShipSeesObjectCondition.h
**
**  Author:  
**
**  Description:
**      Header file for the training library "ShipSeesObjectCondition" interface.
**
**  History:
*/
#ifndef _SHIP_SEES_OBJECT_CONDITION_H_
#define _SHIP_SEES_OBJECT_CONDITION_H_

#include <igc.h>

#include "AbstractTarget.h"
#include "Condition.h"

namespace Training
{
    //------------------------------------------------------------------------------
    // class definitions
    //------------------------------------------------------------------------------
    class ShipSeesObjectCondition : public Condition
    {
        public:
            /* void */                  ShipSeesObjectCondition (IshipIGC* pShip, ImodelIGC* pTarget);
            /* void */                  ShipSeesObjectCondition (IshipIGC* pShip, ObjectType targetType, ObjectID targetID);
            /* void */                  ShipSeesObjectCondition (ObjectID shipID, ObjectType targetType, ObjectID targetID);
            virtual /* void */          ~ShipSeesObjectCondition (void);
            virtual bool                Evaluate (void);

        protected:
                    AbstractTarget*     m_pShip;
                    AbstractTarget*     m_pTarget;
    };

    //------------------------------------------------------------------------------
}

#endif  //_SHIP_SEES_OBJECT_CONDITION_H_

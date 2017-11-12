/*
**  Copyright (C) 1999 Microsoft Corporation. All Rights Reserved.
**
**  File:	GetPickedCondition.h
**
**  Author:  
**
**  Description:
**      Header file for the training library "GetPickedCondition" interface.
**
**  History:
*/
#ifndef _GET_PICKED_CONDITION_H_
#define _GET_PICKED_CONDITION_H_

#include <igc.h>

#include "AbstractTarget.h"
#include "Condition.h"

namespace Training
{
    //------------------------------------------------------------------------------
    // class definitions
    //------------------------------------------------------------------------------
    class GetPickedCondition : public Condition
    {
        public:
                    /* void */          GetPickedCondition (ObjectType targetType, ObjectID targetID);
            virtual /* void */          ~GetPickedCondition (void);
            virtual bool                Evaluate (void);

        protected:
                    AbstractTarget*     m_pTarget;
    };

    //------------------------------------------------------------------------------
}

#endif  //_GET_PICKED_CONDITION_H_

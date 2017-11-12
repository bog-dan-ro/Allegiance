/*
**  Copyright (C) 1999 Microsoft Corporation. All Rights Reserved.
**
**  File:	GetCommandCondition.h
**
**  Author:  
**
**  Description:
**      Header file for the training library "GetCommandCondition" interface.
**
**  History:
*/
#ifndef _GET_COMMAND_CONDITION_H_
#define _GET_COMMAND_CONDITION_H_

#include <igc.h>

#include "AbstractTarget.h"
#include "Condition.h"

namespace Training
{
    //------------------------------------------------------------------------------
    // class definitions
    //------------------------------------------------------------------------------
    class GetCommandCondition : public Condition
    {
        public:
                    /* void */          GetCommandCondition (IshipIGC* pShip, CommandID command);
                    /* void */          GetCommandCondition (ObjectID shipID, CommandID command);
            virtual /* void */          ~GetCommandCondition (void);
            virtual bool                Evaluate (void);

        protected:
                    AbstractTarget*     m_pShip;
                    CommandID           m_command;
    };

    //------------------------------------------------------------------------------
}

#endif  //_GET_COMMAND_CONDITION_H_

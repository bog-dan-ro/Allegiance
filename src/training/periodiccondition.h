/*
**  Copyright (C) 1999 Microsoft Corporation. All Rights Reserved.
**
**  File:	periodiccondition.h
**
**  Author:  
**
**  Description:
**      Header file for the training library "periodiccondition" interface.
**
**  History:
*/
#ifndef _PERIODIC_CONDITION_H_
#define _PERIODIC_CONDITION_H_

#include <cstdint>

#include "Condition.h"

namespace Training
{
    //------------------------------------------------------------------------------
    // class definitions
    //------------------------------------------------------------------------------
    class PeriodicCondition : public Condition
    {
        public:
                    /* void */          PeriodicCondition (Condition* pCondition, float fPeriod);
            virtual /* void */          ~PeriodicCondition (void);
            virtual bool                Start (void);
            virtual void                Stop (void);
            virtual bool                Evaluate (void);

        protected:
                    Condition*          m_pCondition;
                    uint32_t            m_dwPeriod;
                    uint32_t            m_dwStartTime;
    };

    //------------------------------------------------------------------------------
}

#endif  //_PERIODIC_CONDITION_H_

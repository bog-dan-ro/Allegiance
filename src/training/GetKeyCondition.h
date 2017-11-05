/*
**  Copyright (C) 1999 Microsoft Corporation. All Rights Reserved.
**
**  File:	GetKeyCondition.h
**
**  Author:  
**
**  Description:
**      Header file for the training library "GetKeyCondition" interface.
**
**  History:
*/
#ifndef _GET_KEY_CONDITION_H_
#define _GET_KEY_CONDITION_H_

#include <igc.h>

#include "Condition.h"

namespace Training
{
    //------------------------------------------------------------------------------
    // class definitions
    //------------------------------------------------------------------------------
    class GetKeyCondition : public Condition
    {
        public:
                    /* void */          GetKeyCondition (TrekKey key);
            virtual /* void */          ~GetKeyCondition (void);
            virtual bool                Start (void);
            virtual bool                Evaluate (void);
                    void                KeyPressed (TrekKey key);

        protected:
                    TrekKey             m_key;
                    bool                m_pressed;
    };

    //------------------------------------------------------------------------------
}

#endif  //_GET_KEY_CONDITION_H_

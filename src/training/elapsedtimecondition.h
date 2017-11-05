/*
**  Copyright (C) 1999 Microsoft Corporation. All Rights Reserved.
**
**  File:	elapsedtimecondition.h
**
**  Author:  
**
**  Description:
**      Header file for the training library "elapsedtimecondition" interface.
**
**  History:
*/
#ifndef _ELAPSED_TIME_CONDITION_H_
#define _ELAPSED_TIME_CONDITION_H_

#include "periodiccondition.h"
#include "ntimescondition.h"
#include "truecondition.h"

namespace Training
{
    #define ElapsedTimeCondition(fTime)  NTimesCondition (new PeriodicCondition (new TrueCondition, fTime), 2, true)
}

#endif  //_ELAPSED_TIME_CONDITION_H_

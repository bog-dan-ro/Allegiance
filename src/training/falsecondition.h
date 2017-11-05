/*
**  Copyright (C) 1999 Microsoft Corporation. All Rights Reserved.
**
**  File:	falsecondition.h
**
**  Author:  
**
**  Description:
**      Header file for the training library "falsecondition" interface.
**
**  History:
*/
#ifndef _FALSE_CONDITION_H_
#define _FALSE_CONDITION_H_

#include "notcondition.h"
#include "truecondition.h"

namespace Training
{
    #define FalseCondition  NotCondition (new TrueCondition)
}

#endif  //_FALSE_CONDITION_H_

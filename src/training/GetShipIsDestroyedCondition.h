/*
**  Copyright (C) 1999 Microsoft Corporation. All Rights Reserved.
**
**  File:	getshipisdestroyedcondition.h
**
**  Author:  
**
**  Description:
**      Header file for the training library "getshipisdestroyedcondition" interface.
**
**  History:
*/
#ifndef _GET_SHIP_IS_DESTROYED_CONDITION_H_
#define _GET_SHIP_IS_DESTROYED_CONDITION_H_

#include "GetShipIsDamagedCondition.h"
#include "notcondition.h"

namespace Training
{
    #define GetShipIsDestroyedCondition(ship)               NotCondition (new GetShipIsDamagedCondition (ship, 0.0f))
    #define GetShipIsDestroyedCondition2(shipType, shipID)   NotCondition (new GetShipIsDamagedCondition (shipType, shipID, 0.0f))
}

#endif  //_GET_SHIP_IS_DESTROYED_CONDITION_H_

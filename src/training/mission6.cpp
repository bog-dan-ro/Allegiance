/*
**  Copyright (C) 1999 Microsoft Corporation. All Rights Reserved.
**
**  File:	Mission6.cpp
**
**  Author:  
**
**  Description:
**      Implementation of the sixth training mission
**
**  History:
*/
#include    "mission6.h"

#include    "Training.h"
#include    "goallist.h"
#include    "conditionalaction.h"
#include    "GetShipIsDestroyedCondition.h"
#include    "falsecondition.h"
#include    "elapsedtimecondition.h"
#include    "setdisplaymodeaction.h"
#include    "CreateDroneAction.h"
#include    "messageaction.h"

namespace Training
{
    //------------------------------------------------------------------------------
    // class methods
    //------------------------------------------------------------------------------
    /* void */  Mission6::~Mission6 (void)
    {
    }

    //------------------------------------------------------------------------------
    int         Mission6::GetMissionID (void)
    {
        return c_TM_6_Practice_Arena;
    }

    //------------------------------------------------------------------------------
    SectorID    Mission6::GetStartSectorID (void)
    {
        return 2080; //new map
    }

    //------------------------------------------------------------------------------
    bool        Mission6::RestoreShip (void)
    {
        // end the mission
        Terminate ();

        // and return false so the engine stays in the override camera mode
        return false;
    }

    //------------------------------------------------------------------------------
    void        Mission6::CreateUniverse (void)
    {
        LoadUniverse("training_6", 488, 1030);    // 488 = Adv. IC fighter

        // activate all the starting weapons
        trekClient.fGroupFire = true;

        // Adjust loadout
        IshipIGC*       pShipU = trekClient.GetShip();
        // destroy mounted dumbfires
        IpartIGC*       pPart = pShipU->GetMountedPart(ET_Magazine, 0);
        if (pPart)
            pPart->Terminate();;
        // Mount Seeker 2s
        AddPartToShip(154, 0, 5);
        // Change missiles in cargo for Seeker 2s
        for (int i = -1; i >= -c_maxCargo; i--) {
            pPart = pShipU->GetMountedPart(NA, i);
            if (pPart->GetEquipmentType() == ET_Magazine)
            {
                pPart->Terminate();
                AddPartToShip(154, i, 5);
            }
        }
        trekClient.SaveLoadout(pShipU);
        //Add tech, so equipment doesn't show as new treassure and can be got at the station
        TechTreeBitMask ttbm = trekClient.GetSide()->GetDevelopmentTechs();
        ttbm |= trekClient.GetCore()->GetPartType(154)->GetEffectTechs();   //Seeker 2 tech
        ttbm |= trekClient.GetCore()->GetPartType(13)->GetEffectTechs();    //Mine Pack 1 tech
        ttbm |= trekClient.GetCore()->GetPartType(13)->GetRequiredTechs();
        ttbm |= trekClient.GetCore()->GetPartType(174)->GetEffectTechs();   //Hvy Booster tech
        ttbm |= trekClient.GetCore()->GetPartType(174)->GetRequiredTechs();
        trekClient.GetSide()->SetDevelopmentTechs(ttbm);
    }

    //------------------------------------------------------------------------------
    Condition*  Mission6::CreateMission (void)
    {
        m_commandViewEnabled = true;

        GoalList*   pGoalList = new GoalList;

        ImissionIGC*        pMission = trekClient.GetCore();
        ImodelIGC*          pHomeStation = pMission->GetModel(OT_station, 2080);

        // put the commander ship in the station
        {
            IshipIGC*       pCommander = trekClient.GetCore()->GetShip(m_commanderID);
            pCommander->SetStation(static_cast<IstationIGC*> (pHomeStation));
            pCommander->SetCommand(c_cmdAccepted, NULL, c_cidDoNothing);
            pCommander->SetCommand(c_cmdCurrent, NULL, c_cidDoNothing);
            pCommander->SetAutopilot(false);
        }

        // play the introductory audio
        pGoalList->AddGoal (CreatePlaySoundGoal (salCommenceScanSound));

        // create friendly miner 01
        {
            Goal*	pGoal = new Goal(new ElapsedTimeCondition(0.5f));

            ShipID          minerID = pMission->GenerateNewShipID();
            Vector          pos = Vector(0.0f, 2500.0f, 100.0f); //create forward to draw aggro

            CreateDroneAction*  pCreateDroneAction = new CreateDroneAction("Miner 01", minerID, 438, 0, c_ptMiner);
            pCreateDroneAction->SetCreatedLocation(GetStartSectorID(), pos);
            pGoal->AddStartAction(pCreateDroneAction);

            pGoalList->AddGoal(pGoal);
        }

		// tm_6_01
		// Okay, Cadet, here's your Advanced Fighter. There's a base 
		// outpost here in case you need to replenish yourself.
        pGoalList->AddGoal (CreatePlaySoundGoal (tm_6_01Sound));

        // create friendly miner 02, wait two more seconds in cockpit
        {
            Goal*	pGoal = new Goal(new ElapsedTimeCondition(2.0f));

            ShipID          minerID = pMission->GenerateNewShipID();
            Vector          pos = pHomeStation->GetPosition();
            pos.x += 250.0f; //simulate undock
            pos.y += 200.0f;

            CreateDroneAction*  pCreateDroneAction = new CreateDroneAction("Miner 02", minerID, 438, 0, c_ptMiner);
            pCreateDroneAction->SetCreatedLocation(GetStartSectorID(), pos);
            pGoal->AddStartAction(pCreateDroneAction);

            pGoal->AddStartAction(new SetDisplayModeAction(TrekWindow::cmCockpit));

            pGoalList->AddGoal(pGoal);
        }

		// tm_6_02
		// Iron Coalition Intelligence reports inbound enemy craft. 
		// They're using an old code for their comms, so we can hear 
		// them. Watch your message stream to see what they're up to.
        {
            Goal*   pGoal = CreatePlaySoundGoal (tm_6_02Sound);
            pGoal->AddStartAction (new MessageAction ("Watch the chat to see what the enemy craft are after."));
            pGoalList->AddGoal (pGoal);
        }

        // create friendly miner 03
        {
            Goal*	pGoal = new Goal(new ElapsedTimeCondition(0.2f));

            ShipID          minerID = pMission->GenerateNewShipID();
            Vector          pos = pHomeStation->GetPosition();
            pos.x += -250.0f; //simulate undock
            pos.y += -200.0f;

            CreateDroneAction*  pCreateDroneAction = new CreateDroneAction("Miner 03", minerID, 438, 0, c_ptMiner);
            pCreateDroneAction->SetCreatedLocation(GetStartSectorID(), pos);
            pGoal->AddStartAction(pCreateDroneAction);

            pGoalList->AddGoal(pGoal);
        }

        // wait half  second
        pGoalList->AddGoal (new Goal (new ElapsedTimeCondition (0.5f)));

		// tm_6_03
		// DEFEND THE MINERS! This simulation is over when you die.
        pGoalList->AddGoal (CreatePlaySoundGoal (tm_6_03Sound));

        // create enemy carrier
        {
            Goal*	pGoal = new Goal(new ElapsedTimeCondition(1.0f));

            ShipID          carrierID = pMission->GenerateNewShipID();
            Vector          pos = Vector(3560.0f, 4880.0f, 850.0f); //Near Neptune aleph

            CreateDroneAction*  pCreateDroneAction = new CreateDroneAction("Enemy Carrier", carrierID, 325, 1, c_ptCarrier);
            pCreateDroneAction->SetCreatedLocation(2081, pos); //Mars sector 2081
            pGoal->AddStartAction(pCreateDroneAction);

            pGoalList->AddGoal(pGoal);
        }

        // wait one more second
        pGoalList->AddGoal(new Goal(new ElapsedTimeCondition(1.0f)));

        //create enemy ids to reuse
        ShipID              enemyScoutID = pMission->GenerateNewShipID();
        ShipID              enemyFighterID = pMission->GenerateNewShipID();
        //spawn enemies
        {
            Goal*           pGoal = new Goal(new ElapsedTimeCondition(8.0f));

            CreateDroneAction*  pCreateEnemyScoutAction = new CreateDroneAction("Enemy Support", enemyScoutID, 310, 1, c_ptWingman); //310 == Bios Scout
            pCreateEnemyScoutAction->SetCreatedLocation(GetStartSectorID(), Vector(3800.0f, 4275.0f, 855.0f));
            CreateDroneAction* pCreateEnemyFighterAction = new CreateDroneAction("Enemy Fighter", enemyFighterID, 315, 1, c_ptWingman); //315 == Bios Fighter
            pCreateEnemyFighterAction->SetCreatedLocation(GetStartSectorID(), Vector(3800.0f, 4175.0f, 855.0f));

            pGoal->AddStartAction(pCreateEnemyScoutAction);
            pGoal->AddStartAction(pCreateEnemyFighterAction);

            pGoalList->AddGoal(pGoal);
        }

        // create enemy miners
        {
            Goal*	pGoal = new Goal(new ElapsedTimeCondition(1.0f));

            ShipID          minerID = pMission->GenerateNewShipID();
            Vector          pos = Vector(3080.0f, -440.0f, -700.0f); //near mid he-3

            CreateDroneAction*  pCreateDroneAction = new CreateDroneAction("Enemy Miner 01", minerID, 338, 1, c_ptMiner);
            pCreateDroneAction->SetCreatedLocation(2082, pos); //sector "Enemy"
            pGoal->AddStartAction(pCreateDroneAction);

            minerID = pMission->GenerateNewShipID();
            pos = Vector(-1760.0f, -3240.0f, -700.0f); //near lower left he-3
            pCreateDroneAction = new CreateDroneAction("Enemy Miner 02", minerID, 338, 1, c_ptMiner);
            pCreateDroneAction->SetCreatedLocation(2082, pos); //sector "Enemy"
            pGoal->AddStartAction(pCreateDroneAction);

            pGoalList->AddGoal(pGoal);
        }
        // create friendly miner 04
        {
            Goal*	pGoal = new Goal(new ElapsedTimeCondition(1.0f));

            ShipID          minerID = pMission->GenerateNewShipID();
            Vector          pos = pHomeStation->GetPosition();
            pos.x += 250.0f; //simulate undock
            pos.y += 200.0f;

            CreateDroneAction*  pCreateDroneAction = new CreateDroneAction("Miner 04", minerID, 437, 0, c_ptMiner);
            pCreateDroneAction->SetCreatedLocation(GetStartSectorID(), pos);
            pGoal->AddStartAction(pCreateDroneAction);

            pGoalList->AddGoal(pGoal);
        }

        //respawn the enmies if destroyed (or not yet created)
        {
            Goal*               pGoal = new Goal(new FalseCondition); //will never evaluate as true - wait for player to be dead

                                                                      //can't reuse old actions, or clean-up will fail
            CreateDroneAction*  pCreateEnemyScoutAction = new CreateDroneAction("Enemy Support", enemyScoutID, 310, 1, c_ptWingman); //310 == Bios Scout
            pCreateEnemyScoutAction->SetCreatedLocation(GetStartSectorID(), Vector(3800.0f, 4275.0f, 855.0f));
            CreateDroneAction* pCreateEnemyFighterAction = new CreateDroneAction("Enemy Fighter", enemyFighterID, 315, 1, c_ptWingman); //315 == Bios Fighter
            pCreateEnemyFighterAction->SetCreatedLocation(GetStartSectorID(), Vector(3800.0f, 4175.0f, 855.0f));

            Condition*          pShipIsDestroyedcondition = new GetShipIsDestroyedCondition2(OT_ship, static_cast<ObjectID> (enemyScoutID));
            pGoal->AddConstraintCondition(new ConditionalAction(pShipIsDestroyedcondition, pCreateEnemyScoutAction));
            pShipIsDestroyedcondition = new GetShipIsDestroyedCondition2(OT_ship, static_cast<ObjectID> (enemyFighterID));
            pGoal->AddConstraintCondition(new ConditionalAction(pShipIsDestroyedcondition, pCreateEnemyFighterAction));

            pGoalList->AddGoal(pGoal);
        }

        return new Goal(pGoalList);

    }

    //------------------------------------------------------------------------------
}



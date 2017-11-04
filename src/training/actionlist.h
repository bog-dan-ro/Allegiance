/*
**  Copyright (C) 1999 Microsoft Corporation. All Rights Reserved.
**
**  File:	actionlist.h
**
**  Author:  
**
**  Description:
**      Header file for the training library "actionlist" interface.
**
**  History:
*/
#ifndef _ACTION_LIST_H_
#define _ACTION_LIST_H_

#include <list>

namespace Training
{
    class Action;
    //------------------------------------------------------------------------------
    // class definitions
    //------------------------------------------------------------------------------
    class ActionList : public Action
    {
        public:
                    /* void */          ActionList (void);
            virtual /* void */          ~ActionList (void);
            virtual void                Execute (void);
            virtual void                Stop (void);
                    void                AddAction (Action* pAction);

        protected:
                    std::list<Action*>              m_actionList;
    };

    //------------------------------------------------------------------------------
}

#endif  //_ACTION_LIST_H_

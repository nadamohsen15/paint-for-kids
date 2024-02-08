#pragma once

#include "Action.h"

//Add Square Action class
class ActionSwitchToPlay : public Action
{
public:
	ActionSwitchToPlay(ApplicationManager* pApp);

	//Add Square to the ApplicationManager
	virtual void Execute();


};
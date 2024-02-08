#pragma once

#include "Action.h"

class ActionPlayReset : public Action
{
public:
	ActionPlayReset(ApplicationManager* pApp);

	virtual void Execute();


};
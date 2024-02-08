#pragma once
#include "Actions/Action.h"
#include "./Figures/CFigure.h"
class ActionResize : public Action
{
	CFigure* selected = NULL;
	
public:
	ActionResize(ApplicationManager* pApp);
	void ActionResize::Execute();

};


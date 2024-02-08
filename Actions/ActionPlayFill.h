#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"


class ActionPlayFill :public Action
{
public:
	ActionPlayFill(ApplicationManager* mgr);
	void Execute();
};


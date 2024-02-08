#pragma once

#include "Action.h"
#include "..\DefS.h"

class ApplicationManager;
class Action;



class ActionPlayBy :public Action
{

public:

	static int correct;
	static int wrong;
	static string inGameType;
	static ActionType type;
	static color SessionClr;

	ActionPlayBy(ApplicationManager* pApp);

	virtual void Execute() = 0;

	static void resetGame();

};

#include "ActionPlayReset.h"
#include "../ApplicationManager.h"
#include "../GUI/GUI.h"
#include "Action.h"
#include "ActionPlayBy.h"

ActionPlayReset::ActionPlayReset(ApplicationManager* pApp) :Action(pApp) {};

void ActionPlayReset::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	ActionPlayBy::resetGame();
	pGUI->ClearStatusBar();
	pGUI->PrintMessage("Game reset sucessfully");

	pManager->setVisabilityToTrue();
}

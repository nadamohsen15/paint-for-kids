#include "Action.h"
#include "ActionPlayBy.h"
#include "ActionSwitchToPlay.h"
#include "..\GUI\GUI.h"
#include "..\ApplicationManager.h"


ActionSwitchToPlay::ActionSwitchToPlay(ApplicationManager* pApp) :Action(pApp)
{}

//Execute the action
void ActionSwitchToPlay::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	pGUI->ClearToolBarArea();
	pGUI->ClearDrawArea();
	pGUI->CreatePlayToolBar();
}
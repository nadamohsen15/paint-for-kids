#include "ActionChngBkGrndClr.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionChngBkGrndClr::ActionChngBkGrndClr(ApplicationManager* pApp) :Action(pApp)
{}

void ActionChngBkGrndClr::Execute() {
	//Get a Pointer to the Input / Output Interfaces

	GUI* pGUI = pManager->GetGUI();

	pGUI->PrintMessage("Choose BackGround Color");
	UI.InterfaceMode = MODE_COLOR;
	//Reads the input draw color
	if (pManager->GetColor(BkGrndClr)) {
		pGUI->setCrntBKGrandColor(BkGrndClr);
		pGUI->ClearDrawArea();
		pGUI->CreateColorBar();
		pGUI->CreateDrawToolBar();
	}
	else
	{
		UI.InterfaceMode = MODE_DRAW;
		return;
	}
}

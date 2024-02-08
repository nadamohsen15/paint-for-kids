#include "ApplicationManager.h"
#include "ActionPlayBy.h"
#include "GUI\GUI.h"
#include "DEFS.h"

int ActionPlayBy::correct = 0;
int ActionPlayBy::wrong = 0;
ActionType ActionPlayBy::type = EMPTY;
string ActionPlayBy::inGameType = "";
color ActionPlayBy::SessionClr = color(255, 255, 255);
int  CFigure::newID = 0;

int main()
{
	/*
	GUI* g=new GUI();
	
	
	window* w=g->CreateWind(200, 300, 10, 10);
	int x, y;
	w->WaitMouseClick(x, y);
	*/
	
	ApplicationManager AppManager;
	AppManager.Run();		
	return 0;
}


#include "ActionPlayBy.h"
#include "..\ApplicationManager.h"
#include "Action.h"

ActionPlayBy::ActionPlayBy(ApplicationManager* pApp) :Action(pApp) {};

 void ActionPlayBy::resetGame() {
	 ActionPlayBy::correct = 0;
	 ActionPlayBy::wrong = 0;
	 ActionPlayBy::inGameType = "";
	 ActionPlayBy::type = EMPTY;

}


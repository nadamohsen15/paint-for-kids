#include "ActionPlayTypeFill.h"
#include "..\ApplicationManager.h"
#include "ActionPlayBy.h"
#include "..\GUI\GUI.h"
ActionPlayTypeFill::ActionPlayTypeFill(ApplicationManager* mgr) :Action(mgr)
{
}

void ActionPlayTypeFill::Execute()
{
	GUI *pGUI = pManager->GetGUI();
	int x = 0, y = 0;
	if (ActionPlayBy::type != ACTION_PLAY_TYPEFILL) {
		ActionPlayBy::correct = 0;
		ActionPlayBy::wrong = 0;
		ActionPlayBy::type = ACTION_PLAY_TYPEFILL;
		pManager->setVisabilityToTrue();
		pGUI->PrintMessage("Please Click On A Shape!!");
		CFigure* fig = pManager->GetRandomExitingTypeT();
		if (fig == NULL) {
			pGUI->PrintMessage("No Figure Plz Draw Some Figures");
			return;
		}
		ActionPlayBy::inGameType = fig->getShapeType();
		ActionPlayBy::SessionClr = fig->getColor();
		string c = pGUI->MapColortoString(ActionPlayBy::SessionClr);
		pGUI->PrintMessage("choose " + ActionPlayBy::inGameType + "with color " + c);

	}
	else {
		pGUI->GetPointClicked(x, y);
		CFigure* fig2 = pManager->GetFigure(x, y);
		if (fig2 == NULL || fig2->isVisible() == false) {
			pGUI->PrintMessage("Not A Shape");
			return;
		}
		if (pGUI->ColorsEq(fig2->getColor(), ActionPlayBy::SessionClr) && fig2->getShapeType() == ActionPlayBy::inGameType) {
			ActionPlayBy::correct++;
		}
		else {
			ActionPlayBy::wrong++;
		}
		fig2->setVisibility(false);
		int shapesCount = pManager->getNumberOfShapesColor(ActionPlayBy::inGameType, ActionPlayBy::SessionClr);

		pGUI->PrintMessage("Correct: " + to_string(ActionPlayBy::correct) + " || Wrong:" + to_string(ActionPlayBy::wrong));
		//the user has number of trys equal to the right shapes
		if (ActionPlayBy::correct == shapesCount || ActionPlayBy::wrong == 3) {
			string msg = ActionPlayBy::correct >= ActionPlayBy::wrong ? "You Won" : "You Lost";
			pManager->setVisabilityToTrue();
			pGUI->PrintMessage(msg);
			ActionPlayBy::resetGame();
		}

	}

	
}

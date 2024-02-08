#include "ActionPlayFill.h"
#include "ActionPlayBy.h"


ActionPlayFill::ActionPlayFill(ApplicationManager* mgr) :Action(mgr){}

void ActionPlayFill::Execute()
{
    GUI* pGUI = pManager->GetGUI();
    int x = 0, y = 0;
    if (ActionPlayBy::type != ACTION_PLAY_FILL) {
        ActionPlayBy::correct = 0;
        ActionPlayBy::wrong = 0;
        ActionPlayBy::type = ACTION_PLAY_FILL;
        CFigure* Rfig = pManager->GetRandomExitingTypeT();
        if (Rfig == NULL) {
            pGUI->PrintMessage("there is no shapes :(");
            return;
        }
        string clr = pGUI->MapColortoString(Rfig->getColor());
        ActionPlayBy::SessionClr = pGUI->MapStringtoColor[clr];
        pGUI->PrintMessage("Get All Shapes with Color " + clr);
        pManager->setVisabilityToTrue();


    }
    else {
        pGUI->GetPointClicked(x, y);
        CFigure* fig = pManager->GetFigure(x, y);

        if (fig == NULL) {
            pGUI->PrintMessage("Not A Shape");
            return;
        }
        // == and != operators for class color not working and there is no cpp file for color class
        color  figcolor = fig->getColor();

        if (pGUI->ColorsEq(ActionPlayBy::SessionClr, figcolor) && (fig->isVisible())) {

            ActionPlayBy::correct++;
            fig->setVisibility(false);


        }
        else {
            ActionPlayBy::wrong++;
            fig->setVisibility(false);

        }

        pGUI->PrintMessage("Correct: " + to_string(ActionPlayBy::correct) + " || Wrong:" + to_string(ActionPlayBy::wrong));
        int nOfShapesInColor = pManager->getNumberOfAllShapesColor(ActionPlayBy::SessionClr);
        //the user has number of trys equal to the right shapes
        if (nOfShapesInColor == ActionPlayBy::correct || ActionPlayBy::wrong == 3) {
            string msg = (ActionPlayBy::correct >= ActionPlayBy::wrong) ? "You Won" : "You lost";
            pGUI->PrintMessage(msg);
            pManager->setVisabilityToTrue();
            ActionPlayBy::resetGame();
        }
    }


}


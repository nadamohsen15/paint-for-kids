#include "ActionSelect.h"
#include "Actions/Action.h"
#include "GUI/GUI.h"
#include "./ApplicationManager.h"
#include "CFigure.h"


    ActionSelect::ActionSelect(ApplicationManager* AppMgr):Action(AppMgr) {
                
    }
    void ActionSelect::Execute() {
        GUI* pGUI = pManager->GetGUI();
        Point P;
        pGUI->PrintMessage("click on a shape to select/unselect");
        pGUI->GetPointClicked(P.x,P.y);
      
        CFigure* fig = pManager->GetFigure(P.x, P.y);

        if (fig == NULL) {
            pGUI->PrintMessage("there is no shape in clicked points");
        }
        else {

            if (!fig->IsSelected()) {
                fig->SetSelected(true);
                fig->ChngDrawClr(BISQUE);
                pManager->AddSelectedFigure(fig);
                fig->printFigInfo(pGUI);
            }

            else if(fig->IsSelected() ){
                fig->SetSelected(false);
                fig->ChngDrawClr(UI.DrawColor);
                pManager->RemoveSelectedFigure(fig);
            }
        }
    }




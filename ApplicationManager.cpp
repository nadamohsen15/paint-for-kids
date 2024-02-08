#include "ApplicationManager.h"
#include "Actions\ActionAddSquare.h"
#include "ActionDelete.h"
#include "ActionResize.h"
#include "ActionSelect.h"
#include "ActionSwitchToDrawMode.h"
#include "ActionResize.h"
#include "ActionMove.h"
#include "Actions/ActionSendToBack.h"
#include "Actions/ActionSendToFront.h"
#include "Actions/ActionLoad.h"
#include "Actions/ActionSave.h"
#include "Actions/ActionChangeDrawColor.h"
#include "Actions/ActionChangeFillColor.h"
#include "Actions/ActionChngBkGrndClr.h"
#include"Actions/ActionAddEllipse.h"
#include"Actions/ActionAddHexagon.h"
#include"Actions/ActionExit.h"
#include "ActionSwitchToPlay.h"
#include "ActionPlayReset.h"
#include "ActionPlayByType.h"
#include "ActionPlayFill.h"
#include "ActionPlayTypeFill.h"
#include <string>
#include <string.h>
#include <iostream>
#include <sstream>

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pGUI = new GUI;	
	
	FigCount = 0;
	SelectedCount = 0;
		
	//Create an array of figure pointers and set them to NULL		
	for(int i=0; i<MaxFigCount; i++)
	{ 
		FigList[i] = NULL;	
		SelectedFigures[i] = NULL;
	}
}

void ApplicationManager::Run()
{
	ActionType ActType;
	do
	{		
		//1- Read user action
		ActType = pGUI->MapInputToActionType();

		//2- Create the corresponding Action
		Action *pAct = CreateAction(ActType);
		
		//3- Execute the action
		ExecuteAction(pAct);

		//4- Update the interface
		UpdateInterface();

	}while(ActType != EXIT);
	
}


//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
//Creates an action
Action* ApplicationManager::CreateAction(ActionType ActType) 
{
	Action* newAct = NULL;
	
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
		case DRAW_SQUARE:
			newAct = new ActionAddSquare(this);
			break;

		case DRAW_ELPS:
			///create AddLineAction here
			newAct = new ActionAddEllipse(this);
			break;
		case DRAW_HEX:
			newAct = new ActionAddHexagon(this);
			break;
		case DEL:
			newAct = new ActionDelete(this);
			break;

		case RESIZE:
			newAct = new ActionResize(this);
			break;

		case MOVE:
			newAct = new ActionMove(this);
			break;
		
		case GO_BACK:
			newAct = new ActionSwitchToDrawMode(this);
			break;

		case DRAWING_AREA:
			newAct = new ActionSelect(this);
			break;

		//New Actions Added
		case SAVE:
			newAct = new ActionSave(this, FigCount);
			break;

		case LOAD:
			newAct = new ActionLoad(this);
			break;

		case BACK:
			newAct = new ActionSendToBack(this);
			break;

		case FRONT:
			newAct = new ActionSendToFront(this);
			break;
		//color Actions
		case CHNG_DRAW_CLR:
			newAct = new ActionChangeDrawColor(this);
			break;
		case CHNG_BK_CLR:
			newAct = new ActionChngBkGrndClr(this);
			break;
		case CHNG_FILL_CLR:
			newAct = new ActionChangeFillColor(this);
			break;

		case TO_PLAY:
			newAct = new ActionSwitchToPlay(this);
			break;

		case ACTION_PLAY_TYPE:
			newAct = new ActionPlayByType(this);
			break;

		case ACTION_PLAY_FILL:
			newAct = new ActionPlayFill(this);
			break;

		case ACTION_PLAY_TYPEFILL:
			newAct = new ActionPlayTypeFill(this);
			break;

		case ACTION_PLAY_RESET:
			newAct = new ActionPlayReset(this);
			break;

		case ACTION_TO_DRAW:
			newAct = new ActionSwitchToDrawMode(this);
			break;



		case EXIT:
			newAct = new ActionExit(this);
			///create ExitAction here
			
			break;
		
		case STATUS:	//a click on the status bar ==> no action
			return NULL;
			break;

	}
	//UndoStack->push(newAct);
	return newAct;
}
//////////////////////////////////////////////////////////////////////
//Executes the created Action
void ApplicationManager::ExecuteAction(Action* &pAct) 
{	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		//delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if(FigCount < MaxFigCount )
		FigList[FigCount++] = pFig;	
}
////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(int x, int y) const
{
	
	for (int i = FigCount - 1; i >= 0; i--)
	{
		if (FigList[i]->insideFigure(x, y) && FigList[i]->isVisible())
			return FigList[i];
	}
	return NULL;
}

CFigure* ApplicationManager::GetFigure(int indx)
{
	if(indx < FigCount && indx >= 0)
		return FigList[indx];

	return NULL;
}


int ApplicationManager::numberOfShapes()
{
	return FigCount;
}

string ApplicationManager::getRandomExistingType()
{
	//generating Random index 
	int RandomIndex = rand() % FigCount;
	return FigList[RandomIndex]->getShapeType();
}

int ApplicationManager::getNumberOfAllShapesColor(color clr) {
	int count = 0;
	for (int i = 0;i < FigCount;i++) {
		if (pGUI->ColorsEq(FigList[i]->getColor(), clr)) {
			count++;
		}
	}
	return count;
}
int ApplicationManager::getNumberOfShapesColor(string t, color c) {
	int count = 0;
	for (int i = 0;i < FigCount;i++) {
		if (FigList[i]->getShapeType() == t && pGUI->ColorsEq(FigList[i]->getColor(), c)) {
			count++;
		}
	}
	return count;
}

CFigure* ApplicationManager::GetRandomExitingTypeT() {
	if (FigCount <= 0) {
		return NULL;
	}
	return FigList[rand() % FigCount];
}


int ApplicationManager::countByType(string type) {
	int count = 0;
	for (int i = 0; i < FigCount; i++)
		if (FigList[i]->getShapeType() == type)
			count++;
	return count;
}

void ApplicationManager::setVisabilityToTrue() {
	for (int i = 0;i < FigCount;i++) {
		FigList[i]->setVisibility(true);
	}
}

//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	if (UI.InterfaceMode == MODE_PLAY) {
		pGUI->ClearDrawArea();
	}

	for (int i = 0; i < FigCount; i++)
	{

		if (FigList[i]->isVisible())
			FigList[i]->DrawMe(pGUI);
	}
	
}

////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the interface
GUI *ApplicationManager::GetGUI() const
{	return pGUI; }
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<FigCount; i++)
		delete FigList[i];
	delete pGUI;
	
}


//==================================================================================//
//							Selection Functions										//
//==================================================================================//
int ApplicationManager :: GetSelectedCount() {
	return SelectedCount;
}

CFigure** ApplicationManager :: GetSelectedFigures() {
	return SelectedFigures;
}

void ApplicationManager :: AddSelectedFigure(CFigure* selected)
{
	SetSelectedFigure(selected);
	SelectedFigures[SelectedCount] = selected;
	SelectedCount++;
}

void ApplicationManager::RemoveSelectedFigure(CFigure* selected)
{
	for (int i = 0; i < SelectedCount; i++) {
		if (SelectedFigures[i] == selected) {
			SelectedFigures[i] = SelectedFigures[SelectedCount - 1];
			SelectedFigures[SelectedCount - 1] = NULL;
			SelectedCount--;
		}
	}
}

//Set the selected Figure For the Select Action
void ApplicationManager :: SetSelectedFigure(CFigure* selected)
{
	SelectedFigure = selected;
}

CFigure* ApplicationManager::GetSelectedFigure() {
	return SelectedFigure;
}

// Getting selected Figure ID
int ApplicationManager::GetSelectedFigureID() {
	for (int i = FigCount - 1; i >= 0; i--)
	{
		if (FigList[i] != NULL) {
			if (FigList[i]->IsSelected())
				return i;
		}
	}
	return -1;
}



//==================================================================================//
//							 Deletion Functions										//
//==================================================================================//

void ApplicationManager::RemoveFig(int ID) {
	// Loop to shift Elements 
	for (int i = ID; i < FigCount - 1; i++) {
		FigList[i] = FigList[i + 1];
		FigList[i]->SetID(i);
	}
	//reduce Figcount by 1 and Remove from FigList
	FigCount--;
	FigList[FigCount] = NULL;
}

// clear Selected Figures Array

void ApplicationManager::ClearSelectedFigures() {
	for (int i = 0; i < SelectedCount; i++) {
		SelectedFigures[i] = NULL;
	}
	SelectedCount = 0;
}
void ApplicationManager::deleteALLFig()
{
	for (int i = 0; i < FigCount; i++)
	{
		FigList[i] = NULL;

	}

	FigCount = 0;
}

//==================================================================================//
//							 Move Functions											//
//==================================================================================//
void ApplicationManager::moveFigure()
{
	int x, y;
	int x1, y1;
	while (!pGUI->isLeftButtonPressed(x, y)) { ; }
	while(pGUI->isLeftButtonPressed(x, y)) {		
		SelectedFigure->getCenter(x1, y1);
		int dx = x - x1;
		int dy = y - y1;
		SelectedFigure->Move(dx, dy, GetGUI());
		pGUI->ClearDrawArea();
		UpdateInterface();
	}
	pGUI->CreateColorBar();
};

//==================================================================================//
//							Undo/Redo Functions										//
//==================================================================================//
//void ApplicationManager::Undo() {
	//Action* pAct = UndoStack->pop();
	//pAct->Undo();
	//RedoStack->push(pAct);
//}

void ApplicationManager::Redo() {
	Action* pAct = RedoStack->pop();
	pAct->Execute();
	UndoStack->push(pAct);
}
void ApplicationManager::removeLastFigure() {
	FigList[FigCount - 1] = NULL;
	FigCount--;
}

//==================================================================================//
//							Send to Back/Front Functions							//
//==================================================================================//

void ApplicationManager::SendToFront(int index) {
	CFigure* SelectedFigure = FigList[index];
	for (int i = index; i < FigCount - 1; i++)
		FigList[i] = FigList[i + 1];

	FigList[FigCount - 1] = SelectedFigure;
}

void ApplicationManager::SendToBack(int index) {
	CFigure* SelectedFigure = FigList[index];
	for (int i = index; i > 0; i--)
		FigList[i] = FigList[i - 1];

	FigList[0] = SelectedFigure;
}

//==================================================================================//
//				                 save & load                     					//
//==================================================================================//


string ApplicationManager::colorToString(color c)
{
	cout << "color";
	std::ostringstream os;
	os << int(c.ucRed) << "\t";
	os << int(c.ucGreen) << "\t";
	os << int(c.ucBlue);

	std::string s = os.str();

	return s;
}

void ApplicationManager::SaveFile(ofstream& outputfile)
{

	for (int i = 0; i < FigCount; ++i)
	{
		cout << "save done ";
		FigList[i]->Save(outputfile);
	}



}

//==================================================================================//
//						Colors Functions		     		                        //
//==================================================================================//


bool ApplicationManager::GetColor(color& inputColor)
{

	bool isColor = true;

	ActionType inputColorAction = pGUI->MapInputToActionType();
	cout << inputColorAction << endl;
	switch (inputColorAction) {

	case SET_RED:
		inputColor = RED;
		break;

	case SET_GREEN:
		inputColor = GREEN;
		break;

	case SET_BLUE:
		inputColor = BLUE;
		break;

	case SET_PINK:
		inputColor = PINK;
		break;

	case SET_MAROON:
		inputColor = MAROON;
		break;

	case SET_PURPLE:
		inputColor = PURPLE;
		break;
	case SET_BLACK:
		inputColor = BLACK;
		break;
	case SET_WHITE:
		inputColor = WHITE;
		break;
	case SET_ORANGE:
		inputColor = ORANGE;
		break;

	case SET_YELLOW:
		inputColor = YELLOW;
		break;
	default:
		isColor = false;
	}

	return isColor;
}

void ApplicationManager::changeDrawColor(color drawClr)
{
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
		{
			FigList[i]->ChngDrawClr(drawClr);
		}
	}
}

void ApplicationManager::changeFillColor(color FillClr)
{
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
		{
			FigList[i]->ChngFillClr(FillClr);
		}
	}
}

bool ApplicationManager::AnySelected()
{
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
		{
			return true;
		}
	}
	return false;
}

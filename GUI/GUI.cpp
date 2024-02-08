#include "GUI.h"
#include "ActionPlayBy.h"
#include<iostream>

//constructor make necessary initializations
GUI::GUI()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;

	UI.width = 1300;
	UI.height = 700;
	UI.wx = 5;
	UI.wy = 5;


	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 75;

	UI.DrawColor = BLUE;	//Drawing color
	UI.FillColor = GREEN;	//Filling color
	UI.MsgColor = BLUE;		//Messages color
	UI.BkGrndColor = LIGHTGOLDENRODYELLOW;	//Background color
	UI.HighlightColor = MAGENTA;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = SNOW;
	UI.PenWidth = 1;	//width of the figures frames

	MapStringtoColor["BLACK"] = BLACK;
	MapStringtoColor["WHITE"] = WHITE;
	MapStringtoColor["LIGHTBLUE"] = LIGHTBLUE;
	MapStringtoColor["GREEN"] = GREEN;
	MapStringtoColor["BLUE"] = BLUE;
	MapStringtoColor["YELLOW"] = YELLOW;
	MapStringtoColor["PINK"] = PINK;
	MapStringtoColor["ORANGE"] = ORANGE;
	MapStringtoColor["MAROON"] = MAROON;
	MapStringtoColor["PURPLE"] = PURPLE;
	MapStringtoColor["RED"] = RED;
	colors[0] = "BLACK";
	colors[1] = "WHITE";
	colors[2] = "LIGHTBLUE";
	colors[3] = "GREEN";
	colors[4] = "BLUE";
	colors[5] = "YELLOW";
	colors[6] = "PINK";
	colors[7] = "ORANGE";
	colors[8] = "MAROON";
	colors[9] = "PURPLE";
	colors[10] = "RED";


	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");

	CreateDrawToolBar();
	CreateColorBar();
	CreateStatusBar();
	
}


//======================================================================================//
//								Input Functions										    //
//======================================================================================//


void GUI::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string GUI::GetSrting() const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if(Key == 8 )	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label+= Key;
		PrintMessage(Label);
	}
}

//This function reads the position where the user clicks to determine the desired action
ActionType GUI::MapInputToActionType() const
{	
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_SQUR: return DRAW_SQUARE;
			case ITM_ELPS: return DRAW_ELPS;
			case ITM_HEX: return DRAW_HEX;
			case ITM_SIZE: return RESIZE;
			case ITM_MOVE: return MOVE;
			case ITM_DELE: return DEL;
			case ITM_BACK: return BACK;
			case ITM_FRONT: return FRONT;
			case ITM_SAVE: return SAVE;
			case ITM_LOAD: return LOAD;
			case ITM_FILL_COLOR: return CHNG_FILL_CLR;
			case ITM_BG_COLOR_CHANGE: return CHNG_BK_CLR;
			case ITM_CHNG_DRAW_COLOR: return CHNG_DRAW_CLR;
			case ITM_PLAYMODE: return TO_PLAY;
			case ITM_EXIT: return EXIT;	
			
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;	
		}
		
		//[3] User clicks on the status bar
		return STATUS;
	}
	else if (UI.InterfaceMode == MODE_SIZE) {
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_HALF: return HALF;
			case ITM_QUARTER: return QUARTER;
			case ITM_DOUBLE: return DOUBLE1;
			case ITM_QUADRUPLE: return QUADRUPLE;
			case ITM_GO_BACK: return GO_BACK;

			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
	}
	else if (UI.InterfaceMode == MODE_COLOR)
	{

		if (x >= 0 && x < UI.MenuItemWidth && y>UI.ToolBarHeight)
		{
			//Check whick Color was clicked
			//==> This assumes that Color images are lined up Vertically <==
			int ClickedItemOrder = (y / 50)-1;
			cout << ClickedItemOrder << "color mode" << endl;
			switch (ClickedItemOrder)
			{
			case ITM_RED: return SET_RED;
			case ITM_GREEN: return SET_GREEN;
			case ITM_BLUE: return SET_BLUE;
			case ITM_PINK: return SET_PINK;
			case ITM_MAROON: return SET_MAROON;
			case ITM_PURPLE: return SET_PURPLE;
			case ITM_BLACK: return SET_BLACK;
			case ITM_WHITE: return SET_WHITE;
			case ITM_ORANGE: return SET_ORANGE;
			case ITM_YELLOW: return SET_YELLOW;
			default: return EMPTY;
			}
		}
		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//GUI is in PLAY mode
	{
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			switch (ClickedItemOrder)
			{
			case PLAY_TYPE: return ACTION_PLAY_TYPE;
			case PLAY_FILL: return ACTION_PLAY_FILL;
			case PLAY_TYPEFILL: return ACTION_PLAY_TYPEFILL;
			case PLAY_RESET: return ACTION_PLAY_RESET;
			case PLAY_BACK: return ACTION_TO_DRAW;
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}
		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{

			switch (ActionPlayBy::type)
			{
			case ACTION_PLAY_TYPE: return ACTION_PLAY_TYPE;
			case ACTION_PLAY_FILL: return ACTION_PLAY_FILL;
			case ACTION_PLAY_TYPEFILL: return ACTION_PLAY_TYPEFILL;
			default: return EMPTY;
			}

		}
		//[3] User clicks on the status bar
		return STATUS;
	}	

}
//======================================================================================//
//								Output Functions										//
//======================================================================================//

window* GUI::CreateWind(int w, int h, int x, int y) const
{ 
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);	
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white Square
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateDrawToolBar() const
{
	UI.InterfaceMode = MODE_DRAW;

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way
	
	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_SQUR] = "images\\MenuItems\\Menu_Sqr.jpg";
	MenuItemImages[ITM_ELPS] = "images\\MenuItems\\Menu_Elps.jpg";
	MenuItemImages[ITM_HEX] = "images\\MenuItems\\hexa.jpg";
	MenuItemImages[ITM_BACK] = "images\\MenuItems\\Menu_SendToBack.jpg";
	MenuItemImages[ITM_FRONT] = "images\\MenuItems\\Menu_BringToFront.jpg";
	MenuItemImages[ITM_BG_COLOR_CHANGE] = "images\\MenuItems\\background.jpg";
	MenuItemImages[ITM_CHNG_DRAW_COLOR] = "images\\MenuItems\\draw.jpg";
	MenuItemImages[ITM_FILL_COLOR] = "images\\MenuItems\\brush.jpg";
	MenuItemImages[ITM_SAVE] = "images\\MenuItems\\save_icon.jpg";
	MenuItemImages[ITM_LOAD] = "images\\MenuItems\\load_icon.jpg";
	MenuItemImages[ITM_PLAYMODE] = "images\\MenuItems\\play.jpg";
	MenuItemImages[ITM_DELE] = "images\\MenuItems\\Menu_DELE.jpg";
	MenuItemImages[ITM_MOVE] = "images\\MenuItems\\move.jpg";
	MenuItemImages[ITM_SIZE] = "images\\MenuItems\\Resize.jpg";
	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\Menu_Exit.jpg";

	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	for(int i=0; i<DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth,0,UI.MenuItemWidth, UI.ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(BLUE, 1);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	

}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::CreatePlayToolBar() const
{
	UI.InterfaceMode = MODE_PLAY;
	///TODO: write code to create Play mode menu

	UI.InterfaceMode = MODE_PLAY;
	ClearToolBarArea();
	///TODO: write code to create Play mode menu
	string PlayMenuItem[PLAY_ITM_COUNT];
	PlayMenuItem[PLAY_TYPE] = "images\\MenuItems\\game1.jpg";
	PlayMenuItem[PLAY_FILL] = "images\\MenuItems\\game2.jpg";
	PlayMenuItem[PLAY_TYPEFILL] = "images\\MenuItems\\game3.jpg";
	PlayMenuItem[PLAY_RESET] = "images\\MenuItems\\reset1.jpg";
	PlayMenuItem[PLAY_BACK] = "images\\MenuItems\\back.jpg";
	
	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	for (int i = 0; i < PLAY_ITM_COUNT; i++)
		pWind->DrawImage(PlayMenuItem[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(DARKGREEN, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateColorBar() const
{
	pWind->SetPen(BLACK, 2);
	pWind->SetBrush(UI.ColorBarColor);
	pWind->DrawLine(UI.MenuItemWidth + 2, UI.ToolBarHeight, UI.MenuItemWidth + 2, UI.height - UI.StatusBarHeight);
	string MenuItemImages[COLOR_ITM_COUNT];
	MenuItemImages[ITM_RED] = "images\\MenuItems\\red.jpg";
	MenuItemImages[ITM_GREEN] = "images\\MenuItems\\green.jpg";
	MenuItemImages[ITM_BLUE] = "images\\MenuItems\\blue.jpg";
	MenuItemImages[ITM_PINK] = "images\\MenuItems\\pink.jpg";
	MenuItemImages[ITM_MAROON] = "images\\MenuItems\\color\\maroon.jpg";
	MenuItemImages[ITM_PURPLE] = "images\\MenuItems\\color\\purple.jpg";
	MenuItemImages[ITM_BLACK] = "images\\MenuItems\\color\\black.jpg";
	MenuItemImages[ITM_WHITE] = "images\\MenuItems\\color\\white2.jpg";
	MenuItemImages[ITM_ORANGE] = "images\\MenuItems\\color\\orange.jpg";
	MenuItemImages[ITM_YELLOW] = "images\\MenuItems\\color\\yellow2.jpg";
	//Drawing Color image

	//Draw color item one image at a time
	for (int i = 0; i < COLOR_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], 0, (i * 50) + (UI.ToolBarHeight + 7), UI.MenuItemWidth, 50);

}

//////////////////////////////////////////////////////////////////////////////////////////

void GUI::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);	
	
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::ClearToolBarArea() const
{
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
}

void GUI::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight/1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntDrawColor() const	//get current drwawing color
{	return UI.DrawColor;	}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntFillColor() const	//get current filling color
{	return UI.FillColor;	}
//////////////////////////////////////////////////////////////////////////////////////////
	
int GUI::getCrntPenWidth() const		//get current pen width
{	return UI.PenWidth;	}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void GUI::DrawSquare(Point P1, int length, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = RectGfxInfo.DrawClr;
	
	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width
	
	drawstyle style;
	if (RectGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else	
		style = FRAME;

	
	pWind->DrawRectangle(P1.x, P1.y, P1.x +length, P1.y+length, style);

}
void GUI::setCrntBKGrandColor(color c) {
	UI.BkGrndColor = c;
}
string GUI::MapColortoString(color clr) {
	for (int i = 0; i <11;i++) {
		if (this->ColorsEq(MapStringtoColor[colors[i]], clr)) {
			return colors[i];
		}
	}
}

bool GUI::ColorsEq(color c1, color c2) {
	return c1.ucBlue == c2.ucBlue && c1.ucGreen == c2.ucGreen && c1.ucRed == c2.ucRed;
}

void GUI::setCrntFillColor(color c) {
	UI.FillColor = c;
}

void GUI::setCrntDrawColor(color c) {
	UI.DrawColor = c;
}
void GUI::setIsFilled(bool isF) {
	UI.isFilled = isF;
}

void GUI::DrawEllipse(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawEllipse(P1.x, P1.y, P2.x, P2.y, style);


}

void GUI::DrawHexagon(Point P1, Point P2, GfxInfo HexGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = HexGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, HexGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (HexGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(HexGfxInfo.FillClr);
	}
	else
		style = FRAME;

	int lengthx = abs(P1.x - P2.x);
	int lengthy = abs(P1.y - P2.y);

	int arrx[6] = { P1.x,P1.x + lengthx, P1.x + 1.5 * lengthx,P1.x + lengthx,P1.x,P1.x - 0.5 * lengthx };
	int arry[6] = { P1.y,P1.y,P1.y + 0.5 * lengthy,P1.y + lengthy,P1.y + lengthy,P1.y + 0.5 * lengthy };

	pWind->DrawPolygon(arrx, arry, 6, style);

}
//======================================================================================//
//								Figures Resizing Functions								//
//======================================================================================//
void GUI::ClearToolBarArea() {
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight, FILLED, 5, 5);


}
void ::GUI::CreateResizeToolBar() {
	UI.InterfaceMode = MODE_SIZE;

	string MenuItemImages[SIZE_ITM_COUNT];
	MenuItemImages[ITM_HALF] = "images//MenuItems/1-2.jpg";
	MenuItemImages[ITM_QUARTER] = "images//MenuItems/1-4.jpg";
	MenuItemImages[ITM_DOUBLE] = "images//MenuItems/2x.jpg";
	MenuItemImages[ITM_QUADRUPLE] = "images//MenuItems/4x.jpg";
	MenuItemImages[ITM_GO_BACK] = "images//MenuItems/back.jpg";

	//draw menu items images one by one
	for (int i = 0; i < SIZE_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}

bool GUI::ExceedDrawingArea(int minX, int minY, int maxX, int maxY)
{
	int DrawAreaHeight = UI.height - UI.StatusBarHeight - UI.ToolBarHeight;
	if (maxX > (UI.wx + UI.width) || (minX < UI.wx) || maxY > (UI.wy + UI.ToolBarHeight + DrawAreaHeight) || minY < (UI.wy + UI.ToolBarHeight))
	{
		return true;
	}
	return false;
}
//======================================================================================//
//								Figures moving Functions								//
//======================================================================================//

buttonstate GUI::getLeftMouseStatus(int& x, int& y) {
	return pWind->GetButtonState(LEFT_BUTTON, x, y);
}
bool GUI::isLeftButtonPressed(int&x, int&y) {
	return pWind->GetButtonState(LEFT_BUTTON, x, y) == BUTTON_DOWN;
}
void GUI::waitMouseClick() {
	int x, y;
	pWind->WaitMouseClick(x, y);
}

//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
}


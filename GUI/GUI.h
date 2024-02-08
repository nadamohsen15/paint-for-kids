#ifndef GUI_H
#define GUI_H

#include "..\DEFS.h"
#include "UI_Info.h" 
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include <map>


//This class is responsible for Grphical User Interface handling
//All user input and program outputs MUST be done through this class
//No other class is allowed to perform direct i/o
class GUI	
{
public:	
	window* pWind;	//Pointer to the Graphics Window
	std::map<string, color> MapStringtoColor;
	string colors[11];
public:
	GUI();	
	~GUI();	
	window* CreateWind(int, int, int , int) const; //creates the application window

	/////////// Input Functoinality  /////////////////
	void GetPointClicked(int &x, int &y) const;//Get coordinate where user clicks
	string GetSrting() const ;	 //Returns a string entered by the user
	ActionType MapInputToActionType() const; //Read the user click and map to an action


	/////////// Output Functoinality  ////////////////
	void CreateDrawToolBar() const;	//creates Draw mode toolbar & menu
	void CreatePlayToolBar() const;	//creates Play mode toolbar & menu
	void CreateStatusBar() const;	//create the status bar

	void ClearStatusBar() const;	//Clears the status bar
	void ClearDrawArea() const;	//Clears the drawing area
	void ClearToolBarArea() const;
	
	// -- Figures Drawing functions
	void DrawSquare(Point P1, int length, GfxInfo RectGfxInfo, bool selected=false) const;  //Draw a Square
	void DrawEllipse(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const;
	void DrawHexagon(Point P1, Point P2, GfxInfo HexGfxInfo, bool selected) const;
	bool GUI::ExceedDrawingArea(int minX, int minY, int maxX, int maxY);
	///TODO: Make similar functions for drawing all other figures.
	
	void PrintMessage(string msg) const;	//Print a message on Status bar

	color getCrntDrawColor() const;	//get current drwawing color
	color getCrntFillColor() const;	//get current filling color
	int getCrntPenWidth() const;		//get current pen width
	void setCrntBKGrandColor(color c);
	string MapColortoString(color clr);
	bool GUI::ColorsEq(color c1, color c2);

	void setCrntFillColor(color c);
	void setCrntDrawColor(color c);
	void setIsFilled(bool isF);

	void ClearToolBarArea();		//Clear tool Bar to draw another one
	void CreateResizeToolBar();		//Draw new Tool Bar for Resize
	buttonstate getLeftMouseStatus(int& x, int& y);		//Get Left Mouse Button Status
	bool isLeftButtonPressed(int& x, int& y);
	void waitMouseClick();					//Wait for Mouse Click
	void CreateColorBar() const;			//Color Bar Creation






};


#endif
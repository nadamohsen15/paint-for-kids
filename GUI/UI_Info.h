#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

enum GUI_MODE	//Graphical user interface mode
{
	MODE_DRAW,	//Drawing mode (startup mode)
	MODE_PLAY,	//Playing mode
	MODE_SIZE,   //Resize mode
	MODE_COLOR	//Color Mode
};

enum DrawMenuItem //The items of the Draw menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	ITM_SQUR,		//Square item in menu
	ITM_ELPS,		//Ellipse item in menu
	ITM_HEX,		//Hex item in menu
	ITM_SIZE,		//Resize item in menu	
	ITM_MOVE,		//Move item in menu	
	ITM_DELE,       //Delete Icon
	ITM_BACK,		//Send to back
	ITM_FRONT,		//bring to front
	ITM_BG_COLOR_CHANGE,		// BG Color item in menu
	ITM_CHNG_DRAW_COLOR,		// DR Color item in menu
	ITM_FILL_COLOR,
	ITM_SAVE,
	ITM_LOAD,
	ITM_PLAYMODE,
	ITM_EXIT,		//Exit item
	
	DRAW_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum
	
};
enum ColorMenuItem //The items of the Color menu (you should add more items)
{
	ITM_RED,     //Red color item in menu
	ITM_GREEN,		//Green color item in menu
	ITM_BLUE,		//Blue color item in menu
	ITM_PINK,		//Pink color item in menu
	ITM_MAROON,		//Maroon color item in menu
	ITM_PURPLE,		//Purple color item in menu
	ITM_BLACK,		//Black color item in menu
	ITM_WHITE,		//Gray color item in menu
	ITM_ORANGE,		//NAVY color item in menu
	ITM_YELLOW,		//Yellow color item in menu
	COLOR_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum

};

enum PlayMenuItem //The items of the Play menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here

	//TODO: Add more items names here
	PLAY_TYPE,
	PLAY_FILL,
	PLAY_TYPEFILL,
	PLAY_RESET,
	PLAY_BACK,
	PLAY_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum

};


enum SizeMenuItem
{
	ITM_QUARTER,
	ITM_HALF,
	ITM_DOUBLE,
	ITM_QUADRUPLE,
	ITM_GO_BACK,
	
	SIZE_ITM_COUNT
};



__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	GUI_MODE InterfaceMode;
	
	int	width, height,	//Window width and height
		wx , wy,			//Window starting coordinates
		StatusBarHeight,	//Status Bar Height
		ToolBarHeight,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		MenuItemWidth;		//Width of each item in toolbar menu
	

	bool isFilled;
	color DrawColor;		//Drawing color
	color FillColor;		//Filling color
	color HighlightColor;	//Highlighting color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Background color
	color StatusBarColor;	//Status bar color
	color ColorBarColor;
	int PenWidth;			//width of the pen that draws shapes

	/// Add more members if needed
	
}UI;	//create a global object UI

#endif
#include "CFigure.h"

CFigure::CFigure()
{
	//	PlayHidden = false;
	ID = newID++;
	Selected = false;
	visible = true;
}

CFigure::CFigure(GfxInfo FigureGfxInfo)
{ 
	ID = newID++;
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	visible = true;
}

void CFigure::SetSelected(bool s)
{	Selected = s; }

bool CFigure::IsSelected() const
{	return Selected; }

void CFigure::setVisibility(bool h) {
	visible = h;
}

bool CFigure::isVisible()
{
	return visible;
}

color CFigure::getColor()
{
	return  color(FigGfxInfo.FillClr);
}

void CFigure::ChngDrawClr(color Dclr)
{	FigGfxInfo.DrawClr = Dclr; }

void CFigure::ChngFillClr(color Fclr)
{	
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr; 
}


color CFigure::StringToColor(string s) {
	if (s == "GREEN")
		return GREEN;
	if (s == "BLUE")
		return BLUE;
	if (s == "WHITE")
		return WHITE;
	if (s == "PINK")
		return PINK;
	if (s == "YELLOW")
		return YELLOW;
	if (s == "ORANGE")
		return ORANGE;
	if (s == "MAROON")
		return MAROON;
	if (s == "PURPLE")
		return PURPLE;
	return BLACK;
}

string CFigure::ColorToString(color c)
{
	if ((c.ucBlue == BLACK.ucBlue) && (c.ucGreen == BLACK.ucGreen) && (c.ucRed == BLACK.ucRed))
		return "BLACK";
	if ((c.ucBlue == PINK.ucBlue) && (c.ucGreen == PINK.ucGreen) && (c.ucRed == PINK.ucRed))
		return "PINK";
	if ((c.ucBlue == LIGHTBLUE.ucBlue) && (c.ucGreen == LIGHTBLUE.ucGreen) && (c.ucRed == LIGHTBLUE.ucRed))
		return "LIGHTBLUE";
	if ((c.ucBlue == MAROON.ucBlue) && (c.ucGreen == MAROON.ucGreen) && (c.ucRed == MAROON.ucRed))
		return "MAROON";
	if ((c.ucBlue == ORANGE.ucBlue) && (c.ucGreen == ORANGE.ucGreen) && (c.ucRed == ORANGE.ucRed))
		return "ORANGE";
	if ((c.ucBlue == BLUE.ucBlue) && (c.ucGreen == BLUE.ucGreen) && (c.ucRed == BLUE.ucRed))
		return "BLUE";
	if ((c.ucBlue == WHITE.ucBlue) && (c.ucGreen == WHITE.ucGreen) && (c.ucRed == WHITE.ucRed))
		return "WHITE";
	if ((c.ucBlue == YELLOW.ucBlue) && (c.ucGreen == YELLOW.ucGreen) && (c.ucRed == YELLOW.ucRed))
		return "YELLOW";
	if ((c.ucBlue == GREEN.ucBlue) && (c.ucGreen == GREEN.ucGreen) && (c.ucRed == GREEN.ucRed))
		return "GREEN";
	return "NO-FILL";

}

void CFigure::SetID(int _id) {
	ID = _id;
}
int CFigure::GetID() const
{
	return ID;
}



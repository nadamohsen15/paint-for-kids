#include "CHexagon.h"
#include <iostream>
#include <fstream>


#include "..\ApplicationManager.h"
#include "CSquare.h"

CHexagon::CHexagon() {} //default constructor, We need it to Load


CHexagon::CHexagon(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	TopLeftCorner = P1;
	BottomRightCorner = P2;
	VerticalLen = abs(P1.y - P2.y);
	HorizentalLen = abs(P1.x - P2.x);

}
//CHexagon::CHexagon() {};
void CHexagon::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Square on the screen	
	pGUI->DrawHexagon(TopLeftCorner, BottomRightCorner, FigGfxInfo, Selected);
}
void CHexagon::Resize(GUI* pGUI, float factor) {
	pGUI->ClearStatusBar();
	float oldHorizentalLen = HorizentalLen;
	float oldVerticalLen = VerticalLen;
	if (TopLeftCorner.x - HorizentalLen * factor <= 0 || BottomRightCorner.x + HorizentalLen * factor >= UI.width) {
		pGUI->PrintMessage("Can't resize, it will be out of borders");
		return;
	}
	else if (HorizentalLen * factor < 5 || VerticalLen * factor < 5) {
		pGUI->PrintMessage("Can't resize, it will be too small");
		return;
	}
	else {
		HorizentalLen = HorizentalLen * factor;
		VerticalLen = VerticalLen * factor;
	}
	BottomRightCorner.x = BottomRightCorner.x + (HorizentalLen - oldHorizentalLen);
	BottomRightCorner.y = BottomRightCorner.y + (VerticalLen - oldVerticalLen);
}
bool CHexagon::insideFigure(int x, int y)
{
	int lengthx = abs(TopLeftCorner.x - BottomRightCorner.x);
	int lengthy = abs(TopLeftCorner.y - BottomRightCorner.y);

	int xCenter = (BottomRightCorner.x + TopLeftCorner.x) / 2;
	int yCenter = (BottomRightCorner.y + TopLeftCorner.y) / 2;

	int arrx[6] = { TopLeftCorner.x,TopLeftCorner.x + lengthx, TopLeftCorner.x + 1.5 * lengthx,TopLeftCorner.x + lengthx,TopLeftCorner.x,TopLeftCorner.x - 0.5 * lengthx };
	int arry[6] = { TopLeftCorner.y,TopLeftCorner.y,TopLeftCorner.y + 0.5 * lengthy,TopLeftCorner.y + lengthy,TopLeftCorner.y + lengthy,TopLeftCorner.y + 0.5 * lengthy };

	float areax1 = (0.5) * abs(x * (arry[0] - arry[1]) + arrx[0] * (arry[1] - y) + arrx[1] * (y - arry[0]));
	float areax2 = (0.5) * abs(x * (arry[1] - arry[2]) + arrx[1] * (arry[2] - y) + arrx[2] * (y - arry[1]));
	float areax3 = (0.5) * abs(x * (arry[2] - arry[3]) + arrx[2] * (arry[3] - y) + arrx[3] * (y - arry[2]));
	float areax4 = (0.5) * abs(x * (arry[3] - arry[4]) + arrx[3] * (arry[4] - y) + arrx[4] * (y - arry[3]));
	float areax5 = (0.5) * abs(x * (arry[4] - arry[5]) + arrx[4] * (arry[5] - y) + arrx[5] * (y - arry[4]));
	float areax6 = (0.5) * abs(x * (arry[5] - arry[0]) + arrx[5] * (arry[0] - y) + arrx[0] * (y - arry[5]));
	float areax = areax1 + areax2 + areax3 + areax4 + areax5 + areax6;

	float totalarea = lengthy * lengthx * 1.5;
	Area = totalarea;
	if (areax == totalarea)
		return true;
	else
		return false;
};
string CHexagon::getShapeType() {
	return "Hexagon";
}



void CHexagon::Save(ofstream& File)
{
	
	File << "Hexagon\t"
		<< this->GetID() << "\t"
		<< TopLeftCorner.x << "\t"
		<< TopLeftCorner.y << "\t"
		<< BottomRightCorner.x << "\t"
		<< BottomRightCorner.y << "\t"
		<< ColorToString(FigGfxInfo.DrawClr) << "\t";
	if (this->FigGfxInfo.isFilled)
		File << this->ColorToString(this->FigGfxInfo.FillClr) << "\n";
	else
		File << "No-Fill-color\n";
}

void CHexagon::Load(ifstream& file)
{
	string temp;
	file >> this->ID >>
		this->TopLeftCorner.x >>
		this->TopLeftCorner.y >>
		this->BottomRightCorner.x >>
		this->BottomRightCorner.y;
	file >> temp;
	this->FigGfxInfo.DrawClr = StringToColor(temp);
	file >> temp;
	if (temp == "No-Fill-color") {
		this->FigGfxInfo.isFilled = false;
	}
	else
	{
		this->FigGfxInfo.FillClr = StringToColor(temp);
		this->FigGfxInfo.isFilled = true;
		cout << "fail";
	}
	this->Selected = false;
	this->FigGfxInfo.BorderWdth = 3;
}

void CHexagon::getCenter(int& x, int& y)
{
	x = (TopLeftCorner.x + BottomRightCorner.x) / 2;
	y = (TopLeftCorner.y + BottomRightCorner.y) / 2;
}

void CHexagon::Move(int x, int y, GUI* pGUI)
{
	pGUI->ClearStatusBar();
	if (TopLeftCorner.x + x - (VerticalLen) <= 0 || TopLeftCorner.x + x + (HorizentalLen - VerticalLen / 4) >= UI.width || TopLeftCorner.y + y + VerticalLen > (UI.height - UI.StatusBarHeight) || TopLeftCorner.y + y <= UI.ToolBarHeight) {
		pGUI->PrintMessage("Can't move, it will be out of borders");
		return;
	}
	else {
		TopLeftCorner.x += x;
		TopLeftCorner.y += y;
		BottomRightCorner.x += x;
		BottomRightCorner.y += y;
	}
}

void CHexagon::printFigInfo(GUI* pGUI)
{
	pGUI->PrintMessage("Hexagon with ID: " + std::to_string(ID) +
		" TopLeftPoint: (" + std::to_string(TopLeftCorner.x) + ", " + std::to_string(TopLeftCorner.y) + " )" +
		" BottomRightCorner: (" + std::to_string(BottomRightCorner.x) + ", " + std::to_string(BottomRightCorner.y) + " )");
}

#include <iostream>
#include <windows.h>
#include "Door.h"

Door::Door(int x, int y, char drawSymbol, ActorColor color, ActorColor closedColor)
	: PlacableActor(x, y, m_drawSymbol, color)
	, m_isOpen(false)
	, m_closedColor(closedColor)
{

}

void Door::Draw()
{
	ClearPreviousPositionDraw();

	PrepareDraw();

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (m_isOpen)
	{
		SetConsoleTextAttribute(console, (int)m_color);
	}
	else
	{
		SetConsoleTextAttribute(console, (int)m_closedColor);
	}

	std::cout << m_drawSymbol;
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}
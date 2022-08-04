#include "PlacableActor.h"
#include <Windows.h>
#include <iostream>

PlacableActor::PlacableActor(int x, int y, char drawSymbol, ActorColor color)
	: m_pPosition(new Point(x, y))
	, m_pPreviousPosition(new Point(m_pPosition->x, m_pPosition->y))
	, m_IsActive(true)
	, m_PreviousIsActive(true)
	, m_color(color)
	, m_drawSymbol(drawSymbol)
{

}

PlacableActor::~PlacableActor()
{
	delete m_pPosition;
	m_pPosition = nullptr;

	delete m_pPreviousPosition;
	m_pPreviousPosition = nullptr;
}

int PlacableActor::GetXPosition()
{
	return m_pPosition->x;
}

int PlacableActor::GetYPosition()
{
	return m_pPosition->y;
}

int* PlacableActor::GetXPositionPointer()
{
	return &(m_pPosition->x);
}

int* PlacableActor::GetYPositionPointer()
{
	return &(m_pPosition->y);
}

void PlacableActor::SetPosition(int x, int y)
{
	if (m_pPosition->x != x || m_pPosition->y != y)
	{
		m_pPreviousPosition->x = m_pPosition->x;
		m_pPreviousPosition->y = m_pPosition->y;

		m_pPosition->x = x;
		m_pPosition->y = y;
	}
}

bool PlacableActor::HasChanged()
{
	return m_pPosition->x != m_pPreviousPosition->x || m_pPosition->y != m_pPreviousPosition->y;
}

void PlacableActor::Place(int x, int y)
{
	m_pPosition->x = x;
	m_pPosition->y = y;
	SetIsActive(true);
}

void PlacableActor::SetIsActive(bool newValue)
{
	m_PreviousIsActive = m_IsActive;

	m_IsActive = newValue;
}

void PlacableActor::ClearPreviousPositionDraw()
{
	// overwrite previous position
	COORD previousPosition;
	previousPosition.X = m_pPreviousPosition->x;
	previousPosition.Y = m_pPreviousPosition->y;

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(console, previousPosition);

	std::cout << ' ';
}

void PlacableActor::PrepareDraw()
{
	COORD currentPosition;
	currentPosition.X = m_pPosition->x;
	currentPosition.Y = m_pPosition->y;

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(console, (int)m_color);

	SetConsoleCursorPosition(console, currentPosition);
}

void PlacableActor::Draw()
{
	if (!HasChanged() && m_bDrawn) return;

	m_bDrawn = true;

	ClearPreviousPositionDraw();

	PrepareDraw();

	std::cout << m_drawSymbol;

	// reset color for next draw
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}
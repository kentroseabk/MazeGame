#pragma once
#include "Point.h"

enum class ActorColor
{
	Regular = 7,
	Blue = 9,
	Green = 10,
	Red = 12,
	Yellow = 14,
	SolidGreen = 34,
	SolidRed = 68,
	SolidBlue = 153
};

enum class ActorType
{
	Door,
	Enemy,
	Goal,
	Key,
	Money,
	Player,
	Trap
};

class PlacableActor
{
public:
	PlacableActor(int x, int y, char drawSymbol, ActorColor color = ActorColor::Regular);
	virtual ~PlacableActor();

	int GetXPosition();
	int GetYPosition();
	int* GetXPositionPointer();
	int* GetYPositionPointer();
	void SetPosition(int x, int y);
	bool HasChanged();

	ActorColor GetColor() { return m_color; }

	void Remove() { m_IsActive = false; }
	void SetIsActive(bool newValue);
	bool IsActive() { return m_IsActive; }
	void Place(int x, int y);

	virtual ActorType GetType() = 0;
	virtual void Draw();
	virtual void Update()
	{

	}

protected:
	void ClearPreviousPositionDraw();
	void PrepareDraw();
	Point* m_pPosition;
	Point* m_pPreviousPosition;

	bool m_IsActive;
	bool m_PreviousIsActive;
	ActorColor m_color;

	char m_drawSymbol = ' ';
	bool m_bDrawn = false;
};
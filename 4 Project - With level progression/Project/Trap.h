#pragma once
#include "PlacableActor.h"
class Trap : public PlacableActor
{
public:
	Trap(int x, int y, char drawSymbol, ActorColor color)
		: PlacableActor(x, y, drawSymbol, color)
	{

	}

	virtual ActorType GetType() override { return ActorType::Trap; }
	//virtual void Draw() override;
};


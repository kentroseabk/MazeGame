#pragma once
#include "PlacableActor.h"
class Key : public PlacableActor
{
public:
	Key(int x, int y, char drawSymbol, ActorColor color)
		: PlacableActor(x, y, drawSymbol, color)
	{

	}

	virtual ActorType GetType() override { return ActorType::Key; }
	//virtual void Draw() override;
};


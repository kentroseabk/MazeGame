#pragma once
#include "PlacableActor.h"
class Goal : public PlacableActor
{
public:
	Goal(int x, int y, char drawSymbol);

	virtual ActorType GetType() override { return ActorType::Goal; }
	//virtual void Draw() override;
};


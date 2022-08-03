#pragma once
#include "GameState.h"

#include <set>

class StateMachineExampleGame;

class HighScoreState : public GameState
{
	StateMachineExampleGame* m_pOwner;
	std::set<int> m_HighScores;

public:
	HighScoreState(StateMachineExampleGame* pOwner);
	~HighScoreState() = default;

	void ProcessInput() override;
	virtual void Draw() override;
};


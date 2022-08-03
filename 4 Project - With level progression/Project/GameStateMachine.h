#pragma once

class GameState;

class GameStateMachine
{
public:
	virtual ~GameStateMachine() = default;

	virtual bool Init() = 0;
	virtual void UpdateCurrentState() = 0;
	virtual void DrawCurrentState() = 0;
	virtual void ProcessInput() = 0;
	virtual void ChangeState(GameState* pNewState) = 0;
	virtual bool Cleanup() = 0;

	bool m_gameOver = false;
};


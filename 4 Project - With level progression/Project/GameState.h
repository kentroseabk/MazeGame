#pragma once

class GameState
{
public:
	virtual ~GameState() {}

	virtual void Enter() {}
	virtual void Update() {}
	virtual void ProcessInput() { }
	virtual void Draw() = 0;
	virtual void Exit() {}

protected:
	bool m_bDrawn = false;
};
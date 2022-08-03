#pragma once
#include "GameStateMachine.h"
#include "Player.h"
#include "Level.h"

class Game
{
	GameStateMachine* m_pStateMachine;
public:
	Game();
	void Initialize(GameStateMachine* pStateMachine);
	void RunGameLoop();
	void Deinitialize();

private:
	void Update();
	void ProcessInput();
	void Draw();
	uint32_t GetTime();

	const float m_FPS = 250;
	const float m_FRAME_TIME_MS = 1000 / m_FPS;
	uint32_t m_timeOfLastFrame = 0;
};
#pragma once
#include "GameStateMachine.h"
#include "Player.h"
#include "Level.h"
#include <thread>

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

	const float m_FPS = 60;
	const float m_FRAME_TIME_MS = 1000 / m_FPS;
	uint32_t m_timeOfLastFrame = 0;

	const float m_UPDATES_PER_SECOND = 1;
	const float m_UPDATE_TIME_MS = 1000 / m_UPDATES_PER_SECOND;
	uint32_t m_timeOfLastUpdate = 0;

	std::thread m_updateThread;
	std::thread m_renderThread;
};
#include "Game.h"
#include <chrono>
#include <thread>
#include <Windows.h>

Game::Game()
	: m_pStateMachine(nullptr)
{

}

void Game::Initialize(GameStateMachine* pStateMachine)
{
	if (pStateMachine != nullptr)
	{
		pStateMachine->Init();
		m_pStateMachine = pStateMachine;
	}

	m_updateAndRenderThread = std::thread(&Game::UpdateAndRender, this);
}

void Game::UpdateAndRender()
{
	while (!m_pStateMachine->m_gameOver)
	{
		Update();
		Draw();
	}
}

void Game::RunGameLoop()
{
	while (!m_pStateMachine->m_gameOver)
	{
		uint32_t now = GetTime();

		if (now > m_timeOfLastInput + m_INPUT_TIME_MS)
		{
			ProcessInput();
			m_timeOfLastInput = now;
		}
	}

	Draw();
}

void Game::Deinitialize()
{
	if (m_pStateMachine != nullptr)
		m_pStateMachine->Cleanup();

	m_updateAndRenderThread.join();
}

void Game::Update()
{
	uint32_t now = GetTime();

	if (now > m_timeOfLastUpdate + m_UPDATE_TIME_MS)
	{
		m_pStateMachine->UpdateCurrentState();
		m_timeOfLastUpdate = now;
	}
}

void Game::Draw()
{
	uint32_t now = GetTime();

	if (now > m_timeOfLastFrame + m_FRAME_TIME_MS)
	{
		m_pStateMachine->DrawCurrentState();
		m_timeOfLastFrame = now;
	}
}

void Game::ProcessInput()
{
	m_pStateMachine->ProcessInput();
}

uint32_t Game::GetTime()
{
	using namespace std::chrono;
	return static_cast<uint32_t>(duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count());
}

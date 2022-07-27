#pragma once
#include <windows.h>

class AudioManager
{
	static AudioManager* s_pInstance;

	bool m_SoundOn;

	AudioManager()
		: m_SoundOn(true)
	{

	}

public:
	static AudioManager* GetInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new AudioManager();
		}
		return s_pInstance;
	}

	static void DestroyInstance()
	{
		delete s_pInstance;
		s_pInstance = nullptr;
	}

	void ToggleSound()
	{
		m_SoundOn = !m_SoundOn;
	}

	bool IsSoundOn()
	{
		return m_SoundOn;
	}

	void PlayDoorClosedSound()
	{
		if (!m_SoundOn)
			return;
		Beep(500, 75);
		Beep(500, 75);
	}

	void PlayDoorOpenSound()
	{
		if (!m_SoundOn)
			return;
		Beep(1397, 200);
	}

	void PlayKeyPickupSound()
	{
		if (!m_SoundOn)
			return;
		Beep(1568, 50);
		Beep(1568, 200);
	}

	void PlayKeyDropSound()
	{
		if (!m_SoundOn)
			return;
		Beep(1568, 200);
		Beep(1568, 50);
	}

	void PlayTrapPickupSound()
	{
		if (!m_SoundOn)
			return;
		Beep(1000, 50);
		Beep(1600, 200);
	}

	void PlayTrapDropSound()
	{
		if (!m_SoundOn)
			return;
		Beep(1200, 200);
		Beep(1500, 50);
	}

	void PlayMoneySound()
	{
		if (!m_SoundOn)
			return;
		Beep(1568, 50);
	}

	void PlayLoseLivesSound()
	{
		if (!m_SoundOn)
			return;
		Beep(200, 100);
	}

	void PlayEnemyDieSound()
	{
		if (!m_SoundOn)
			return;
		Beep(400, 100);
	}

	void PlayLoseSound()
	{
		if (!m_SoundOn)
			return;
		Beep(500, 75);
		Beep(500, 75);
		Beep(500, 75);
		Beep(500, 75);
	}

	void PlayWinSound()
	{
		if (!m_SoundOn)
			return;
		Beep(1568, 200);
		Beep(1568, 200);
		Beep(1568, 200);
		Beep(1245, 1000);
		Beep(1397, 200);
		Beep(1397, 200);
		Beep(1397, 200);
		Beep(1175, 1000);
	}
};

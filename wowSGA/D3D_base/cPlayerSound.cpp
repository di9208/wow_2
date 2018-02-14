#include "stdafx.h"
#include "cPlayerSound.h"


cPlayerSound::cPlayerSound()
	:attack(false)
	, attack_time(0.0f)
	, swing(false)
{
}


cPlayerSound::~cPlayerSound()
{
}

void cPlayerSound::Setup()
{
	g_pSoundManager->Setup();
	g_pSoundManager->addSound("attack", "player/Sound/attack.mp3", false, false);
	g_pSoundManager->addSound("SWING", "player/Sound/SWING.wav", false, false);
}

void cPlayerSound::Update(condition * pCondition)
{
	if (*pCondition == ATTACK)
	{
		if (!attack)
		{
			attack_time = g_pTimeManager->GetLastUpdateTime();
			attack = true;
		}
		if (attack)
		{
			if (!swing)
			{
				if (attack_time + 0.6f < g_pTimeManager->GetLastUpdateTime())
				{
					g_pSoundManager->play("attack", 0.7f);
					g_pSoundManager->play("SWING", 1.0f);
					swing = true;
				}
			}
		}
	}
	else
	{
		attack = false;
		swing = false;
	}

}

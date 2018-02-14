#include "stdafx.h"
#include "cPlayerSound.h"


cPlayerSound::cPlayerSound()
	:attack(false)
	, attack_time(0.0f)
	, swing(false)
	, attack2(false)
	, attack_time2(0.0f)
	, swing2(false)
	, attack3(false)
	, attack_time3(0.0f)
	, swing3(false)
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

	if (*pCondition == SKILL_2)
	{
		if (!attack2)
		{
			attack_time2 = g_pTimeManager->GetLastUpdateTime();
			attack2 = true;
		}
		if (attack2)
		{
			if (!swing2)
			{
				if (attack_time2 + 0.6f < g_pTimeManager->GetLastUpdateTime())
				{
					g_pSoundManager->play("attack", 0.7f);
					g_pSoundManager->play("SWING", 1.0f);
					swing2 = true;
				}
			}
		}
	}
	else
	{
		attack2 = false;
		swing2 = false;
	}

	if (*pCondition == SKILL_3)
	{
		if (!attack3)
		{
			attack_time3 = g_pTimeManager->GetLastUpdateTime();
			attack3 = true;
		}
		if (attack3)
		{
			if (!swing3)
			{
				if (attack_time3 + 0.6f < g_pTimeManager->GetLastUpdateTime())
				{
					g_pSoundManager->play("attack", 0.7f);
					g_pSoundManager->play("SWING", 1.0f);
					swing3= true;
				}
			}
		}
	}
	else
	{
		attack3 = false;
		swing3 = false;
	}

}

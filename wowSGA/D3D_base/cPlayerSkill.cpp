#include "stdafx.h"
#include "cPlayerSkill.h"


cPlayerSkill::cPlayerSkill()
{
}


cPlayerSkill::~cPlayerSkill()
{
}

void cPlayerSkill::Setup()
{
}

void cPlayerSkill::Update(condition * pCondition, bool animCheck)
{
	if (g_pKeyManager->isOnceKeyDown('1'))
	{
		*pCondition = ATTACK;
	}
	if (g_pKeyManager->isOnceKeyDown('2'))
	{
		*pCondition = BREATH;
	}
	if (g_pKeyManager->isOnceKeyDown('3'))
	{
		*pCondition = BUFF;
	}
	if (g_pKeyManager->isOnceKeyDown('4'))
	{
		*pCondition = DEATH;
	}
	if (g_pKeyManager->isOnceKeyDown('5'))
	{
		*pCondition = SKILL_1;
	}
	if (g_pKeyManager->isOnceKeyDown('6'))
	{
		*pCondition = SKILL_2;
	}
	if (g_pKeyManager->isOnceKeyDown('7'))
	{
		*pCondition = SKILL_3;
	}
	combo(pCondition,animCheck);
}

void cPlayerSkill::combo(condition* pCondition, bool animCheck)
{
	if (*pCondition == SKILL_2 || *pCondition == SKILL_1)
	{
		if (animCheck)
		{
			*pCondition = SKILL_3;
		}
	}
}


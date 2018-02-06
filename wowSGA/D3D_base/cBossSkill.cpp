#include "stdafx.h"
#include "cBossSkill.h"


cBossSkill::cBossSkill()
{
}

cBossSkill::~cBossSkill()
{ 
}

void cBossSkill::Setup()
{
}

void cBossSkill::Update(E_BOSS_STATE * pState, E_BOSS_RAG_STATE* pStateRag)
{
	if (g_pKeyManager->isOnceKeyDown('T'))
	{
		*pState = E_BOSS_SPELL1;
	}
	if (g_pKeyManager->isOnceKeyDown('E'))
	{
		*pState = E_BOSS_SPELL2;
	}
	if (g_pKeyManager->isOnceKeyDown('R'))
	{
		*pState = E_BOSS_ATT;
	}
	if (g_pKeyManager->isOnceKeyDown('Y'))
	{
		*pState = E_BOSS_WHIRLWIND;
	}
	if (g_pKeyManager->isOnceKeyDown('U'))
	{
		*pState = E_BOSS_ATT2;
	}
	if (g_pKeyManager->isOnceKeyDown('O'))
	{
		*pState = E_BOSS_DEATH;
	}
	if (g_pKeyManager->isOnceKeyDown('P'))
	{
		*pState = E_BOSS_START;
	}

	/*if (g_pKeyManager->isOnceKeyDown(VK_F11))
	{
		*pStateRag = E_BOSS_RAG_STAND;
	}*/
	if (g_pKeyManager->isOnceKeyDown(VK_F9))
	{
		*pStateRag = E_BOSS_RAG_SPELL;
	}
	if (g_pKeyManager->isOnceKeyDown(VK_F8))
	{
		*pStateRag = E_BOSS_RAG_DEATH;
	}
	if (g_pKeyManager->isOnceKeyDown(VK_F7))
	{
		*pStateRag = E_BOSS_RAG_MERGE;
	}
	if (g_pKeyManager->isOnceKeyDown(VK_F6))
	{
		*pStateRag = E_BOSS_RAG_START;
	}
}

void cBossSkill::Render()
{
}

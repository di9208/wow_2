#pragma once
#include "cUnit.h"
class cBossSkill
{
public:
	cBossSkill();
	~cBossSkill();

	void Setup();
	void Update(E_BOSS_STATE* pState, E_BOSS_RAG_STATE* pStateRag);
	void Render();

};


#pragma once
#include "cUnit.h"
class cSkinnedMesh;

class cBossRagController
{
	cSkinnedMesh*			m_pSkinnedMesh_rag;

	E_BOSS_RAG_STATE		cBoss_rag_state;

private:
	SYNTHESIZE(float, m_fBossRotY, fBossRotY);
	SYNTHESIZE(D3DXVECTOR3, m_vBossPos, vBossPos);
	SYNTHESIZE(D3DXVECTOR3, m_vBossDir, BossDir);
	SYNTHESIZE_REF(D3DXMATRIXA16, m_world, World);
	D3DXVECTOR3	m_vBossDirX;

public:

	cBossRagController();
	~cBossRagController();

	void SetUp();
	void Update(E_BOSS_RAG_STATE* pStateRag);
	void Render(D3DXMATRIXA16* m_world);

	void SetAnimation(E_BOSS_RAG_STATE* pStateRag);
};


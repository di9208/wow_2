#pragma once
#include "cUnit.h"
class cSkinnedMesh;
class cOBB;
class cParticle;

class cBossRagController
{
	cSkinnedMesh*			m_pSkinnedMesh_rag;
	cSkinnedMesh*			m_pSkinnedMesh_rag_skill1;
	cSkinnedMesh*			m_pSkinnedMesh_rag_skill2;

	E_BOSS_RAG_STATE		cBoss_rag_state;
	SYNTHESIZE(cOBB*, m_pBossRagOBB, RagOBB);

private:
	SYNTHESIZE(float, m_fBossRotY, fBossRotY);
	SYNTHESIZE(D3DXVECTOR3, m_vBossPos, vBossPos);
	SYNTHESIZE(D3DXVECTOR3, m_vBossDir, BossDir);
	SYNTHESIZE_REF(D3DXMATRIXA16, m_world, World);
	D3DXVECTOR3	m_vBossDirX;

	D3DXMATRIXA16 m_obbw;
public:

	cBossRagController();
	~cBossRagController();

	void SetUp(std::vector<tagMon> Monster);
	void Update(E_BOSS_RAG_STATE* pStateRag);
	void Render(D3DXMATRIXA16  &m_world);

	void SetAnimation(E_BOSS_RAG_STATE* pStateRag);

	void skillRender();
	void skillRender2();

	cOBB* getOBB() { return m_pBossRagOBB; }
	D3DXVECTOR3 getOBBCenter();
	float getOBBhalf();
	E_BOSS_RAG_STATE getCondition() { return cBoss_rag_state; }
};


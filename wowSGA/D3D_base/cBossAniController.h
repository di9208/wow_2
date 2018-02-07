#pragma once
#include "cUnit.h"
class cSkinnedMesh;
class cOBB;

class cBossAniController
{
	cSkinnedMesh*		m_pSkinnedMesh;
	cSkinnedMesh*		m_pSkinnedMeshSkill;		//리치왕스킬용

	E_BOSS_STATE		cBoss_STATE;
//	cOBB*				m_pBossOBB;
	SYNTHESIZE(cOBB*, m_pBossOBB, BossOBB);

private:
	bool				m_bSKill;					//스킬 조건

private:
	SYNTHESIZE(float, m_fBossRotY, fBossRotY);
	SYNTHESIZE(D3DXVECTOR3, m_vBossPos, vBossPos);
	SYNTHESIZE(D3DXVECTOR3, m_vBossDir, BossDir);
	SYNTHESIZE_REF(D3DXMATRIXA16, m_world, World);
	D3DXVECTOR3	m_vBossDirX;
	SYNTHESIZE(D3DXMATRIXA16, m_World, World);
public:
	cBossAniController();
	~cBossAniController();

	void SetUp();
	void Update(E_BOSS_STATE* pState);
	void Render(D3DXMATRIXA16* m_world);

	void SetAnimation(E_BOSS_STATE* pState);
	void Skill();
	void Collision(cOBB* PlayerBox);
};


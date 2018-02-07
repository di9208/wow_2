#pragma once
#include "cUnit.h"
class cSkinnedMesh;

class cBossAniController
{
	SYNTHESIZE(cSkinnedMesh*, m_pSkinnedMesh, SkinnedMesh);
	//cSkinnedMesh*		m_pSkinnedMesh;
	cSkinnedMesh*		m_pSkinnedMeshSkill;		//리치왕스킬용

	E_BOSS_STATE		cBoss_STATE;

private:
	bool				m_bSKill;					//스킬 조건

private:
	SYNTHESIZE(float, m_fBossRotY, fBossRotY);
	SYNTHESIZE(D3DXVECTOR3, m_vBossPos, vBossPos);
	SYNTHESIZE(D3DXVECTOR3, m_vBossDir, BossDir);
	SYNTHESIZE_REF(D3DXMATRIXA16, m_world, mWorld);
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
	
};


#pragma once
#include "cUnit.h"
class cSkinnedMesh;
class cOBB;
class cParticle;

class cBossAniController
{
	cSkinnedMesh*		m_pSkinnedMesh;
	cSkinnedMesh*		m_pSkinnedMeshSkill;		//리치왕스킬 // 가시 솟아오르기
	cSkinnedMesh*		m_pSkinnedMeshSkill2;		//리치왕스킬 // 아이스노바
	E_BOSS_STATE		cBoss_STATE;
//	cOBB*				m_pBossOBB;
	SYNTHESIZE(cOBB*, m_pBossOBB, BossOBB);

private:
	bool				m_bSKill;					//스킬 조건

private:
	SYNTHESIZE(float, m_fBossRotY, fBossRotY);
	SYNTHESIZE(D3DXVECTOR3, m_vBossPos, vBossPos);
	SYNTHESIZE(D3DXVECTOR3, m_vBossDir, BossDir);
	SYNTHESIZE_REF(D3DXMATRIXA16, m_world, world);
	D3DXVECTOR3	m_vBossDirX;
	SYNTHESIZE_REF(D3DXMATRIXA16, m_World, World);

	D3DXMATRIXA16 m_obbw;
public:
	cBossAniController();
	~cBossAniController();

	void SetUp();
	void Update(E_BOSS_STATE* pState);
	void Render(D3DXMATRIXA16* m_world);
	
	void SetAnimation(E_BOSS_STATE* pState);
	void Skill();
	void Collision(cOBB* PlayerBox);
	void skillRender();
	cOBB* getOBB( ) { return m_pBossOBB; }
	D3DXVECTOR3 getOBBCenter();
	float getOBBhalf();
	E_BOSS_STATE getCondition() { return cBoss_STATE; }
};


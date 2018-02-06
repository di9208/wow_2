#pragma once
#include "cEnemyManager.h"

class cBossAniController;
class cBossSkill;

class cBoss : public cEnemyManager
{
private:
	cBossAniController * m_pBossAniController;
	cBossSkill*			m_pBossSkill;

private:
	//Picking
	std::vector<ST_SPHERE>		m_vecSphere;

	D3DMATERIAL9				m_stMtlNone;
	D3DMATERIAL9				m_stMtlPicked;

	LPD3DXMESH					m_pMeshSphere;

private:

public:
	cBoss();
	~cBoss();

	void SetUp();
	void Update();
	void Render();
	void Picking();
	void SetupUI();
	void RenderUI();

};


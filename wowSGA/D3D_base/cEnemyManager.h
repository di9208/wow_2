#pragma once
#include "cGameObject.h"
#include "cUnit.h"

class cEnemyManager : public cGameObject
{

protected:
	E_BOSS_STATE	e_boss_state;
	D3DXMATRIXA16	m_matWorld;
	float			m_fRotX;
	float			m_fRotY;



private:

public:

	void SetUp();
	void Update();
	void Render();
	void BossPos();
	cEnemyManager();
	~cEnemyManager();
};


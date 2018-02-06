#include "stdafx.h"
#include "cBoss.h"
#include "cBossAniController.h"
#include "cBossSkill.h"

cBoss::cBoss()
	:m_pBossAniController(NULL)
	,m_pBossSkill(NULL)
{
}


cBoss::~cBoss()
{
	SAFE_DELETE(m_pBossAniController);
	SAFE_DELETE(m_pBossSkill);
}

void cBoss::SetUp()
{
	m_pBossAniController = new cBossAniController();
//	m_pBossAniController->SetUp();

	m_pBossSkill = new cBossSkill();


}

void cBoss::Update()
{
	cEnemyManager::Update();

	if (m_pBossAniController)
		m_pBossAniController->Update(&e_boss_state);

	if (m_pBossSkill)
		m_pBossSkill->Update(&e_boss_state);
}

void cBoss::Render()
{
	if (m_pBossAniController)
		m_pBossAniController->Render(&m_matWorld);
}


void cBoss::Picking()
{

}

void cBoss::SetupUI()
{

}

void cBoss::RenderUI()
{

}

#include "stdafx.h"
#include "cPlayer_Enemy.h"

#include "cPlayer.h"
#include "cEnemyControl.h"
#include "cStage1.h"
#include "cFrustum.h"
#include "iMap.h"
#include "shop_TEST_CLASS.h"
#include "cRay.h"

cPlayer_Enemy::cPlayer_Enemy()
	:m_Player(NULL),
	m_EnemyControl(NULL),
	m_Stage1(NULL)
	, m_Frustum(NULL)
	, RichKing(false)
	, RichKingTime(0.0f)
	, RichKingCheck(false)
	, Player_Attack(false)
{
}


cPlayer_Enemy::~cPlayer_Enemy()
{
	SAFE_RELEASE(m_Player);
	SAFE_RELEASE(m_EnemyControl);
	SAFE_DELETE(m_Stage1);
	SAFE_DELETE(m_Frustum);
}

void cPlayer_Enemy::Setup()
{
	m_Player = new cPlayer();
	m_Player->Setup();

	m_EnemyControl = new cEnemyControl();
	m_EnemyControl->SetUp();

	//m_Stage1 = new cStage1();
	//m_Stage1->Setup();

	m_Frustum = new cFrustum();
}

void cPlayer_Enemy::Update(iMap* pMap)
{
	if (m_Player)
	{
		m_Player->Update(pMap);
		m_Player->Update(pMap);
		//늑대
		for (int i = 0; i < m_EnemyControl->getWolfVectorSize(); i++)
		{
			if (m_EnemyControl->getWolfCondition(i) == MONSTER_ATTACK || m_EnemyControl->getWolfCondition(i) == MONSTER_ATTACK)
			{
				if (m_EnemyControl->getWolfTimeCheck(i) == false)
				{
					m_EnemyControl->setWolfDamageTimeCheck(i, g_pTimeManager->GetLastUpdateTime());
					m_EnemyControl->setWolfTimeCheck(i, true);
				}
				if (m_EnemyControl->getWolfDamageCheck(i) == false)
				{
					if (m_EnemyControl->getWolfDamageTimeCheck(i) + 0.3f < g_pTimeManager->GetLastUpdateTime())
					{
						m_Player->Collsion(m_EnemyControl->getWolfOBB(i));
						m_EnemyControl->setWolfDamageCheck(i, true);
					}
				}
			}
			else
			{
				m_EnemyControl->setWolfDamageCheck(i, false);
				m_EnemyControl->setWolfTimeCheck(i, false);
			}
		}
		//거미
		for (int i = 0; i < m_EnemyControl->getSpiderVectorSize(); i++)
		{
			if (m_EnemyControl->getSpiderCondition(i) == MONSTER_ATTACK || m_EnemyControl->getSpiderCondition(i) == MONSTER_ATTACK)
			{
				if (m_EnemyControl->getSpiderTimeCheck(i) == false)
				{
					m_EnemyControl->setSpiderDamageTimeCheck(i, g_pTimeManager->GetLastUpdateTime());
					m_EnemyControl->setSpiderTimeCheck(i, true);
				}
				if (m_EnemyControl->getSpiderDamageCheck(i) == false)
				{
					if (m_EnemyControl->getSpiderDamageTimeCheck(i) + 0.3f < g_pTimeManager->GetLastUpdateTime())
					{
						m_Player->Collsion(m_EnemyControl->getSpiderOBB(i));
						m_EnemyControl->setSpiderDamageCheck(i, true);
					}
				}
			}
			else
			{
				m_EnemyControl->setSpiderDamageCheck(i, false);
				m_EnemyControl->setSpiderTimeCheck(i, false);
			}
		}
		//리치왕
		if (m_EnemyControl->getBossCondition() == E_BOSS_ATT || m_EnemyControl->getBossCondition() == E_BOSS_ATT2)
		{
			float cool;
			if (m_EnemyControl->getBossCondition() == E_BOSS_ATT)cool = 1.0f;
			if (m_EnemyControl->getBossCondition() == E_BOSS_ATT2)cool = 0.5f;
			if (!RichKingCheck)
			{
				RichKingTime = g_pTimeManager->GetLastUpdateTime();
				RichKingCheck = true;
			}
			if (!RichKing)
			{
				if (RichKingTime + cool < g_pTimeManager->GetLastUpdateTime())
				{
					m_Player->Collsion(m_EnemyControl->getBossOBB());
					RichKing = true;
				}
			}
		}
		else
		{
			RichKing = false;
			RichKingCheck = false;
		}

		//플레이어-------------------------------------
		if (m_Player->Getchractor_condition() == ATTACK || m_Player->Getchractor_condition() == SKILL_2)
		{
			if (!Player_Attack)
			{
				m_EnemyControl->WeaponHit(m_Player->getWeapon());
				Player_Attack = true;
			}
		}
		else
		{
			Player_Attack = false;
		}
	}
	if (m_EnemyControl)
		m_EnemyControl->Update(m_Player->GetPosition(), pMap);


}

void cPlayer_Enemy::Render()
{
	if (m_Player)
		m_Player->Render();

	if (m_EnemyControl)
		m_EnemyControl->Render();

}

void cPlayer_Enemy::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_Player)
		m_Player->WndProc(hWnd, message, wParam, lParam);
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		cRay r = cRay::RayAtWorldSpace(LOWORD(lParam), HIWORD(lParam));
		for (size_t i = 0; i < m_EnemyControl->getALLEnemyCenter().size(); i++)
		{
			//m_EnemyControl->getALLEnemyCenter()[i].bIsPicked = r.IsPicked(&m_EnemyControl->getALLEnemyCenter()[i]);
			if (r.IsPicked(&m_EnemyControl->getALLEnemyCenter()[i]))
			{
				m_Player->UpdatePicking(m_EnemyControl->getALLEnemyCenter()[i].Mons);
				//m_Player->setUI(true);
				m_Player->setHp(m_EnemyControl->getALLEnemyCenter()[i].HP,
					m_EnemyControl->getALLEnemyCenter()[i].Max_HP);
			}
		}
	} break;
	}
}
void cPlayer_Enemy::connet_shop(shop_TEST_CLASS * _connectSHOP)
{
	if (m_Player)
		m_Player->connet_shop_test_class(_connectSHOP);
}
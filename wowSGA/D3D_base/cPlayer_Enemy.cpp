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
	, Enemy_NUM(999)
	, Rag(false)
	, RagCheck(false)
	, RagTime(0.0f)

{
}


cPlayer_Enemy::~cPlayer_Enemy()
{
	SAFE_RELEASE(m_Player);
	SAFE_RELEASE(m_EnemyControl);
}

void cPlayer_Enemy::Setup(float x, float y, float z, std::vector<tagMon> Monster)
{
	m_Player = new cPlayer();
	m_Player->Setup(x, y, z);

	m_EnemyControl = new cEnemyControl();
	m_EnemyControl->SetUp(Monster);

	//m_Stage1 = new cStage1();
	//m_Stage1->Setup();
}

void cPlayer_Enemy::Update(iMap* pMap, std::vector<tagMon> Monster)
{
	if (m_Player)
	{
		m_Player->Update(pMap);
		//m_Player->Collsion(m_EnemyControl->getRagOBB());
		//드루
		for (int i = 0; i < m_EnemyControl->getDruidVectorSize(); i++)
		{
			if (m_EnemyControl->getDruidCondition(i) == MONSTER_ATTACK || m_EnemyControl->getDruidCondition(i) == MONSTER_ATTACK)
			{
				if (m_EnemyControl->getDruidTimeCheck(i) == false)
				{
					m_EnemyControl->setDruidDamageTimeCheck(i, g_pTimeManager->GetLastUpdateTime());
					m_EnemyControl->setDruidTimeCheck(i, true);
				}
				if (m_EnemyControl->getDruidDamageCheck(i) == false)
				{
					if (m_EnemyControl->getDruidDamageTimeCheck(i) + 0.3f < g_pTimeManager->GetLastUpdateTime())
					{
						m_Player->Collsion(m_EnemyControl->getBulletOBB(i),m_EnemyControl->getDruidATK(i));
						m_EnemyControl->setDruidDamageCheck(i, true);
					}
				}
			}
			else
			{
				m_EnemyControl->setDruidDamageCheck(i, false);
				m_EnemyControl->setDruidTimeCheck(i, false);
			}
		}
		////늑대
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
						m_Player->Collsion(m_EnemyControl->getWolfOBB(i),m_EnemyControl->getWolfATK(i));
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
		////거미
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
						m_Player->Collsion(m_EnemyControl->getSpiderOBB(i), m_EnemyControl->getSpiderATK(i));
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
		//라그
		if (m_EnemyControl->getRagCondition() == E_BOSS_ATT)
		{
			float cool;
			if (m_EnemyControl->getRagCondition() == E_BOSS_ATT)cool = 0.0f;
			if (!RagCheck)
			{
				RagTime = g_pTimeManager->GetLastUpdateTime();
				RagCheck = true;
			}
			if (!Rag)
			{
				if (RagTime + cool < g_pTimeManager->GetLastUpdateTime())
				{
					m_Player->Collsion(m_EnemyControl->getRagOBB(), m_EnemyControl->Rag_ATK());
					Rag = true;
				}
			}
		}
		else
		{
			Rag = false;
			RagCheck = false;
		}
		////리치왕
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
					m_Player->Collsion(m_EnemyControl->getBossOBB(),m_EnemyControl->Boss_ATK());
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
			m_EnemyControl->WeaponHit(m_Player->getWeapon(), m_Player->getPlayerATK());
		}
		else
		{
			m_EnemyControl->WeaponHit_AFTER(m_Player->getWeapon());
		}
	}
	if (m_EnemyControl)
		m_EnemyControl->Update(m_Player->GetPosition(), pMap, Monster);

	if (Enemy_NUM != 999)
	{
		m_Player->setHp(m_EnemyControl->getALLEnemyCenter()[Enemy_NUM].HP,
			m_EnemyControl->getALLEnemyCenter()[Enemy_NUM].Max_HP);
	}

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
				Enemy_NUM = i;
				m_Player->UpdatePicking(m_EnemyControl->getALLEnemyCenter()[i].Mons);
				m_Player->setHp(m_EnemyControl->getALLEnemyCenter()[i].HP,
					m_EnemyControl->getALLEnemyCenter()[i].Max_HP);
				m_Player->checkUI();
				break;
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

D3DXVECTOR3 cPlayer_Enemy::Getpos()
{
	return m_Player->GetPosition();
}

float cPlayer_Enemy::Getrot()
{
	return m_Player->GetRotY();
}

bool cPlayer_Enemy::isChange()
{
	return m_EnemyControl->GetChange();
}

void cPlayer_Enemy::setState(E_BOSS_STATE s)
{
	m_EnemyControl->setState(s);
}



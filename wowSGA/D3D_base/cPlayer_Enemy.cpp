#include "stdafx.h"
#include "cPlayer_Enemy.h"

#include "cPlayer.h"
#include "cEnemyControl.h"
#include "cStage1.h"
#include "cFrustum.h"
#include "iMap.h"
cPlayer_Enemy::cPlayer_Enemy()
	:m_Player(NULL),
	m_EnemyControl(NULL),
	m_Stage1(NULL)
	, m_Frustum(NULL)
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
		m_Player->Update(pMap);
	if (m_EnemyControl)
		m_EnemyControl->Update(m_Player->GetPosition(), pMap);
}

void cPlayer_Enemy::Render()
{
	if (m_Player)
		m_Player->Render();

	if (m_EnemyControl)
		m_EnemyControl->Render();
	//if (m_Stage1)
	//	m_Stage1->Draw(m_Frustum);
}

void cPlayer_Enemy::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_Player)
		m_Player->WndProc(hWnd, message, wParam, lParam);
}

#include "stdafx.h"
#include "cPlayer.h"

#include "cPlayerAniController.h"
#include "cPlayerSkill.h"
#include "cWeapon.h"
#include "cPlayerInFo.h"
#include "cOBB.h"
#include "iMap.h"
#include "shop_TEST_CLASS.h"


cPlayer::cPlayer()
	:m_playerAnimController(NULL),
	m_playerSkill(NULL),
	m_Weapon(NULL),
	m_playerInFo(NULL),
	m_EnemyPos(0, 0, 0),
	m_playerPicking(NULL),
	m_EnemyPicking(NULL)
{
}

cPlayer::~cPlayer()
{
	SAFE_DELETE(m_playerAnimController);
	SAFE_DELETE(m_playerSkill);
	SAFE_DELETE(m_Weapon);
	SAFE_DELETE(m_playerInFo);
	SAFE_DELETE(m_playerPicking);
	SAFE_DELETE(m_EnemyPicking);
}

void cPlayer::Setup()
{
	m_playerAnimController = new cPlayerAniController();
	m_playerAnimController->Setup();

	m_playerSkill = new cPlayerSkill();
	m_playerSkill->Setup();


	D3DXMATRIXA16  matR, matS, World;
	D3DXMatrixRotationX(&matR, D3DX_PI / 2.0f);
	D3DXMatrixScaling(&matS, 0.015f, 0.015f, 0.015f);
	D3DXMatrixIdentity(&World);
	World = matS * matR;

	m_Weapon = new cWeapon();
	m_Weapon->Setup(&m_matWorld, m_playerAnimController->GetFindBONE("character_human_male_humanmale_hd_bone_110"), &World);

	m_playerInFo = new cPlayerInFo();
	m_playerInFo->Setup(m_playerAnimController->GetSkinnedMesh(), &World);
}

void cPlayer::Update(iMap* m_map)
{
	cCharacter::Update(m_map, m_playerAnimController->GetAniCheck());

	if (m_playerAnimController)
		m_playerAnimController->Update(&m_chractor_condition);

	if (m_playerSkill)
		m_playerSkill->Update(&m_chractor_condition, m_playerAnimController->GetAniCheck());

	if (m_Weapon)
		m_Weapon->Update(&m_matWorld, m_playerAnimController->GetFindBONE("character_human_male_humanmale_hd_bone_110"));

	D3DXMATRIXA16 mat, matR, matS;
	D3DXMatrixRotationX(&matR, D3DX_PI / 2.0f);
	D3DXMatrixScaling(&matS, 0.15f, 0.15f, 0.15f);
	mat = matR * m_matWorld;

	if (m_playerInFo)
		m_playerInFo->Update(&m_chractor_condition, &m_matWorld);



	//Collsion(m_DummyBox->GetOBB());
}

void cPlayer::Render()
{
	if (m_playerAnimController)
		m_playerAnimController->Render(&m_matWorld);
	if (m_Weapon)
		m_Weapon->Render(&m_matWorld);
	if (m_playerInFo)
		m_playerInFo->Render(&m_playerAnimController->GetWorld(), &m_matWorld);
	if (m_playerSkill)
		m_playerSkill->Render();
}

void cPlayer::Collsion(cOBB * EnemyBox)
{
	m_playerInFo->Collsion(EnemyBox);
}

void cPlayer::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_playerInFo)
	{
		m_playerInFo->WndProc(hWnd, message, wParam, lParam);
	}
}

void cPlayer::SetPlayerPick(std::vector<ST_PC_VERTEX> m_vecVertex)
{
	//m_playerPicking->Setup(m_vecVertex);
}

void cPlayer::connet_shop_test_class(shop_TEST_CLASS * connect_shop_test)
{
	if (connect_shop_test->Getpicking_data().mouse_pick)
	{
		//m_playerInFo
	}
}

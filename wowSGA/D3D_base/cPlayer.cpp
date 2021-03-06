#include "stdafx.h"
#include "cPlayer.h"

#include "cPlayerAniController.h"
#include "cPlayerSkill.h"
#include "cWeapon.h"
#include "cPlayerInFo.h"
#include "cOBB.h"
#include "iMap.h"
#include "shop_TEST_CLASS.h"
#include "cEnemyPicking.h"
#include "cPlayerSound.h"

cPlayer::cPlayer()
	:m_playerAnimController(NULL),
	m_playerSkill(NULL),
	m_Weapon(NULL),
	m_playerInFo(NULL),
	m_EnemyPos(0, 0, 0),
	m_playerPicking(NULL),
	m_EnemyPicking(NULL),
	weaponNUM(1),
	WeaponNUMCheck(0)
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

void cPlayer::Setup(float x, float y, float z)
{
	m_vPos.x = x;
	m_vPos.y = y;
	m_vPos.z = z;

	m_playerAnimController = new cPlayerAniController();
	m_playerAnimController->Setup(x, y, z);

	m_playerSkill = new cPlayerSkill();
	m_playerSkill->Setup();


	D3DXMATRIXA16  matR, matS, World, matRY;
	D3DXMatrixRotationX(&matR, D3DX_PI / 2.0f);
	D3DXMatrixRotationY(&matRY, D3DX_PI / 2.0f);
	D3DXMatrixScaling(&matS, 0.05f, 0.03f, 0.015f);
	D3DXMatrixIdentity(&World);
	World = matS * matR;

	m_Weapon = new cWeapon();
	m_Weapon->Setup(&m_matWorld, m_playerAnimController->GetFindBONE("character_human_male_humanmale_hd_bone_110"), &World);

	m_playerInFo = new cPlayerInFo();
	m_playerInFo->Setup(m_playerAnimController->GetSkinnedMesh(), &World);

	m_EnemyPicking = new cEnemyPicking();
	m_EnemyPicking->Setup();

	m_playerSound = new cPlayerSound();
	m_playerSound->Setup();
}

void cPlayer::Update(iMap* m_map)
{
	if (m_chractor_condition != DEATH)
	{
		cCharacter::Update(m_map, m_playerAnimController->GetAniCheck());

		if (m_playerAnimController)
			m_playerAnimController->Update(&m_chractor_condition);

		if (m_playerInFo)
		{
			m_playerInFo->Update(&m_chractor_condition, &m_matWorld);
			if (m_playerInFo->Getchange_weapon())
			{
				m_Weapon->change(m_playerInFo->findItemNUM());
				m_playerInFo->Setchange_weapon(false);
			}
		}
	}

	if (m_playerSkill)
		m_playerSkill->Update(&m_chractor_condition, m_playerAnimController->GetAniCheck());

	if (m_Weapon)
	{
		m_Weapon->Update(&m_matWorld, m_playerAnimController->GetFindBONE("character_human_male_humanmale_hd_bone_110"));
	}
	D3DXMATRIXA16 mat, matR, matS, matRY;

	weaponNUM = m_Weapon->GetWeaponNum();

	D3DXMatrixRotationX(&matR, D3DX_PI / 2.0f);
	D3DXMatrixScaling(&matS, 0.15f, 0.15f, 0.15f);
	mat = matR * m_matWorld;

	if (m_playerSound)
		m_playerSound->Update(&m_chractor_condition);
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
	if (m_EnemyPicking)
		m_EnemyPicking->Render();
}

void cPlayer::UpdatePicking(MONSTER_KIND monster)
{
	m_EnemyPicking->Update(monster);
}


void cPlayer::Collsion(cOBB * EnemyBox, float Damage)
{
	m_playerInFo->Collsion(EnemyBox, Damage);
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
	m_playerInFo->getItem(connect_shop_test);
	connect_shop_test->setting_playerinfo(m_playerInFo);
}
void cPlayer::setUI(bool check)
{
	m_EnemyPicking->setUI(check);
}

void cPlayer::setHp(int hp, int maxHP)
{
	m_EnemyPicking->HPset(hp, maxHP);
}

void cPlayer::checkUI()
{
	return m_EnemyPicking->SetUiOn(true);
}

float cPlayer::getPlayerATK()
{
	return m_playerInFo->GetPlayerInFo().ATK;
}

cOBB * cPlayer::getWeapon()
{
	return m_Weapon->GetweaponOBB();
}


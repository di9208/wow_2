#include "stdafx.h"
#include "cPlayer.h"

#include "cPlayerAniController.h"
#include "cPlayerSkill.h"
#include "cWeapon.h"
#include "cPlayerInFo.h"
#include "cOBB.h"

cPlayer::cPlayer()
	:m_playerAnimController(NULL),
	m_playerSkill(NULL),
	m_Weapon(NULL),
	m_playerInFo(NULL),
	m_EnemyPos(0, 0, 0),
	m_playerOBB(NULL),
	m_weaponOBB(NULL)
{
}

cPlayer::~cPlayer()
{
	SAFE_DELETE(m_playerAnimController);
	SAFE_DELETE(m_playerSkill);
	SAFE_DELETE(m_Weapon);
	SAFE_DELETE(m_playerInFo);
	SAFE_DELETE(m_playerOBB);
	SAFE_DELETE(m_weaponOBB);
}

void cPlayer::Setup()
{
	m_playerAnimController = new cPlayerAniController();
	m_playerAnimController->Setup();

	m_playerSkill = new cPlayerSkill();
	m_playerSkill->Setup();

	m_Weapon = new cWeapon();
	m_Weapon->Setup(&m_matWorld, m_playerAnimController->GetFindBONE("character_human_male_humanmale_hd_bone_110"));

	m_playerInFo = new cPlayerInFo();
	m_playerInFo->Setup();


	D3DXMATRIXA16  matR, matS, World;
	D3DXMatrixRotationX(&matR, D3DX_PI / 2.0f);
	D3DXMatrixScaling(&matS,0.15f, 0.15f, 0.15f);
	World = matS;

	m_playerOBB = new cOBB();
	//m_playerOBB->Setup((m_playerAnimController->GetFindSkinedMesh("character_human_male_humanmale_hd_bone_110")));
	m_playerOBB->Setup(m_playerAnimController->GetSkinnedMesh(),&World);
	
	m_weaponOBB = new cOBB();
	m_weaponOBB->Setup(m_Weapon->GetSkinnedMesh(),&World);
}

void cPlayer::Update()
{
	cCharacter::Update(NULL, m_playerAnimController->GetAniCheck());

	if (m_playerAnimController)
		m_playerAnimController->Update(&m_chractor_condition);

	if (m_playerSkill)
		m_playerSkill->Update(&m_chractor_condition, m_playerAnimController->GetAniCheck());

	if (m_Weapon)
		m_Weapon->Update(&m_matWorld);
	if (m_playerInFo)
		m_playerInFo->Update(&m_chractor_condition);

	if (m_playerOBB)
		m_playerOBB->Update(&m_matWorld);

	if (m_weaponOBB)
		m_weaponOBB->Update(&m_matWorld);

}

void cPlayer::Render()
{
	if (m_playerAnimController)
		m_playerAnimController->Render(&m_matWorld);
	if (m_Weapon)
		m_Weapon->Render();
	if (m_playerInFo)
		m_playerInFo->Render();

	D3DCOLOR c = D3DCOLOR_XRGB(255, 255, 255);

	if(m_weaponOBB)
		m_weaponOBB->Render_Debug(c, &m_Weapon->GetWorld(), NULL);

	if (m_playerOBB)
		m_playerOBB->Render_Debug(c, &m_playerAnimController->GetWorld(), &m_matWorld);
}

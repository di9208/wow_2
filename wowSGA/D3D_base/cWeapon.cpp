#include "stdafx.h"
#include "cWeapon.h"

#include "cSkinnedMesh.h"
#include "cOBB.h"

cWeapon::cWeapon()
	: m_pSkinnedMesh(NULL)
	, m_hand(NULL)
	, m_charactor(NULL)
	, m_WeaponNum(0)
	, m_changeTime(m_changeTime)
	, m_weaponOBB(NULL)
{

}

cWeapon::~cWeapon()
{
	SAFE_DELETE(m_pSkinnedMesh);
	SAFE_DELETE(m_weaponOBB);
}

void cWeapon::Setup(D3DXMATRIXA16* c_charactor, ST_BONE* c_hand)
{
	m_pSkinnedMesh = new cSkinnedMesh();

	m_pSkinnedMesh->Setup("Weapon", "doom.X");
	m_handle = m_pSkinnedMesh->GetFindBONE("item_objectcomponents_weapon_mace_1h_doomhammer_d_02");

	//m_weaponOBB = new cOBB();
	//m_weaponOBB->Setup(m_pSkinnedMesh);

	m_charactor = c_charactor;
	m_hand = c_hand;
}

void cWeapon::Update(D3DXMATRIXA16* world)
{
	if (m_pSkinnedMesh)
		m_pSkinnedMesh->Update();

	if (g_pKeyManager->isOnceKeyDown(VK_TAB))
	{
		m_WeaponNum++;
		if (m_changeTime == NULL)
		{
			m_changeTime = g_pTimeManager->GetEllapsedTime();
		}
		Change_Weapon();
	}

	if (m_weaponOBB)
		m_weaponOBB->Update(world);
}

void cWeapon::Render()
{
	D3DXMATRIXA16 matS, matR, World;
	D3DXMatrixScaling(&matS, 4.0f, 4.0f, 4.0f);
	D3DXMatrixRotationX(&matR, D3DX_PI);
	m_World =
		matS
		*m_hand->matCombinedTransformMatrix
		*m_handle->matCombinedTransformMatrix
		*(*m_charactor);

	if (m_pSkinnedMesh)
	{
		if (m_changeTime == NULL)
		{
			m_pSkinnedMesh->Render(NULL, &m_World);
		}
		else
		{
			if (m_changeTime + 0.00001f < g_pTimeManager->GetEllapsedTime())
			{
				m_pSkinnedMesh->Render(NULL, &m_World);
				m_changeTime = NULL;
			}
		}
	}

	D3DCOLOR c = D3DCOLOR_XRGB(255, 255, 255);

	if (m_weaponOBB)
		m_weaponOBB->Render_Debug(c, &m_World,NULL);
}

void cWeapon::Change_Weapon()
{
	SAFE_DELETE(m_pSkinnedMesh);
	m_pSkinnedMesh = new cSkinnedMesh();

	switch (m_WeaponNum % 3)
	{
	case 0:
		m_pSkinnedMesh->Setup("Weapon", "doom.X");
		m_handle = m_pSkinnedMesh->GetFindBONE("item_objectcomponents_weapon_mace_1h_doomhammer_d_02");
		break;
	case 1:
		m_pSkinnedMesh->Setup("Weapon", "axe.x");
		m_handle = m_pSkinnedMesh->GetFindBONE("item_objectcomponents_weapon_axe_2h_gorehowl_d_01_hd");
		break;
	case 2:
		m_pSkinnedMesh->Setup("Weapon", "cris.x");
		m_handle = m_pSkinnedMesh->GetFindBONE("item_objectcomponents_weapon_sword_2h_crystal_c_02");
		break;
	}
}

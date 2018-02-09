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
	, m_hp(100)
	, m_Equip(true)
{

}

cWeapon::~cWeapon()
{
	SAFE_DELETE(m_pSkinnedMesh);
	SAFE_DELETE(m_weaponOBB);
	SAFE_RELEASE(m_pFont);
}

void cWeapon::Setup(D3DXMATRIXA16* c_charactor, ST_BONE* c_hand, D3DXMATRIXA16* player)
{
	SetFont();


	m_pSkinnedMesh = new cSkinnedMesh();

	m_pSkinnedMesh->Setup("Weapon", "doom.X");
	m_handle = m_pSkinnedMesh->GetFindBONE("item_objectcomponents_weapon_mace_1h_doomhammer_d_02");

	m_charactor = c_charactor;
	m_hand = c_hand;

	D3DXMATRIXA16  matR, matS, World;
	D3DXMatrixRotationX(&matR, D3DX_PI / 2.0f);
	D3DXMatrixScaling(&matS, 0.025f, 0.025f, 0.025f);
	D3DXMatrixIdentity(&World);
	World = matS * matR;
	D3DXMatrixIdentity(&m_World);
	m_World = World;


	m_weaponOBB = new cOBB();
	m_weaponOBB->Setup(m_pSkinnedMesh, &m_World);

}

void cWeapon::Update(D3DXMATRIXA16* world, ST_BONE* c_hand)
{
	if (m_pSkinnedMesh)
		m_pSkinnedMesh->Update();

	D3DXMATRIXA16 matS, matR;
	D3DXMatrixRotationX(&matR, D3DX_PI / 2.0f);




	//matR = matR1;


	if (m_weaponOBB)
	{
		m_weaponOBB->Update(&m_player);
	}
}

void cWeapon::Render(D3DXMATRIXA16* world)
{
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 4.0f, 4.0f, 4.0f);
	m_WorldTM =
		matS *
		(m_hand->matCombinedTransformMatrix)
		*(m_handle->matCombinedTransformMatrix)
		*(*world);

	D3DXMatrixScaling(&matS, 35.0f, 35.0f, 35.0f);
	m_player =
		matS *
		(m_hand->matCombinedTransformMatrix)
		*(m_handle->matCombinedTransformMatrix)
		*(*world);
	if (m_pSkinnedMesh)
	{
		if (m_changeTime == NULL)
		{
			m_pSkinnedMesh->Render(NULL, &m_WorldTM);
		}
		else
		{
			if (m_changeTime + 0.00001f < g_pTimeManager->GetEllapsedTime())
			{
				m_pSkinnedMesh->Render(NULL, &m_WorldTM);
				m_changeTime = NULL;
			}
		}
	}

	D3DCOLOR c = D3DCOLOR_XRGB(255, 255, 255);

	if (m_weaponOBB)
		m_weaponOBB->Render_Debug(c, &m_WorldTM, NULL);

	RenderFont();
}

void cWeapon::Change_Weapon(int n)
{
	SAFE_DELETE(m_pSkinnedMesh);
	m_pSkinnedMesh = new cSkinnedMesh();

	switch (n % 3)
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

void cWeapon::collsion(cOBB * EnemyBox)
{
	if (EnemyBox)
	{

		if (EnemyBox->getCheck(0).x != -431602080)
		{
			if (m_weaponOBB->IsCollision(m_weaponOBB, EnemyBox))
			{
				m_hp = 0;
			}
			else
			{
				m_hp = 1;
			}
		}
	}

}

void cWeapon::SetFont()
{
	D3DXFONT_DESC stFD;
	ZeroMemory(&stFD, sizeof(D3DXFONT_DESC));
	stFD.Height = 50;
	stFD.Width = 25;
	stFD.Weight = FW_MEDIUM;
	stFD.Italic = false;
	stFD.CharSet = DEFAULT_CHARSET;
	stFD.OutputPrecision = OUT_DEFAULT_PRECIS;
	stFD.PitchAndFamily = FF_DONTCARE;

	AddFontResource("font/umberto.ttf");
	strcpy_s(stFD.FaceName, "umberto");

	D3DXCreateFontIndirect(g_pD3DDevice, &stFD, &m_pFont);
}

void cWeapon::RenderFont()
{
	if (m_pFont)
	{
		//std::string sText = Convert(m_hp);
		////sprintf(sText, "%f", (PlayerInFo.HP));

		//RECT rc;
		//SetRect(&rc, 100, 100, 300, 200);

		//m_pFont->DrawText(NULL,
		//	sText.c_str(),
		//	sText.length(),
		//	&rc,
		//	DT_LEFT | DT_TOP | DT_NOCLIP,
		//	D3DCOLOR_XRGB(255, 255, 0));
	}
}

void cWeapon::change(int n)
{
	
	{

		if (m_changeTime == NULL)
		{
			m_changeTime = g_pTimeManager->GetEllapsedTime();
		}
		Change_Weapon(n);
	}
}


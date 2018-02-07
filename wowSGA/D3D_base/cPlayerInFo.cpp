#include "stdafx.h"
#include "cPlayerInFo.h"

#include <sstream>
#include "cOBB.h"

//std::string Convert(float number) {
//	std::ostringstream buff;
//	buff << number;
//	return buff.str();
//}


cPlayerInFo::cPlayerInFo()
	:m_pTexture(NULL)
	, m_pSprite(NULL)
	, m_playerOBB(NULL)
	, m_PlayerUI_back(NULL)
	, m_PlayerUI(NULL)
{

}

cPlayerInFo::~cPlayerInFo()
{
	SAFE_RELEASE(m_pFont);
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_PlayerUI_back);
	SAFE_RELEASE(m_PlayerUI);
	SAFE_DELETE(m_playerOBB);
}

void cPlayerInFo::Setup(cSkinnedMesh* playerSkinned, D3DXMATRIXA16* playerWorld)
{
	SetFont();
	SetUI();
	PlayerInFo.HP = 100;
	PlayerInFo.MP = 70;


	m_playerOBB = new cOBB();
	m_playerOBB->Setup(playerSkinned, playerWorld);
}

void cPlayerInFo::Update(condition* pCondition, D3DXMATRIXA16* pMatWorld)
{
	if (g_pKeyManager->isOnceKeyDown('Q'))
	{
		if (PlayerInFo.HP>0)PlayerInFo.HP -= 10;
		*pCondition = HURT;
	}
	if (m_playerOBB)
		m_playerOBB->Update(pMatWorld);
}

void cPlayerInFo::SetFont()
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

void cPlayerInFo::SetUI()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
	ZeroMemory(&m_stImageInfo, sizeof(D3DXIMAGE_INFO));
	ZeroMemory(&m_PlayerUI_backinfo, sizeof(D3DXIMAGE_INFO));
	ZeroMemory(&m_PlayerUI_info, sizeof(D3DXIMAGE_INFO));

	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		"player/PLAYER_UI.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_stImageInfo,
		NULL,
		&m_pTexture);

	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		"player/Player_Human.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_PlayerUI_info,
		NULL,
		&m_PlayerUI);

	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		"player/Player_BACK.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_PlayerUI_backinfo,
		NULL,
		&m_PlayerUI_back);
}

void cPlayerInFo::RenderUI()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	//m_pSprite->Draw(m_pTexture,
	//	NULL, //&rc,
	//	&D3DXVECTOR3(m_stImageInfo.Width / 2.0f, m_stImageInfo.Height / 2.0, 0),
	//	&D3DXVECTOR3(WIDTH/2.0f, HEIGHT-159, 0.5f),
	//	D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pSprite->Draw(m_PlayerUI,
		NULL, //&rc,
		&D3DXVECTOR3(m_PlayerUI_info.Width / 2.0f + 50, m_PlayerUI_info.Height / 2.0 + 50, 0),
		&D3DXVECTOR3(m_PlayerUI_info.Width / 2.0f + 50, m_PlayerUI_info.Height / 2.0 + 50, 0.5f),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pSprite->Draw(m_PlayerUI_back,
		NULL, //&rc,
		&D3DXVECTOR3(m_PlayerUI_backinfo.Width / 2.0f + 50, m_PlayerUI_backinfo.Height / 2.0 + 50, 0),
		&D3DXVECTOR3(m_PlayerUI_backinfo.Width / 2.0f + 50, m_PlayerUI_backinfo.Height / 2.0 + 50, 0.5f),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pSprite->End();
}

void cPlayerInFo::RenderFont()
{
	if (m_pFont)
	{
		//std::string sText = Convert(PlayerInFo.HP);
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

void cPlayerInFo::Render(D3DXMATRIXA16* playerWorld, D3DXMATRIXA16* pMatWorld)
{
	RenderUI();
	RenderFont();

	D3DCOLOR c = D3DCOLOR_XRGB(0, 255, 255);

	if (m_playerOBB)
		m_playerOBB->Render_Debug(c, playerWorld, pMatWorld);
}

void cPlayerInFo::Collsion(cOBB * EnemyBox)
{
	if (EnemyBox)
	{

		if (EnemyBox->getCheck(0).x != -431602080 && m_playerOBB->getCheck(0).x != -431602080)
		{
			if (m_playerOBB->IsCollision(m_playerOBB, EnemyBox))
			{
				PlayerInFo.HP = 100;
			}
			else
			{
				PlayerInFo.HP = 200;
			}
		}
	}
}

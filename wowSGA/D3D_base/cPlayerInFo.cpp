#include "stdafx.h"
#include "cPlayerInFo.h"

#include <sstream>
#include "cOBB.h"

std::string Convert(float number) {
	std::ostringstream buff;
	buff << number;
	return buff.str();
}

cPlayerInFo::cPlayerInFo()
	:m_pTexture(NULL)
	, m_pSprite(NULL)
	, m_playerOBB(NULL)
	, m_PlayerUI_back(NULL)
	, m_PlayerUI(NULL)
	, m_statusUI(NULL)
	, m_status(false)
{
	Pt.x = 0;
	Pt.y = 0;
}

cPlayerInFo::~cPlayerInFo()
{
	SAFE_RELEASE(m_pFont);
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_PlayerUI_back);
	SAFE_RELEASE(m_PlayerUI);
	SAFE_RELEASE(m_statusUI);

	SAFE_DELETE(m_playerOBB);
}

void cPlayerInFo::Setup(cSkinnedMesh* playerSkinned, D3DXMATRIXA16* playerWorld)
{
	SetFont();
	SetUI();
	setRC();
	PlayerInFo.HP = 100;
	PlayerInFo.MP = 70;
	PlayerInFo.ATK = 10;
	PlayerInFo.DEF = 5;
	PlayerInFo.Gold = 0;

	m_playerOBB = new cOBB();
	m_playerOBB->Setup(playerSkinned, playerWorld);
}

void cPlayerInFo::Update(condition* pCondition, D3DXMATRIXA16* pMatWorld)
{
	if (g_pKeyManager->isOnceKeyDown('Q'))
	{
		if (PlayerInFo.HP > 0)PlayerInFo.HP -= 10;
		*pCondition = HURT;
	}
	if (g_pKeyManager->isOnceKeyDown('E'))
	{
		if (!m_status)m_status = true;
		else m_status = false;
	}
	if (m_playerOBB)
		m_playerOBB->Update(pMatWorld);

	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	if (m_status)
	{
		for (int i = 0; i < 5; i++)
		{
			if (PtInRect(&m_stats[i].m_statsRC, Pt))
			{
				int a = 0;
			}
		}
	}
}

void cPlayerInFo::SetFont()
{
	D3DXFONT_DESC stFD;
	ZeroMemory(&stFD, sizeof(D3DXFONT_DESC));
	stFD.Height = 15;
	stFD.Width = 7;
	stFD.Weight = FW_MEDIUM;
	stFD.Italic = false;
	stFD.CharSet = DEFAULT_CHARSET;
	stFD.OutputPrecision = OUT_DEFAULT_PRECIS;
	stFD.PitchAndFamily = FF_DONTCARE;

	AddFontResource("FRIZQT__.TTF");
	strcpy_s(stFD.FaceName, "FRIZQT__");

	D3DXCreateFontIndirect(g_pD3DDevice, &stFD, &m_pFont);
}

void cPlayerInFo::SetUI()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
	ZeroMemory(&m_stImageInfo, sizeof(D3DXIMAGE_INFO));
	ZeroMemory(&m_PlayerUI_backinfo, sizeof(D3DXIMAGE_INFO));
	ZeroMemory(&m_PlayerUI_info, sizeof(D3DXIMAGE_INFO));
	ZeroMemory(&m_statusUI_info, sizeof(D3DXIMAGE_INFO));
	ZeroMemory(&m_Dummy_info, sizeof(D3DXIMAGE_INFO));

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

	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		"player/제목 없음.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_Dummy_info,
		NULL,
		&m_Dummy);

	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		"player/UI_PLAYER.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_statusUI_info,
		NULL,
		&m_statusUI);

}

void cPlayerInFo::RenderUI()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	m_pSprite->Draw(m_pTexture,
		NULL, //&rc,
		&D3DXVECTOR3(m_stImageInfo.Width / 2.0f, m_stImageInfo.Height / 2.0, 0),
		&D3DXVECTOR3(WIDTH / 2.0f, HEIGHT - 100, 0.0f),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pSprite->Draw(m_PlayerUI,
		NULL, //&rc,
		&D3DXVECTOR3(m_PlayerUI_info.Width / 2.0f + 50, m_PlayerUI_info.Height / 2.0 + 50, 0),
		&D3DXVECTOR3(m_PlayerUI_info.Width / 2.0f + 50, m_PlayerUI_info.Height / 2.0 + 50, 0.0f),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pSprite->Draw(m_PlayerUI_back,
		NULL, //&rc,
		&D3DXVECTOR3(m_PlayerUI_backinfo.Width / 2.0f + 50, m_PlayerUI_backinfo.Height / 2.0 + 50, 0),
		&D3DXVECTOR3(m_PlayerUI_backinfo.Width / 2.0f + 50, m_PlayerUI_backinfo.Height / 2.0 + 50, 0.0f),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pSprite->End();
}

void cPlayerInFo::RenderFont()
{
	if (m_pFont)
	{
		std::string sText =
			"체력: " + Convert(PlayerInFo.HP) + "\n"
			"마력: " + Convert(PlayerInFo.MP) + "\n"
			"공격력: " + Convert(PlayerInFo.ATK) + "\n"
			"방어력: " + Convert(PlayerInFo.DEF) + "\n"
			"소지금: " + Convert(PlayerInFo.Gold) + "\n";
		//sprintf(sText, "%f", (PlayerInFo.HP));

		RECT rc;
		SetRect(&rc, 410, 270, 510, 370);

		m_pFont->DrawText(NULL,
			sText.c_str(),
			sText.length(),
			&rc,
			DT_LEFT | DT_TOP | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 255));
	}
}

void cPlayerInFo::Render(D3DXMATRIXA16* playerWorld, D3DXMATRIXA16* pMatWorld)
{
	RenderUI();
	if (m_status)
	{
		RenderPlayerStat();
		RenderFont();
	}

	D3DCOLOR c = D3DCOLOR_XRGB(0, 255, 255);

	if (m_playerOBB)
		m_playerOBB->Render_Debug(c, playerWorld, pMatWorld);
}

void cPlayerInFo::RenderPlayerStat()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	m_pSprite->Draw(m_statusUI,
		NULL, //&rc,
		&D3DXVECTOR3(m_statusUI_info.Width / 2.0f, m_statusUI_info.Height / 2.0, 0),
		&D3DXVECTOR3(m_statusUI_info.Width / 2.0f + 50, m_statusUI_info.Height / 2.0 + 150, 0.0f),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	//m_pSprite->Draw(m_Dummy,
	//	NULL, //&rc,
	//	&D3DXVECTOR3(m_Dummy_info.Width / 2.0f, m_Dummy_info.Height / 2.0, 0),
	//	&D3DXVECTOR3(
	//		m_Dummy_info.Width / 2.0f + m_stats[4].m_x,
	//		m_Dummy_info.Height / 2.0 + m_stats[4].m_y,
	//		0.0f),
	//	D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pSprite->End();
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

void cPlayerInFo::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_SETCURSOR:
		break;
	}
}

void cPlayerInFo::setRC()
{
	float base_X = 50;
	float base_Y = 150;

	m_stats[0].m_x = 70;
	m_stats[0].m_y = 430;
	m_stats[0].check = false;
	m_stats[0].m_statsRC = { 70,430,100,460 };

	m_stats[1].m_x = 350;
	m_stats[1].m_y = 310;
	m_stats[1].check = false;
	m_stats[1].m_statsRC = { 350,310,380,340 };

	m_stats[2].m_x = 350;
	m_stats[2].m_y = 350;
	m_stats[2].check = false;
	m_stats[2].m_statsRC = { 350,350,380,380 };

	m_stats[3].m_x = 70;
	m_stats[3].m_y = 510;
	m_stats[3].check = false;
	m_stats[3].m_statsRC = { 70,510,100,540 };

	m_stats[4].m_x = 195;
	m_stats[4].m_y = 535;
	m_stats[4].check = false;
	m_stats[4].m_statsRC = { 190,535,220,565 };

}

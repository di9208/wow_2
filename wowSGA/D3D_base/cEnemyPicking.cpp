#include "stdafx.h"
#include "cEnemyPicking.h"


cEnemyPicking::cEnemyPicking()
	: m_EnemyUI_back(NULL),
	m_pSprite(NULL),
	m_EnemyUI(NULL),
	m_EnemyIcon(NULL),
	m_UiOn(false),
	m_HP(NULL),
	m_HPint(1),
	m_MaxHPint(1)
{
}


cEnemyPicking::~cEnemyPicking()
{
	SAFE_RELEASE(m_EnemyUI_back);
	SAFE_RELEASE(m_EnemyUI);
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_EnemyIcon);
	SAFE_RELEASE(m_HP);
}

void cEnemyPicking::Setup()
{
	SetFont();
	SetUI();
}

void cEnemyPicking::Update(MONSTER_KIND monster)
{
	switch (monster)
	{
	case KIND_BOSS_ARTHAS:
	{
		SAFE_RELEASE(m_EnemyIcon);
		D3DXCreateTextureFromFileEx(
			g_pD3DDevice,
			"player/RichKing.png",
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			0,
			&m_EnemyIcon_info,
			NULL,
			&m_EnemyIcon);
	}
	break;
	case KIND_SPIDER:
	{
		SAFE_RELEASE(m_EnemyIcon);
		D3DXCreateTextureFromFileEx(
			g_pD3DDevice,
			"player/Spider.png",
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			0,
			&m_EnemyIcon_info,
			NULL,
			&m_EnemyIcon);
	}
	break;
	case KIND_WORG:
	{
		SAFE_RELEASE(m_EnemyIcon);
		D3DXCreateTextureFromFileEx(
			g_pD3DDevice,
			"player/wolf.png",
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			0,
			&m_EnemyIcon_info,
			NULL,
			&m_EnemyIcon);
	}
	break;
	case KIND_DRUID:
	{
		SAFE_RELEASE(m_EnemyIcon);
		D3DXCreateTextureFromFileEx(
			g_pD3DDevice,
			"player/druid.png",
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			0,
			&m_EnemyIcon_info,
			NULL,
			&m_EnemyIcon);
	}
	break;
	case KIND_BOSS_RAGNALOS:
	{
		SAFE_RELEASE(m_EnemyIcon);
		D3DXCreateTextureFromFileEx(
			g_pD3DDevice,
			"player/rag.png",
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			0,
			&m_EnemyIcon_info,
			NULL,
			&m_EnemyIcon);
	}
	break;
	}
}

void cEnemyPicking::SetFont()
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

	D3DXCreateFontIndirect(g_pD3DDevice, &stFD, &m_HpFont);
}

void cEnemyPicking::SetUI()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	ZeroMemory(&m_EnemyUI_backinfo, sizeof(D3DXIMAGE_INFO));
	ZeroMemory(&m_EnemyUI_info, sizeof(D3DXIMAGE_INFO));
	ZeroMemory(&m_EnemyIcon_info, sizeof(D3DXIMAGE_INFO));
	ZeroMemory(&m_HPinfo, sizeof(D3DXIMAGE_INFO));


	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		"player/HP_BAR.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_HPinfo,
		NULL,
		&m_HP);

	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		"player/Charactor_STATS.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_EnemyUI_info,
		NULL,
		&m_EnemyUI);

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
		&m_EnemyUI_backinfo,
		NULL,
		&m_EnemyUI_back);

	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		"player/RichKing.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_EnemyIcon_info,
		NULL,
		&m_EnemyIcon);
}


void cEnemyPicking::RenderFont()
{
	if (m_HpFont)
	{
		char str[128];
		if (m_HPint > 0)
		{
			sprintf(str, "HP: %.0f / %.0f", m_HPint, m_MaxHPint);
		}
		else
		{
			sprintf(str, "����");
		}

		std::string sText(str);

		RECT rc;
		SetRect(&rc, 650, 53, 750, 250);

		m_HpFont->DrawText(NULL,
			sText.c_str(),
			sText.length(),
			&rc,
			DT_LEFT | DT_TOP | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 255));
	}
}

void cEnemyPicking::HPset(float hp, float maxHp)
{
	m_MaxHPint = maxHp;
	m_HPint = hp;
}

void cEnemyPicking::Render()
{

	if (m_UiOn)
	{
		RenderFont();

		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

		m_pSprite->Draw(m_EnemyIcon,
			NULL, //&rc,
			&D3DXVECTOR3(m_EnemyIcon_info.Width / 2.0f + 50, m_EnemyIcon_info.Height / 2.0 + 50, 0),
			&D3DXVECTOR3(WIDTH / 2.0f - 165, m_EnemyIcon_info.Height / 2.0 + 85, 0.5f),
			D3DCOLOR_ARGB(255, 255, 255, 255));

		m_pSprite->Draw(m_EnemyUI,
			NULL, //&rc,
			&D3DXVECTOR3(m_EnemyUI_info.Width / 2.0f + 50, m_EnemyUI_info.Height / 2.0 + 50, 0),
			&D3DXVECTOR3(WIDTH / 2.0f - 80, m_EnemyUI_info.Height / 2.0 + 50, 0.5f),
			D3DCOLOR_ARGB(255, 255, 255, 255));

		m_pSprite->Draw(m_EnemyUI_back,
			NULL, //&rc,
			&D3DXVECTOR3(m_EnemyUI_backinfo.Width / 2.0f + 50, m_EnemyUI_backinfo.Height / 2.0 + 50, 0),
			&D3DXVECTOR3(WIDTH / 2.0f - 80, m_EnemyUI_backinfo.Height / 2.0 + 50, 0.7f),
			D3DCOLOR_ARGB(255, 255, 255, 255));

		float a = (float)m_HPint / (float)m_MaxHPint;
		if (a < 0)a = 0;
		RECT rc = { 0,0,m_HPinfo.Width*a,m_HPinfo.Height };
		m_pSprite->Draw(m_HP,
			&rc, //&rc,
			&D3DXVECTOR3(m_HPinfo.Width / 2.0f + 45, m_HPinfo.Height / 2.0 + 50, 0),
			&D3DXVECTOR3(WIDTH / 2.0f - 50, m_EnemyUI_backinfo.Height / 2.0 + 30, 0.6f),
			D3DCOLOR_ARGB(255, 255, 255, 255));




		m_pSprite->End();
	}
}

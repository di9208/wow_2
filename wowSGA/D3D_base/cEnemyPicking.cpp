#include "stdafx.h"
#include "cEnemyPicking.h"


cEnemyPicking::cEnemyPicking()
	: m_EnemyUI_back(NULL),
	m_pSprite(NULL),
	m_EnemyUI(NULL),
	m_EnemyIcon(NULL),
	m_UiOn(true),
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
	case BOSS_ARTHAS:
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
	case SPIDER:
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
	case WORG:
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
	}
}

void cEnemyPicking::SetFont()
{
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

void cEnemyPicking::RenderUI()
{
}

void cEnemyPicking::RenderFont()
{
}

void cEnemyPicking::DistanceSet(D3DXVECTOR3 Player, D3DXVECTOR3 Enemy)
{
}

void cEnemyPicking::HPset(float hp, float maxHp)
{
	m_MaxHPint = maxHp;
	m_HPint = hp;
}

void cEnemyPicking::Render()
{
	//if (m_UiOn)
	{
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
		RECT rc = { 0,0,m_HPinfo.Width*a,m_HPinfo.Height };
		m_pSprite->Draw(m_HP,
			&rc, //&rc,
			&D3DXVECTOR3(m_HPinfo.Width / 2.0f + 45, m_HPinfo.Height / 2.0 + 50, 0),
			&D3DXVECTOR3(WIDTH / 2.0f - 50, m_EnemyUI_backinfo.Height / 2.0 + 30, 0.6f),
			D3DCOLOR_ARGB(255, 255, 255, 255));




		m_pSprite->End();
	}
}

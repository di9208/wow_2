#include "stdafx.h"
#include "cPlayerInFo.h"

#include <sstream>

std::string Convert(float number) {
	std::ostringstream buff;
	buff << number;
	return buff.str();
}


cPlayerInFo::cPlayerInFo()
	:m_pTexture(NULL)
	, m_pSprite(NULL)
{

}


cPlayerInFo::~cPlayerInFo()
{
	SAFE_RELEASE(m_pFont);
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pSprite);
}

void cPlayerInFo::Setup()
{
	SetFont();
	SetUI();
	PlayerInFo.HP = 100;
	PlayerInFo.MP = 70;
}

void cPlayerInFo::Update(condition* pCondition)
{
	if (g_pKeyManager->isOnceKeyDown('Q'))
	{
		if (PlayerInFo.HP>0)PlayerInFo.HP -= 10;
		*pCondition = HURT;
	}
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
}

void cPlayerInFo::RenderUI()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	RECT rc;
	//SetRect(&rc, 300, 200, 500, 340);
	m_pSprite->Draw(m_pTexture,
		NULL, //&rc,
		&D3DXVECTOR3(m_stImageInfo.Width / 2.0f, m_stImageInfo.Height / 2.0, 0),
		&D3DXVECTOR3(WIDTH/2.0f, HEIGHT- m_stImageInfo.Height, 0.5f),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pSprite->End();
}

void cPlayerInFo::RenderFont()
{
	if (m_pFont)
	{
		std::string sText = Convert(PlayerInFo.HP);
		//sprintf(sText, "%f", (PlayerInFo.HP));

		RECT rc;
		SetRect(&rc, 100, 100, 300, 200);

		m_pFont->DrawText(NULL,
			sText.c_str(),
			sText.length(),
			&rc,
			DT_LEFT | DT_TOP | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 0));
	}
}

void cPlayerInFo::Render()
{
	//RenderUI();
	//RenderFont();
}

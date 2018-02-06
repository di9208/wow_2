#include "stdafx.h"
#include "cUIButton.h"


cUIButton::cUIButton()
	: m_eButtonState(BTN_UP)
	, m_pDelegate(NULL)
{
}


cUIButton::~cUIButton()
{
	/*for (int i = 0; i < BTN_NUM; i++)
	{
		SAFE_RELEASE(m_pTextures[i]);
	}*/
}

void cUIButton::SetTexture(IN char * szUp, IN char * szOver, IN char * szDown)
{
	D3DXIMAGE_INFO	stImageInfo;
	std::string sUp = std::string(szUp);
	std::string sOver = std::string(szOver);
	std::string sDown = std::string(szDown);
	m_pTextures[BTN_UP] = g_pTextureManager->GetTexture(sUp, &stImageInfo);
	m_pTextures[BTN_OVER] = g_pTextureManager->GetTexture(sOver, &stImageInfo);
	m_pTextures[BTN_DOWN] = g_pTextureManager->GetTexture(sDown, &stImageInfo);
	m_stSize.nWidth = stImageInfo.Width;
	m_stSize.nHeight = stImageInfo.Height;
}

void cUIButton::SetTexture(IN std::string keyname, IN char * szUp, IN char * szOver, IN char * szDown)
{
	D3DXIMAGE_INFO	stImageInfo;
	std::string sUp = std::string(szUp);
	std::string sOver = std::string(szOver);
	std::string sDown = std::string(szDown);
	std::string sKeyup = keyname + std::string("up");
	std::string sKeyover = keyname + std::string("over");
	std::string sKeydown = keyname + std::string("down");
	m_pTextures[BTN_UP] = g_pTextureManager->GetTexture(sKeyup, sUp, &stImageInfo);
	m_pTextures[BTN_OVER] = g_pTextureManager->GetTexture(sKeyover, sOver, &stImageInfo);
	m_pTextures[BTN_DOWN] = g_pTextureManager->GetTexture(sKeydown, sDown, &stImageInfo);
	m_stSize.nWidth = stImageInfo.Width;
	m_stSize.nHeight = stImageInfo.Height;
}

void cUIButton::Update()
{
	if (m_isHidden) return;
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	RECT rc;
	SetRect(&rc,
		(int)m_matWorld._41,
		(int)m_matWorld._42,
		(int)m_matWorld._41 + m_stSize.nWidth,
		(int)m_matWorld._42 + m_stSize.nHeight);

	if (PtInRect(&rc, pt))
	{
		if (GetKeyState(VK_LBUTTON)& 0x8000)
		{
			if (m_eButtonState == BTN_OVER)
			{
				m_eButtonState = BTN_DOWN;
				m_isclick = true;
			}
		}
		else
		{
			if (m_eButtonState == BTN_DOWN)
			{
				if (m_pDelegate)
				{
					m_pDelegate->OnClick(this);
				}
			}
			m_eButtonState = BTN_OVER;
		}
	}
	else
	{
		m_eButtonState = BTN_UP;
		m_isclick = false;
	}

	cUIObject::Update();
}

void cUIButton::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden) return;

	pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pSprite->SetTransform(&m_matWorld);
	/*RECT rc;*/
	pSprite->Draw(m_pTextures[m_eButtonState],
		NULL, //&rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	pSprite->End();

	cUIObject::Render(pSprite);
}

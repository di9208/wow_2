#include "stdafx.h"
#include "cUIText.h"


cUIText::cUIText()
	: m_dwDrawTextFormat(DT_TOP | DT_LEFT)
	, m_dwTextColor(D3DCOLOR_XRGB(0, 0, 0))
	, m_eFontType(cFontManager::FT_DEFAULT)
{
}


cUIText::~cUIText()
{
}

void cUIText::Setup(std::string write)
{
	m_sText = write;
}

void cUIText::SetupText(std::string write, ST_SIZE write_size, cFontManager::eFontType fonttype, D3DXCOLOR color)
{
	m_sText = write;
	m_stSize = write_size;
	m_dwTextColor = color;
	m_eFontType = fonttype;
}

void cUIText::Render(LPD3DXSPRITE pSprite)
{
	if (!m_isHidden) return;

	LPD3DXFONT pFont = g_pFontManager->GetFont(m_eFontType);

	RECT rc;
	SetRect(&rc, (int)m_matWorld._41,
		(int)m_matWorld._42,
		(int)m_matWorld._41 + m_stSize.nWidth,
		(int)m_matWorld._42 + m_stSize.nHeight);

	pFont->DrawText(NULL, m_sText.c_str(),
		m_sText.length(),
		&rc,
		m_dwDrawTextFormat,
		m_dwTextColor);

	cUIObject::Render(pSprite);
}

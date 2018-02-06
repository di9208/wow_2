#include "stdafx.h"
#include "cUIText.h"


cUIText::cUIText()
	: m_dwDrawTextFormat(DT_TOP | DT_LEFT)
	, m_dwTextColor(D3DCOLOR_XRGB(192, 0, 0))
	, m_eFontType(cFontManager::FT_DEFAULT)
{
}


cUIText::~cUIText()
{
}

void cUIText::setTex(std::string text)
{
	m_sText = text;
}

void cUIText::Render(LPD3DXSPRITE pSprite)
{
	LPD3DXFONT pFont = g_pFontManager->GetFont(m_eFontType);
	g_pFontManager->FT_DEFAULT;
	RECT rc;
	/*SetRect(&rc, (int)m_matWorld._41,
		(int)m_matWorld._42,
		(int)m_matWorld._41 + m_stSize.nWidth,
		(int)m_matWorld._42 + m_stSize.nHeight);*/
	SetRect(&rc, 0,
		0,
		1200,
		100);
	pFont->DrawText(NULL, m_sText.c_str(),
		m_sText.length(),
		&rc,
		m_dwDrawTextFormat,
		m_dwTextColor);

	cUIObject::Render(pSprite);
}

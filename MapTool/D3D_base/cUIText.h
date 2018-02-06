#pragma once
#include "cUIObject.h"

class cUIText : public cUIObject
{
protected:
	std::string m_sText;
	cFontManager::eFontType m_eFontType;
	DWORD		m_dwDrawTextFormat;
	D3DCOLOR	m_dwTextColor;

public:
	cUIText();
	virtual ~cUIText();
	void setTex(std::string text);
	virtual void Render(LPD3DXSPRITE pSprite);
};


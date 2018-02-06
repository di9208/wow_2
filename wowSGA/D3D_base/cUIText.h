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

	virtual void Setup(std::string write);
	void SetupText(std::string write, ST_SIZE write_size, cFontManager::eFontType fonttype, D3DXCOLOR color);
	virtual void Render(LPD3DXSPRITE pSprite);
};


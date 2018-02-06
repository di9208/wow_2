#pragma once
#include "cUnit.h"

class cPlayerInFo
{
private:
	TagUnit						PlayerInFo;
	LPD3DXFONT					m_pFont;

	LPD3DXSPRITE				m_pSprite;
	D3DXIMAGE_INFO				m_stImageInfo;
	LPDIRECT3DTEXTURE9	m_pTexture;
public:
	cPlayerInFo();
	~cPlayerInFo();

	void Setup();
	void Update(condition* pCondition);

	void SetFont();
	void SetUI();
	void RenderUI();
	void RenderFont();
	void Render();
};

#pragma once
#include "cUnit.h"

class cOBB;
class cSkinnedMesh;

class cPlayerInFo
{
private:
	TagUnit						PlayerInFo;
	LPD3DXFONT					m_pFont;

	LPD3DXSPRITE				m_pSprite;
	D3DXIMAGE_INFO				m_stImageInfo;
	LPDIRECT3DTEXTURE9			m_pTexture;
	SYNTHESIZE(cOBB*, m_playerOBB, playerOBB);

	D3DXIMAGE_INFO				m_PlayerUI_backinfo;
	LPDIRECT3DTEXTURE9			m_PlayerUI_back;
	D3DXIMAGE_INFO				m_PlayerUI_info;
	LPDIRECT3DTEXTURE9			m_PlayerUI;
public:
	cPlayerInFo();
	~cPlayerInFo();

	void Setup(cSkinnedMesh* playerSkinned, D3DXMATRIXA16* playerWorld);
	void Update(condition* pCondition, D3DXMATRIXA16* pMatWorld);

	void SetFont();
	void SetUI();
	void RenderUI();
	void RenderFont();
	void Render(D3DXMATRIXA16* playerWorld, D3DXMATRIXA16* pMatWorld);

	void Collsion(cOBB* EnemyBox);
};

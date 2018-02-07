#pragma once
#include "cUnit.h"
#include "item_class.h"

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

	D3DXIMAGE_INFO				m_statusUI_info;
	LPDIRECT3DTEXTURE9			m_statusUI;
	bool						m_status;

	POINT Pt;
	struct status
	{
		RECT					m_statsRC;
		bool					check;
		std::string				information;
		float					m_x;
		float					m_y;
	};

	status						m_stats[5];
	D3DXIMAGE_INFO				m_Dummy_info;
	LPDIRECT3DTEXTURE9			m_Dummy;
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
	void RenderPlayerStat();

	void Collsion(cOBB* EnemyBox);
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void setRC();
};

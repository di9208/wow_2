#pragma once
#include "cUnit.h"
#include "shop_TEST_CLASS.h"

class cOBB;
class cSkinnedMesh;
class item_class;
class inventory;
class cUIImage;

class cPlayerInFo
{
private:
	TagUnit						PlayerInFo;
	LPD3DXFONT					m_pFont;
	LPD3DXFONT					m_systemFont;

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
		D3DXIMAGE_INFO			m_EquipUI_info;
		LPDIRECT3DTEXTURE9		m_EquipUI;
		RECT					m_statsRC;
		bool					check;
		std::string				information;
		float					m_x;
		float					m_y;
	};

	cUIImage* item_slot[5];
	status						m_stats_UI[5];			//������ �̹���
	D3DXIMAGE_INFO				m_stats_info[5];	//��Ƶ��̹���
	LPDIRECT3DTEXTURE9			m_stats[5];


	status						m_skill_UI[5];	//������ �̹���

												/*
												0�� �Ϲݰ���
												1�� �������
												2�� �극�� �Ǵ� ��ȿ
												3�� ������
												*/

	D3DXIMAGE_INFO				m_Dummy_info;
	LPDIRECT3DTEXTURE9			m_Dummy;

	D3DXIMAGE_INFO				m_HP_info;
	LPDIRECT3DTEXTURE9			m_HP;

	int ax;

	std::vector<item_class*> player_Equite_vector;
	LPD3DXSPRITE UI_sprite;
public:
	cPlayerInFo();
	~cPlayerInFo();

	void Setup(cSkinnedMesh* playerSkinned, D3DXMATRIXA16* playerWorld);
	void Update(condition* pCondition, D3DXMATRIXA16* pMatWorld);

	void SetFont();
	void SetUI();
	void RenderUI();
	void RenderFont();
	void RenderFontSysytem();
	void Render(D3DXMATRIXA16* playerWorld, D3DXMATRIXA16* pMatWorld);
	void RenderPlayerStat();

	void Collsion(cOBB* EnemyBox);
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void setRC();
	void getItem(shop_TEST_CLASS* iven_item);
	void setting_EQUIT_UI();
};

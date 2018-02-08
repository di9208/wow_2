#pragma once
#include "cUnit.h"
class cEnemyPicking
{
	D3DXIMAGE_INFO				m_EnemyUI_backinfo;
	LPDIRECT3DTEXTURE9			m_EnemyUI_back;
	LPD3DXSPRITE				m_pSprite;
	D3DXIMAGE_INFO				m_EnemyUI_info;
	LPDIRECT3DTEXTURE9			m_EnemyUI;
	D3DXIMAGE_INFO				m_EnemyIcon_info;
	LPDIRECT3DTEXTURE9			m_EnemyIcon;

	SYNTHESIZE(bool, m_UiOn, UiOn);

	//hp¹Ù
	LPD3DXFONT					m_HpFont;
	D3DXIMAGE_INFO				m_HPinfo;
	LPDIRECT3DTEXTURE9			m_HP;
	float							m_HPint;
	float							m_MaxHPint;
public:
	cEnemyPicking();
	~cEnemyPicking();

	void Setup();
	void Update(MONSTER_KIND monster);
	void Render();
	void SetFont();
	void SetUI();

	void RenderFont();

	void HPset(float hp, float maxHp);

	void setUI(bool check) { m_UiOn = check; }
};


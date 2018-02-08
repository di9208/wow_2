#pragma once
#include "cUnit.h"
class cPlayerSkill
{
	struct status
	{
		D3DXIMAGE_INFO			m_EquipUI_info;
		LPDIRECT3DTEXTURE9		m_EquipUI;
		RECT					m_statsRC;
		bool					check;
		std::string				information;
		float					m_x;
		float					m_y;
		int						alpha;
	};
	status						m_coolTime_UI[5];
	LPD3DXSPRITE				m_pSprite;
	float cool_time[5];
public:
	cPlayerSkill();
	~cPlayerSkill();

	void Setup();
	void Update(condition* pCondition, bool animCheck);
	void combo(condition* pCondition, bool animCheck);
	void Render();

	void SetupUI();
	void RenderUI();
};


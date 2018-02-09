#include "stdafx.h"
#include "cPlayerSkill.h"


cPlayerSkill::cPlayerSkill()
	:m_pSprite(NULL)
{
	for (int i = 0; i < 5; i++)
	{
		cool_time[i] = 0;
		m_coolTime_UI[i].m_EquipUI = NULL;
	}
}


cPlayerSkill::~cPlayerSkill()
{
	for (int i = 0; i < 5; i++)
	{
		SAFE_RELEASE(m_coolTime_UI[i].m_EquipUI);
	}
	SAFE_RELEASE(m_pSprite);
}

void cPlayerSkill::Setup()
{
	SetupUI();
}

void cPlayerSkill::Update(condition * pCondition, bool animCheck)
{
	if (g_pKeyManager->isOnceKeyDown('1'))
	{
		if (*pCondition == IDLE || *pCondition == RUN || *pCondition == BACKWALK)
		{
			if (cool_time[0] + 1.5f<g_pTimeManager->GetLastUpdateTime() || cool_time[0] == 0)			//ÄðÅ¸ÀÓ 1.5ÃÊ
			{
				*pCondition = ATTACK;
				cool_time[0] = g_pTimeManager->GetLastUpdateTime();
				m_coolTime_UI[0].check = true;
				m_coolTime_UI[0].alpha = 200;
			}
		}
	}
	if (m_coolTime_UI[0].check == true)
	{
		if (cool_time[0] + 1.5f < g_pTimeManager->GetLastUpdateTime())			//ÄðÅ¸ÀÓ 1.5ÃÊ
		{
			m_coolTime_UI[0].check = false;
		}
		else
		{
			float time_alpha = 200;
			time_alpha = time_alpha - ((g_pTimeManager->GetLastUpdateTime() - cool_time[0]) / 1.5f) * 200;
			m_coolTime_UI[0].alpha = time_alpha;
		}
	}
	if (g_pKeyManager->isOnceKeyDown('2'))
	{
		if (*pCondition == IDLE || *pCondition == RUN || *pCondition == BACKWALK)
		{
			if (cool_time[1] + 2.0f < g_pTimeManager->GetLastUpdateTime())			//ÄðÅ¸ÀÓ 4.0ÃÊ
			{
				*pCondition = SKILL_2;
				cool_time[1] = g_pTimeManager->GetLastUpdateTime();
				m_coolTime_UI[1].check = true;
				m_coolTime_UI[1].alpha = 200;
			}
		}
	}	
	if (m_coolTime_UI[1].check == true)
	{
		if (cool_time[1] + 2.0f < g_pTimeManager->GetLastUpdateTime())			//ÄðÅ¸ÀÓ 1.5ÃÊ
		{
			m_coolTime_UI[1].check = false;
		}
		else
		{
			float time_alpha = 200;
			time_alpha = time_alpha - ((g_pTimeManager->GetLastUpdateTime() - cool_time[1]) / 2.0f) * 200;
			m_coolTime_UI[1].alpha = time_alpha;
		}
	}
	if (g_pKeyManager->isOnceKeyDown('3'))
	{
		if (*pCondition == IDLE || *pCondition == RUN || *pCondition == BACKWALK)
		{
			if (cool_time[2] + 4.0f < g_pTimeManager->GetLastUpdateTime())			//ÄðÅ¸ÀÓ 5.0ÃÊ
			{
				*pCondition = BREATH;
				cool_time[2] = g_pTimeManager->GetLastUpdateTime();
				m_coolTime_UI[2].check = true;
				m_coolTime_UI[2].alpha = 200;
			}
		}
	}
	if (m_coolTime_UI[2].check == true)
	{
		if (cool_time[2] + 4.0f < g_pTimeManager->GetLastUpdateTime())			//ÄðÅ¸ÀÓ 1.5ÃÊ
		{
			m_coolTime_UI[2].check = false;
		}
		else
		{
			float time_alpha = 200;
			time_alpha = time_alpha - ((g_pTimeManager->GetLastUpdateTime() - cool_time[2]) / 4.0f) * 200;
			m_coolTime_UI[2].alpha = time_alpha;
		}
	}
	if (g_pKeyManager->isOnceKeyDown('4'))
	{
		if (*pCondition == IDLE || *pCondition == RUN || *pCondition == BACKWALK)
		{
			if (cool_time[3] + 4.5f < g_pTimeManager->GetLastUpdateTime())			//ÄðÅ¸ÀÓ 4.5ÃÊ
			{
				*pCondition = BUFF;
				cool_time[3] = g_pTimeManager->GetLastUpdateTime();
				m_coolTime_UI[3].check = true;
				m_coolTime_UI[3].alpha = 200;
			}
		}
	}
	if (m_coolTime_UI[3].check == true)
	{
		if (cool_time[3] + 4.5f < g_pTimeManager->GetLastUpdateTime())			//ÄðÅ¸ÀÓ 1.5ÃÊ
		{
			m_coolTime_UI[3].check = false;
		}
		else
		{
			float time_alpha = 200;
			time_alpha = time_alpha - ((g_pTimeManager->GetLastUpdateTime() - cool_time[3]) / 4.5f) * 200;
			m_coolTime_UI[3].alpha = time_alpha;
		}
	}

	combo(pCondition, animCheck);
}

void cPlayerSkill::combo(condition* pCondition, bool animCheck)
{
	if (*pCondition == SKILL_2 || *pCondition == SKILL_1)
	{
		if (animCheck)
		{
			*pCondition = SKILL_3;
		}
	}
}

void cPlayerSkill::Render()
{
	RenderUI();
}

void cPlayerSkill::SetupUI()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	for (int i = 0; i < 5; i++)
	{
		ZeroMemory(&m_coolTime_UI[i].m_EquipUI_info, sizeof(D3DXIMAGE_INFO));

		D3DXCreateTextureFromFileEx(
			g_pD3DDevice,
			"player/BLACK.png",
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			0,
			&m_coolTime_UI[i].m_EquipUI_info,
			NULL,
			&m_coolTime_UI[i].m_EquipUI);

		m_coolTime_UI[i].m_x = 140 + i * 55;
		m_coolTime_UI[i].m_y = 800;
		m_coolTime_UI[i].check = false;
		m_coolTime_UI[i].alpha = 0;
		m_coolTime_UI[i].m_statsRC =
		{ (int)m_coolTime_UI[i].m_x,
			(int)m_coolTime_UI[i].m_y,
			(int)m_coolTime_UI[i].m_x + 46,
			(int)m_coolTime_UI[i].m_y + 46 };
	}
}

void cPlayerSkill::RenderUI()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	for (int i = 0; i < 5; i++)
	{
		m_pSprite->Draw(m_coolTime_UI[i].m_EquipUI,
			NULL, //&rc,
			&D3DXVECTOR3(
				m_coolTime_UI[i].m_EquipUI_info.Width / 2.0f,
				m_coolTime_UI[i].m_EquipUI_info.Width / 2.0,
				0),
			&D3DXVECTOR3(
				m_coolTime_UI[i].m_EquipUI_info.Width / 2.0f + m_coolTime_UI[i].m_x,
				m_coolTime_UI[i].m_EquipUI_info.Width / 2.0f + m_coolTime_UI[i].m_y,
				0.0f),
			D3DCOLOR_ARGB(m_coolTime_UI[i].alpha, 255, 255, 255));
	}
	m_pSprite->End();
}


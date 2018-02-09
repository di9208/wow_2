#include "stdafx.h"
#include "cCharacter.h"
#include "iMap.h"


cCharacter::cCharacter()
	: m_fRotY(0.0f)
	, speed(0.0f)
	, speed_max(0.1f)
	, m_chractor_condition(IDLE)
	, m_jump(0.07f)
	, m_gravity(0.000f)
	, m_gSpeed(0.000000000000f)
	, Ani_Check(false)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cCharacter::~cCharacter()
{
}

void cCharacter::Setup()
{
}

void cCharacter::Update(iMap* pMap, bool animCheck)
{
	setSpeed();
	Jump(animCheck);
	Roll(animCheck);
	if (GetKeyState('A') & 0x8000)
	{
		if (m_chractor_condition != DEATH)m_fRotY -= 0.1f;
	}
	if (GetKeyState('D') & 0x8000)
	{
		if (m_chractor_condition != DEATH)	m_fRotY += 0.1f;
	}
	D3DXVECTOR3 vTempPos = m_vPos;
	if (g_pKeyManager->isStayKeyDown('W'))
	{
		if (m_chractor_condition == RUN
			|| m_chractor_condition == IDLE
			|| m_chractor_condition == JUMP_ING
			|| m_chractor_condition == BACKWALK)
		{
			if (m_chractor_condition == BACKWALK)speed = 0;
			vTempPos = m_vPos + (m_vDir * speed);

			if (m_chractor_condition != JUMP_ING)
			{
				m_chractor_condition = RUN;
			}
		}
	}
	if (g_pKeyManager->isStayKeyDown('S'))
	{
		//if (m_chractor_condition == RUN)
		{
			vTempPos = m_vPos - (m_vDir * speed);
			m_chractor_condition = BACKWALK;
		}
	}

	if (!(g_pKeyManager->isStayKeyDown('W'))
		&& !(g_pKeyManager->isStayKeyDown('S')))
	{
		if (m_chractor_condition == RUN)
			m_chractor_condition = IDLE;
		if (m_chractor_condition == BACKWALK)
			m_chractor_condition = IDLE;
	}

	D3DXMATRIXA16 matR, matT;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixRotationY(&matR, m_fRotY);
	m_vDir = D3DXVECTOR3(1, 0, 0);
	D3DXVec3TransformNormal(&m_vDir, &m_vDir, &matR);

	if (pMap)
	{
		if (pMap->GetHeight(vTempPos.x, vTempPos.y, vTempPos.z))
		{
			if (m_chractor_condition != JUMP_START && m_chractor_condition != JUMP_ING)
			{
				m_vPos = vTempPos;
			}
			else
			{
				m_vPos.x = vTempPos.x;
				m_vPos.z = vTempPos.z;
			}
		}
	}
	else
	{
		m_vPos = vTempPos;
	}

	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
	m_matWorld = matR * matT;
}

void cCharacter::setSpeed()
{
	if (m_chractor_condition == RUN || m_chractor_condition == BACKWALK)
	{
		if (speed < speed_max)
		{
			speed = 0.08f;
		}
	}
	if (m_chractor_condition == ROLL_START)
	{
		if (speed < speed_max)
		{
			speed = 0.15f;
		}
	}
	if (m_chractor_condition == IDLE)
	{
		speed = 0;
	}
}

void cCharacter::Jump(bool animCheck)
{
	static float jump_Position = 0.0f;
	static float dummy = 0.0f;
	if (g_pKeyManager->isOnceKeyDown(VK_SPACE))
	{
		if (m_chractor_condition != ROLL_START && m_chractor_condition != ROLL && m_chractor_condition != ROLL_END)
		{
			m_chractor_condition = JUMP_ING;
			jump_Position = m_vPos.y;

			m_jump = (0.08f);
			m_gravity = (0.0000f);
			m_gSpeed = (0.0003f);
		}
	}
	if (m_chractor_condition == JUMP_UP)
	{
		if (animCheck)
		{
			m_chractor_condition = JUMP_ING;
		}
	}
	else if (m_chractor_condition == JUMP_ING)
	{
		if (!animCheck &&m_vPos.y >= 0)
		{
			m_vPos.y += m_jump;
			m_jump += m_gravity;
			m_gravity -= m_gSpeed;
		}
		else
		{
			m_vPos.y = jump_Position;
			m_chractor_condition = JUMP_DOWN;
		}
	}
}

void cCharacter::Roll(bool animCheck)
{

	if (g_pKeyManager->isOnceKeyDown(VK_SHIFT))
	{
		if (m_chractor_condition != JUMP_UP && m_chractor_condition != JUMP_ING && m_chractor_condition != JUMP_DOWN)
		{
			m_chractor_condition = ROLL_START;
		}

	}
	if (m_chractor_condition == ROLL_START)
	{
		m_vPos = m_vPos + (m_vDir * speed);
		if (animCheck)
		{
			m_chractor_condition = ROLL;
		}
	}
	else if (m_chractor_condition == ROLL)
	{
		m_vPos = m_vPos + (m_vDir * speed);
		if (animCheck)
		{
			m_chractor_condition = ROLL_END;
		}
	}
	else if (m_chractor_condition == ROLL_END)
	{
		m_vPos = m_vPos + (m_vDir * speed*0.5f);
		if (animCheck)
		{
			m_chractor_condition = IDLE;
		}
	}


}

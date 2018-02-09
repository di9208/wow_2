#pragma once
#include "cGameObject.h"
#include "cUnit.h"
class iMap;
class cCharacter : public cGameObject
{
protected:
	SYNTHESIZE(float, m_fRotY, RotY);
	D3DXMATRIXA16	m_matWorld;
	float			speed;
	float			speed_max;
	//condition		m_chractor_condition;
	SYNTHESIZE(condition, m_chractor_condition, chractor_condition);
	E_BOSS_STATE	m_boss_state;

	float			m_jump;
	float			m_gravity;
	float			m_gSpeed;
	bool			Ani_Check;
public:
	cCharacter();
	~cCharacter();

	void Setup();
	void Update(iMap* pMap = NULL, bool animCheck = NULL);

	void setSpeed();
	void Jump(bool animCheck);
	void Roll(bool animCheck);
};


#pragma once
#include "cCharacter.h"
#include "cUnit.h"

class cPlayerAniController;
class cPlayerSkill;
class cWeapon;
class cPlayerInFo;
class cOBB;

class cPlayer :public cCharacter
{
	cPlayerAniController*	m_playerAnimController;
	cPlayerSkill*			m_playerSkill;
	cWeapon*				m_Weapon;
	cPlayerInFo*			m_playerInFo;

	D3DXVECTOR3				m_EnemyPos;
	cOBB*					m_playerOBB;
	cOBB*					m_weaponOBB;
public:
	cPlayer();
	~cPlayer();

	void Setup();
	void Update();
	void Render();

	void setEnemyPos(D3DXVECTOR3 EnemyPos) { m_EnemyPos = EnemyPos; }
};


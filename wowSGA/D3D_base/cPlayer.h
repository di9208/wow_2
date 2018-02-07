#pragma once
#include "cCharacter.h"
#include "cUnit.h"

class cPlayerAniController;
class cPlayerSkill;
class cWeapon;
class cPlayerInFo;
class cPlayerPicking;
class cOBB;
class cEnemyPicking;
class iMap;

class cPlayer :public cCharacter
{
	cPlayerAniController*	m_playerAnimController;
	cPlayerSkill*			m_playerSkill;
	cPlayerPicking*			m_playerPicking;
	cWeapon*				m_Weapon;
	//cPlayerInFo*			m_playerInFo;
	SYNTHESIZE(cPlayerInFo*, m_playerInFo, playerInFo);
	cEnemyPicking*			m_EnemyPicking;
	D3DXVECTOR3				m_EnemyPos;
	

public:
	cPlayer();
	~cPlayer();

	void Setup();
	void Update(iMap* m_map);
	void Render();

	void Collsion(cOBB* EnemyBox);

	void setEnemyPos(D3DXVECTOR3 EnemyPos) { m_EnemyPos = EnemyPos; }
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void SetPlayerPick(std::vector<ST_PC_VERTEX> m_vecVertex);
};

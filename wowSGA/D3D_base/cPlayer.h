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
class shop_TEST_CLASS;

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
	
	int weaponNUM;
	int WeaponNUMCheck;
public:
	cPlayer();
	~cPlayer();

	void Setup(float x, float y, float z);
	void Update(iMap* m_map);
	void Render();
	void UpdatePicking(MONSTER_KIND monster);
	void Collsion(cOBB* EnemyBox,float Damage);

	void setEnemyPos(D3DXVECTOR3 EnemyPos) { m_EnemyPos = EnemyPos; }
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void SetPlayerPick(std::vector<ST_PC_VERTEX> m_vecVertex);
	void connet_shop_test_class(shop_TEST_CLASS* connect_shop_test);

	void setUI(bool check);
	void setHp(int hp, int maxHP);

	cOBB* getWeapon();
	void checkUI();
	float getPlayerATK();
};

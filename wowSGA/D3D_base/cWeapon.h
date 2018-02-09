#pragma once

class cSkinnedMesh;
class cOBB;
class cWeapon
{
	//cSkinnedMesh*		m_pSkinnedMesh;
	SYNTHESIZE(cSkinnedMesh*, m_pSkinnedMesh, SkinnedMesh);
	D3DXMATRIXA16*		m_charactor;
	ST_BONE*			m_hand;
	ST_BONE*			m_handle;

	
	SYNTHESIZE_REF(int, m_WeaponNum, WeaponNum);
	SYNTHESIZE_REF(D3DXMATRIXA16, m_World, World);
	SYNTHESIZE_REF(D3DXMATRIXA16, m_WorldTM, WorldTM);
	SYNTHESIZE_REF(D3DXMATRIXA16, m_player, player);
	float				m_changeTime;

	//cOBB*				m_weaponOBB;
	SYNTHESIZE(cOBB*, m_weaponOBB, weaponOBB);

	int					m_hp;
	LPD3DXFONT					m_pFont;
	SYNTHESIZE(bool, m_Equip, Equip);
public:
	cWeapon();
	~cWeapon();

	void Setup(D3DXMATRIXA16* c_charactor, ST_BONE* c_hand, D3DXMATRIXA16* player);
	void Update(D3DXMATRIXA16* world, ST_BONE* c_hand);
	void Render(D3DXMATRIXA16* world);
	void Change_Weapon(int n);

	void collsion(cOBB * EnemyBox);

	void SetFont();
	void RenderFont();

	void change(int n);
};


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

	int					m_WeaponNum;
	SYNTHESIZE_REF(D3DXMATRIXA16, m_World, World);
	float				m_changeTime;

	cOBB*				m_weaponOBB;
public:
	cWeapon();
	~cWeapon();

	void Setup(D3DXMATRIXA16* c_charactor, ST_BONE* c_hand);
	void Update(D3DXMATRIXA16* world);
	void Render();
	void Change_Weapon();
};


#pragma once
#include "cUnit.h"

class cEnemySkinnedMesh;

class cBoneGuardFel : public cUnit
{
	struct EnemySkinnedMesh
	{
		cEnemySkinnedMesh* m;
		MONSTER_STATUS	ENUM_MONSTER;
		MONSTER_KIND	ENUM_MONSTER_KIND;

		TagUnit		t;
		float		MaxHP;
		float		fx;
		float		fy;
		float		fz;
		float		distance;
		float		range;
		float		MaxRange;
		bool		death;
		bool		bi;
		int			time;
		int			deathTime;

		//몬스터 인식용
		D3DXVECTOR3		m_vPos;
		D3DXVECTOR3		m_vDir;
		D3DXVECTOR3		sum;

		//스피어
		D3DMATERIAL9				m_stMtlNone;
		D3DMATERIAL9				m_stMtlPicked;
		LPD3DXMESH					m_pMeshSphere;
		ST_SPHERE					m_Sphere;

		//원거리 공격용 스피어
		ST_SPHERE					m_rangeSphere;
		LPD3DXMESH					m_rangeMesh;
		D3DXVECTOR3					m_rangeDir;
		D3DXVECTOR3					m_rangeSum;
		float						m_rangeDistance;
		D3DXMATRIXA16				m_matR;
		bool						m_rangeCheck;

		//몬스터 아이템 ㅠ 0ㅠ
		ST_MONSTER_ITEM						m_StItemSprite;
		ST_MONSTER_ITEM						m_StInvectory;
		std::vector<ST_MONSTER_ITEM>		m_ItemSprite;
	};
private:
	SYNTHESIZE(std::vector<EnemySkinnedMesh>, m_vecSkinnedMesh, vecSkinnedMesh);
	D3DXMATRIXA16	m_matWorld;
	

	//몬스터 스탯
	int			nXAlpha;
	int			nCount;
	int			nAnimation;

	POINT		m_ptPrevMouse;
	ST_SPHERE	bInsic;

	bool		m_pSkillOn;
	D3DXVECTOR3	m_vPlayerPos;
	//폰트
	LPD3DXFONT	m_pFont;

	//아이템창 ui
	LPD3DXSPRITE				m_pSprite;
	LPD3DXSPRITE				m_pInvectory;

public:
	void SetUp();
	void Update();
	void Render();

	void MonsterInsic(D3DXVECTOR3 d);

	void addMonster(float x, float y, float z);
	void HarmDamage(int Damage, size_t i);
	void MonsterAI(size_t i);
	void MonsterStatus(size_t i);
	void MonsterDeath(size_t i);

	void SetupUI(size_t i, size_t j);
	void RenderUI(size_t i, size_t j, int x, int y, int sizeX, int sizeY);

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void SphereRender(size_t i);


	cBoneGuardFel();
	~cBoneGuardFel();
};
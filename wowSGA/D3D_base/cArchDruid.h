#pragma once
#include "cUnit.h"

class iMap;
class cSkinnedMesh;

class cArchDruid : public cUnit
{
	struct EnemySkinnedMesh
	{
		cSkinnedMesh* m;
		MONSTER_STATUS	ENUM_MONSTER;
		MONSTER_KIND	ENUM_MONSTER_KIND;

		TagUnit		t;
		float		MaxHP;
		float		distance;
		float		range;
		float		MaxRange;
		bool		death;
		int			attackSpeed;
		int			time;
		int			deathTime;
		int			attackTime;
		int			termCount;
		int			RunCount;

		//���� �νĿ�
		D3DXVECTOR3					m_vPos;
		D3DXVECTOR3					m_vDir;
		D3DXVECTOR3					sum;

		//���Ǿ�
		D3DMATERIAL9				m_stMtlNone;
		D3DMATERIAL9				m_stMtlPicked;
		LPD3DXMESH					m_pMeshSphere;
		ST_SPHERE					m_Sphere;

		//���Ÿ� ���ݿ� ���Ǿ�
		ST_SPHERE					m_rangeSphere;
		LPD3DXMESH					m_rangeMesh;
		D3DXVECTOR3					m_rangeDir;
		D3DXVECTOR3					m_rangeSum;
		float						m_rangeDistance;
		D3DXMATRIXA16				m_matR;
		bool						m_rangeCheck;

		//���� ������ �� 0��
		ST_MONSTER_ITEM						m_StItemSprite;
		ST_MONSTER_ITEM						m_StInvectory;
		std::vector<ST_MONSTER_ITEM>		m_ItemSprite;

		D3DXMATRIXA16 matWorld;
	};
private:
	SYNTHESIZE(std::vector<EnemySkinnedMesh>, m_vecSkinnedMesh, vecSkinnedMesh);
	EnemySkinnedMesh Monster;

	//���� ����
	int			nXAlpha;
	int			nCount;
	int			nAnimation;

	POINT		m_ptPrevMouse;
	ST_SPHERE	bInsic;

	bool		m_pSkillOn;
	D3DXVECTOR3	m_vPlayerPos;
	//��Ʈ
	LPD3DXFONT	m_pFont;

	//������â ui
	LPD3DXSPRITE				m_pSprite;
	LPD3DXSPRITE				m_pInvectory;

public:
	void SetUp();
	void Update(iMap* pMap);
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
	void RangeSphere(size_t i);

	void matUpdate(size_t i, iMap* map);

	cArchDruid();
	~cArchDruid();
};
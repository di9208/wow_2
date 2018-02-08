#pragma once
#include "cUnit.h"
#include "cParticle.h"
#include "cMonsterParticle.h"
#include "cEnemyHitEffect.h"

class iMap;
class cSkinnedMesh;
class cOBB;

class cBoneSpider : public cUnit
{
	struct EnemySkinnedMesh
	{
		cParticle*		Particle;
		cSkinnedMesh*	m;
		cOBB*			MonsterOBB;
		D3DXMATRIXA16	matWorld;
		MONSTER_STATUS	ENUM_MONSTER;
		MONSTER_KIND	ENUM_MONSTER_KIND;

		TagUnit		t;
		float		MaxHP;
		float		distance;
		float		range;
		float		MaxRange;
		int			attackSpeed;
		bool		death;
		int			time;
		int			deathTime;
		int			attackTime;
		int			termCount;
		int			RunCount;


		//몬스터 인식용
		D3DXVECTOR3					m_vPos;
		D3DXVECTOR3					m_vDir;
		D3DXVECTOR3					sum;

		//스피어
		D3DMATERIAL9				m_stMtlNone;
		D3DMATERIAL9				m_stMtlPicked;
		LPD3DXMESH					m_pMeshSphere;
		ST_SPHERE					m_Sphere;

		//몬스터 아이템 ㅠ 0ㅠ
		ST_MONSTER_ITEM						m_StItemSprite;
		ST_MONSTER_ITEM						m_StInvectory;
		std::vector<ST_MONSTER_ITEM>		m_ItemSprite;

		D3DXMATRIXA16 matRT;
	};
private:
	SYNTHESIZE(std::vector<EnemySkinnedMesh>, m_vecSkinnedMesh, vecSkinnedMesh);
	D3DXMATRIXA16 matWorld;



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

	void SphereRender(size_t i, D3DXMATRIXA16& matWorld);

	void matUpdate(size_t i, iMap* map);

	int getVectorSize() { return m_vecSkinnedMesh.size(); }
	cOBB* getOBB(int i) { return m_vecSkinnedMesh[i].MonsterOBB; }

	cBoneSpider();
	~cBoneSpider();
};
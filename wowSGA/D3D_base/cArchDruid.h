#pragma once
#include "cUnit.h"
#include "cParticle.h"
#include "cMonsterParticle.h"
#include "cEnemyHitEffect.h"
#include "cUIObject.h"
#include "cMonsterBombParticle.h"

class iMap;
class cSkinnedMesh;
class cOBB;

class cArchDruid : public cUnit
{
	cUIObject* Root;
	struct EnemySkinnedMesh
	{
		cSkinnedMesh*	m;
		cSkinnedMesh*	b;
		cParticle*		Particle;
		D3DXMATRIXA16	matWorld;
		cOBB*			MonsterOBB;
		cOBB*			MonsterAttackOBB;
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
		int			m_bombcount;
		bool		m_bomb;

		bool		Damage;
		float		Damage_time;
		float		TimeCheck;
		bool		Hurt;

		//몬스터 인식용
		D3DXVECTOR3					m_vPos;
		D3DXVECTOR3					m_vDir;
		D3DXVECTOR3					sum;

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
		cParticle*					cBombParticle;

		//몬스터 아이템 ㅠ 0ㅠ
		ST_MONSTER_ITEM						m_StItemSprite;
		ST_MONSTER_ITEM						m_StInvectory;
		std::vector<ST_MONSTER_ITEM>		m_ItemSprite;

		D3DXMATRIXA16 matRT;
		D3DXMATRIXA16 matRTAttack;
	};
private:
	SYNTHESIZE(std::vector<EnemySkinnedMesh>, m_vecSkinnedMesh, vecSkinnedMesh);
	EnemySkinnedMesh Monster;

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
	LPD3DXFONT	m_pFont2;
	size_t		m_MonsterItem;

	//아이템창 ui
	LPD3DXSPRITE				m_pSprite;
	LPD3DXSPRITE				m_pInvectory;

public:
	void SetUp();
	void Update(iMap* pMap);
	void Render();

	void MonsterInsic(D3DXVECTOR3 d);

	void addMonster(float x, float y, float z);
	void addMonster(std::string key, float x, float y, float z);

	void HarmDamage(int Damage, size_t i);
	void MonsterAI(size_t i);
	void MonsterStatus(size_t i);
	void MonsterDeath(size_t i);

	void SetupUI(size_t j);
	void RenderUI(size_t i);

	void SphereRender(size_t i);
	void RangeSphere(size_t i);

	void matUpdate(size_t i, iMap* map);

	D3DXVECTOR3 getOBBCenter(int i);
	float getOBBhalf(int i);

	MONSTER_STATUS getCondition(int i) { return m_vecSkinnedMesh[i].ENUM_MONSTER; }

	void setDamageCheck(int i, bool check) { m_vecSkinnedMesh[i].Damage = check; }
	bool getDamageCheck(int i) { return m_vecSkinnedMesh[i].Damage; }

	void setTimeCheck(int i, bool check) { m_vecSkinnedMesh[i].TimeCheck = check; }
	bool getTimeCheck(int i) { return m_vecSkinnedMesh[i].TimeCheck; }

	void setDamageTimeCheck(int i, float time) { m_vecSkinnedMesh[i].Damage_time = time; }
	float getDamageTimeCheck(int i) { return m_vecSkinnedMesh[i].Damage_time; }

	MONSTER_KIND getMonsterKind() { return m_vecSkinnedMesh[0].ENUM_MONSTER_KIND; }

	float getMonsterHP(int i) { return m_vecSkinnedMesh[i].t.HP; }
	float getMonsterMaxHP(int i) { return m_vecSkinnedMesh[i].MaxHP; }

	//==========================================================================================

	void getWeaponHit(int i, cOBB * PlayerWeapon);
	void setHurt(int i, bool check) { m_vecSkinnedMesh[i].Hurt = check; };


	int getVectorSize() { return m_vecSkinnedMesh.size(); }
	cOBB* getOBB(int i) { return m_vecSkinnedMesh[i].MonsterOBB; }

	cOBB* getBULLET(int i) { return m_vecSkinnedMesh[i].MonsterAttackOBB; }

	cArchDruid();
	~cArchDruid();
};
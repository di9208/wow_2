#pragma once
#include "cUnit.h"
#include "cParticle.h"
#include "cMonsterParticle.h"
#include "cEnemyHitEffect.h"
#include "cUIObject.h"

class iMap;
class cSkinnedMesh;
class cOBB;

class cBoneSpider : public cUnit
{
	cUIObject* Root;
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
	LPD3DXFONT	m_pFont2;

	//아이템창 ui
	LPD3DXSPRITE				m_pSprite;
	LPD3DXSPRITE				m_pInvectory;
	size_t						m_MonsterItem;

	float	attack_time;
	bool	hit_on;
public:
	void SetUp();
	void Update(iMap* pMap);
	void Render();

	void MonsterInsic(D3DXVECTOR3 d);

	void addMonster(float x, float y, float z);
	void addMonster(std::string key,float x, float y, float z);
	void HarmDamage(int Damage, size_t i);
	void MonsterAI(size_t i);
	void MonsterStatus(size_t i);
	void MonsterDeath(size_t i);

	void SetupUI(size_t j);
	void RenderUI(size_t i);

	void SphereRender(size_t i, D3DXMATRIXA16& matWorld);

	void matUpdate(size_t i, iMap* map);

	int getVectorSize() { return m_vecSkinnedMesh.size(); }
	cOBB* getOBB(int i) { return m_vecSkinnedMesh[i].MonsterOBB; }
	float getATK(int i) { return m_vecSkinnedMesh[i].t.ATK; }

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

	void getWeaponHit(int i, cOBB * PlayerWeapon,float Damage);
	void setHurt(int i, bool check) { m_vecSkinnedMesh[i].Hurt = check; };

	cBoneSpider();
	~cBoneSpider();
};
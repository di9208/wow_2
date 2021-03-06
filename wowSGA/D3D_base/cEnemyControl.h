#pragma once
#include "cEnemyManager.h"

#include "cParticle.h"
#include "cArthasPaticle.h"
#include "cRagPaticle.h"
#include "cUnit.h"

class cBoneSpider;
class cArchDruid;
class cLightningWorg;
class cBossAniController;
class cBossSkill;
class cBossRagController;
class iMap;
class cOBB;

struct stBoss
{
	TagUnit					stat;
	MONSTER_KIND			kind;
	D3DXVECTOR3				m_vPos;
	D3DXVECTOR3				m_vDir;
	D3DXVECTOR3				pb;					// 플레이어와 보스 거리
	float					dist;
	int						count;				// 보스접근후 모션쓰기위한 카운트
	bool					chk;				// 접근했는지 안했는지
	bool					chkDist;			// 거리관련 불값
	bool					Hurt;
	E_BOSS_STATE			e_boss_state;		// 보스 상태
	E_BOSS_RAG_STATE		e_boss_rag_state;	// 라그 상태
	cParticle*				particle;			// 리치왕 파티클

	stBoss()
		: m_vDir(1, 0, 0)
		, m_vPos(0, 0, 0)
		, pb(0, 0, 0)
		, dist(0.f)
		, count(0)
		, chkDist(false)
		, particle(NULL)
	{}											//구조체 초기화
};
struct stBoss_rag
{
	TagUnit					stat;
	MONSTER_KIND			kind;
	D3DXVECTOR3				m_vPos;
	D3DXVECTOR3				m_vDir;
	D3DXVECTOR3				pb;					// 플레이어와 보스 거리
	float					dist;
	int						count;				// 보스접근후 모션쓰기위한 카운트
	bool					chk;				// 접근했는지 안했는지
	E_BOSS_RAG_STATE		e_boss_rag_state;	// 라그 상태

	cParticle*				particle;			// 라그 파티클

	stBoss_rag()
		: m_vDir(1, 0, 0)
		, m_vPos(0, 0, 0)
		, pb(0, 0, 0)
		, dist(0.f)
		, count(0)
		, particle(NULL)
	{}
};

class cEnemyControl : public cEnemyManager
{
private:
	cBoneSpider * m_pSpider;
	cArchDruid*		m_pDruid;
	cLightningWorg*	m_pWorg;

private:
	SYNTHESIZE(std::vector<stBoss>, m_vecBoss, vecBoss);

	stBoss				stBoss1;
	D3DXMATRIXA16		matR;
	//======================================================
	SYNTHESIZE(std::vector<stBoss_rag>, m_vecBoss_rag, vecBoss_rag);
	stBoss_rag			stBoss_rag;
	D3DXMATRIXA16		matragR;

	//보스 거리 조절용 벡터
	D3DXVECTOR3 v;
	//라그나로스 등장
	int a = 0;
	//폰트
	LPD3DXFONT	m_pFont;

	//
	D3DXVECTOR3 dv;
	float	m_fDeathDir;

	float	RAG_attack_time;
	bool	RAG_hit_on;

	float	BOSS_attack_time;
	bool	BOSS_hit_on;
private:
	cBossAniController * m_pBossAniController;
	cBossRagController * m_pBossRagController;
	cBossSkill*			 m_pBossSkill;


	//Picking
	std::vector<ST_SPHERE>	m_vecSphere;
	D3DMATERIAL9			m_stMtlNone;
	D3DMATERIAL9			m_stMtlPicked;
	LPD3DXMESH				m_pMeshSphere;

	//spell
	int						nCount; // spell2 몹소환 카운트
	int						nMonsterX; //소환되는 몹 좌표
	int						nMonsterY; //소환되는 몹 좌표

									   //playerCheck
	D3DXVECTOR3				m_vPlayerPos;

	D3DXMATRIXA16			m_world;
	int						skillDelay; // 플레이어세 붙어서 공격할때 랜덤값
	int						delay1;
	int						delay2;

	bool isboss;
	bool israg;
	SYNTHESIZE(bool, m_Change, Change);

	bool spiderChk;		//몹소환스킬 체크 불값
	bool wolfChk;		//몹소환스킬 체크 불값


public:
	void SetUp(std::vector<tagMon> Monster);
	void Update(D3DXVECTOR3 d, iMap* pMap, std::vector<tagMon> Monster);
	void Render();


	//boss
	void ragSetup(std::vector<tagMon> Monster);
	void BossSetup(std::vector<tagMon> Monster);						//보스 세팅 (x파일 등)
	void BossUpdate(std::vector<tagMon> Monster);						//보스 업데이트 (스킬 등)
	void BossRender();	//렌더
	void ragRender();
	void ragUpdate();

	void BossPlayerCheck();					//플레이어와의 체크
	void BossPlayerRot(D3DXVECTOR3 d);		//플레이어 좌표받아오기
	void BossRagPlayerCheck();				//플레이어와 라그와의 체크
	void BossRagPlayerRot(D3DXVECTOR3 d);   //플레이어 좌표받아오기(라그)
	void Picking();
	void SetupUI();
	void RenderUI();

	//Eenemy
	void SummonsEnemy();
	cEnemyControl();
	~cEnemyControl();
	//-------------------------------------------------------------------------------
	int getWolfVectorSize();
	cOBB* getWolfOBB(int i);
	float getWolfATK(int i);
	MONSTER_STATUS getWolfCondition(int i);

	void setWolfDamageCheck(int i, bool check);
	bool getWolfDamageCheck(int i);

	void setWolfTimeCheck(int i, bool check);
	bool getWolfTimeCheck(int i);

	void  setWolfDamageTimeCheck(int i, float time);
	float getWolfDamageTimeCheck(int i);
	//===============================================================================
	int getSpiderVectorSize();
	cOBB* getSpiderOBB(int i);
	float getSpiderATK(int i);
	MONSTER_STATUS getSpiderCondition(int i);

	void setSpiderDamageCheck(int i, bool check);
	bool getSpiderDamageCheck(int i);

	void setSpiderTimeCheck(int i, bool check);
	bool getSpiderTimeCheck(int i);

	void  setSpiderDamageTimeCheck(int i, float time);
	float getSpiderDamageTimeCheck(int i);
	//===========================================================
	int getDruidVectorSize();
	cOBB* getDruidOBB(int i);
	cOBB* getBulletOBB(int i);
	float getDruidATK(int i);
	MONSTER_STATUS getDruidCondition(int i);

	void setDruidDamageCheck(int i, bool check);
	bool getDruidDamageCheck(int i);

	void setDruidTimeCheck(int i, bool check);
	bool getDruidTimeCheck(int i);

	void  setDruidDamageTimeCheck(int i, float time);
	float getDruidDamageTimeCheck(int i);
	//=========================================================================
	cOBB* getBossOBB();
	E_BOSS_STATE getBossCondition();
	MONSTER_KIND getArthasKind() { return m_vecBoss[0].kind; }
	float getMonsterHP() { return m_vecBoss[0].stat.HP; }
	float getMonsterMaxHP() { return m_vecBoss[0].stat.Max_HP; }
	//-----------------------------------------------------
	cOBB* getRagOBB();
	E_BOSS_RAG_STATE getRagCondition();
	MONSTER_KIND getRagKind() { return m_vecBoss_rag[0].kind; }
	float getRagHP() { return m_vecBoss_rag[0].stat.HP; }
	float getRagMaxHP() { return m_vecBoss_rag[0].stat.Max_HP; }
	//==================================================================
	std::vector<Enemy_Sphere> getALLEnemyCenter();

	//무기충돌----------------------------------------------------
	void WeaponHit(cOBB * PlayerWeapon, float damage);
	void getWeaponHitBOSS(cOBB * PlayerWeapon, float damage);
	void WeaponHit_AFTER(cOBB * PlayerWeapon);
	void getWeaponHitBOSS_After();

	void getWeaponHitRag(cOBB * PlayerWeapon, float damage);
	void getWeaponHitRag_After();

	float Boss_ATK();
	float Rag_ATK();

	void setState(E_BOSS_STATE s) { m_vecBoss[0].e_boss_state = s; }


};


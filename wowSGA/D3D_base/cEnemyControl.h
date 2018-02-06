#pragma once
#include "cEnemyManager.h"

class cBoneSpider;
class cArchDruid;
class cBoneGuardFel;
class cBossAniController;
class cBossSkill;
class cBossRagController;

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
	E_BOSS_STATE			e_boss_state;		// 보스 상태
	E_BOSS_RAG_STATE		e_boss_rag_state;	// 라그 상태
	stBoss()
		: m_vDir(1, 0, 0)
		, m_vPos(0, 0, 0)
		, pb(0, 0, 0)
		, dist(0.f)
		, count(0)
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
	stBoss_rag()
		: m_vDir(1, 0, 0)
		, m_vPos(0, 0, 0)
		, pb(0, 0, 0)
		, dist(0.f)
		, count(0)
	{}
};

class cEnemyControl : public cEnemyManager
{
private:
	cBoneSpider*	m_pSpider;
	cArchDruid*		m_pDruid;
	cBoneGuardFel*	m_pGuardFel;

private:
	SYNTHESIZE(std::vector<stBoss>, m_vecBoss, vecBoss);
	stBoss				stBoss;
	D3DXMATRIXA16		matR;
	//======================================================
	SYNTHESIZE(std::vector<stBoss_rag>, m_vecBoss_rag, vecBoss_rag);
	stBoss_rag			stBoss_rag;
	D3DXMATRIXA16		matragR;

	//폰트
	LPD3DXFONT	m_pFont;

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

public:
	void SetUp();
	void Update(D3DXVECTOR3 d);
	void Render();


	//boss
	void BossSetup();						//보스 세팅 (x파일 등)
	void BossUpdate();						//보스 업데이트 (스킬 등)
	void BossRender();						//렌더
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
};


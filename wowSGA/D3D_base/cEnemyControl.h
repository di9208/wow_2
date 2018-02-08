#pragma once
#include "cEnemyManager.h"

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
	D3DXVECTOR3				pb;					// �÷��̾�� ���� �Ÿ�
	float					dist;
	int						count;				// ���������� ��Ǿ������� ī��Ʈ
	bool					chk;				// �����ߴ��� ���ߴ���
	bool					chkDist;			// �Ÿ����� �Ұ�
	E_BOSS_STATE			e_boss_state;		// ���� ����
	E_BOSS_RAG_STATE		e_boss_rag_state;	// ��� ����
	stBoss()
		: m_vDir(1, 0, 0)
		, m_vPos(0, 0, 0)
		, pb(0, 0, 0)
		, dist(0.f)
		, count(0)
		, chkDist(false)
	{}											//����ü �ʱ�ȭ
};
struct stBoss_rag
{
	TagUnit					stat;
	MONSTER_KIND			kind;
	D3DXVECTOR3				m_vPos;
	D3DXVECTOR3				m_vDir;
	D3DXVECTOR3				pb;					// �÷��̾�� ���� �Ÿ�
	float					dist;
	int						count;				// ���������� ��Ǿ������� ī��Ʈ
	bool					chk;				// �����ߴ��� ���ߴ���
	E_BOSS_RAG_STATE		e_boss_rag_state;	// ��� ����
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
	cLightningWorg*	m_pWorg;

private:
	SYNTHESIZE(std::vector<stBoss>, m_vecBoss, vecBoss);
	stBoss				stBoss;
	D3DXMATRIXA16		matR;
	//======================================================
	SYNTHESIZE(std::vector<stBoss_rag>, m_vecBoss_rag, vecBoss_rag);
	stBoss_rag			stBoss_rag;
	D3DXMATRIXA16		matragR;
	
	//���� �Ÿ� ������ ����
	D3DXVECTOR3 v;
	//��׳��ν� ����
	int a = 0;
	//��Ʈ
	LPD3DXFONT	m_pFont;

	//
	D3DXVECTOR3 dv;
	float	m_fDeathDir;
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
	int						nCount; // spell2 ����ȯ ī��Ʈ
	int						nMonsterX; //��ȯ�Ǵ� �� ��ǥ
	int						nMonsterY; //��ȯ�Ǵ� �� ��ǥ

	//playerCheck
	D3DXVECTOR3				m_vPlayerPos;

	D3DXMATRIXA16			m_world;
	int						skillDelay; // �÷��̾ �پ �����Ҷ� ������
	int						delay1;
	int						delay2;

public:
	void SetUp();
	void Update(D3DXVECTOR3 d, iMap* pMap);
	void Render();


	//boss
	void BossSetup();						//���� ���� (x���� ��)
	void BossUpdate();						//���� ������Ʈ (��ų ��)
	void BossRender();						//����
	void BossPlayerCheck();					//�÷��̾���� üũ
	void BossPlayerRot(D3DXVECTOR3 d);		//�÷��̾� ��ǥ�޾ƿ���
	void BossRagPlayerCheck();				//�÷��̾�� ��׿��� üũ
	void BossRagPlayerRot(D3DXVECTOR3 d);   //�÷��̾� ��ǥ�޾ƿ���(���)
	void Picking();
	void SetupUI();
	void RenderUI();

	//Eenemy
	void SummonsEnemy();
	cEnemyControl();
	~cEnemyControl();

	int getWolfVectorSize();
	cOBB* getWolfOBB(int i);

	int getSpiderVectorSize();
	cOBB* getSpiderOBB(int i);

	cOBB* getBossOBB();
};


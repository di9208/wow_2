#include "stdafx.h"
#include "cEnemyControl.h"
#include "cBoneSpider.h"
#include "cArchDruid.h"
#include "cLightningWorg.h"
#include "cBossAniController.h"
#include "cBossSkill.h"
#include "cBossRagController.h"
#include "iMap.h"
#include "cOBB.h"
cEnemyControl::cEnemyControl()
	: m_pSpider(NULL)
	, m_pDruid(NULL)
	, m_pWorg(NULL)
	, m_pBossAniController(NULL)
	, m_pBossSkill(NULL)
	, nCount(0)
	, m_vPlayerPos(0, 0, 0)
	, skillDelay(30)
	, delay1(0)
	, delay2(0)
	, m_pFont(NULL)
	, m_pBossRagController(NULL)
{
	D3DXMatrixIdentity(&m_world);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matragR);
}

cEnemyControl::~cEnemyControl()
{
	SAFE_RELEASE(m_pFont);
	SAFE_DELETE(m_pSpider);
	SAFE_DELETE(m_pDruid);
	SAFE_DELETE(m_pWorg);
	SAFE_DELETE(m_pBossAniController);
	SAFE_DELETE(m_pBossRagController);
	SAFE_DELETE(m_pBossSkill);
	SAFE_DELETE(m_vecBoss[0].particle);
}

int cEnemyControl::getWolfVectorSize()
{
	return m_pWorg->getVectorSize();
}

cOBB * cEnemyControl::getWolfOBB(int i)
{
	return m_pWorg->getOBB(i);
}

MONSTER_STATUS cEnemyControl::getWolfCondition(int i)
{
	return m_pWorg->getCondition(i);
}

void cEnemyControl::setWolfDamageCheck(int i, bool check)
{
	m_pWorg->setDamageCheck(i, check);
}

bool cEnemyControl::getWolfDamageCheck(int i)
{
	return m_pWorg->getDamageCheck(i);
}

void cEnemyControl::setWolfTimeCheck(int i, bool check)
{
	m_pWorg->setTimeCheck(i, check);
}

bool cEnemyControl::getWolfTimeCheck(int i)
{
	return m_pWorg->getTimeCheck(i);
}

void cEnemyControl::setWolfDamageTimeCheck(int i, float time)
{
	m_pWorg->setDamageTimeCheck(i, time);
}

float cEnemyControl::getWolfDamageTimeCheck(int i)
{
	return m_pWorg->getDamageTimeCheck(i);
}

int cEnemyControl::getSpiderVectorSize()
{
	return m_pSpider->getVectorSize();
}

cOBB * cEnemyControl::getSpiderOBB(int i)
{
	return m_pSpider->getOBB(i);
}

MONSTER_STATUS cEnemyControl::getSpiderCondition(int i)
{
	return m_pSpider->getCondition(i);
}

void cEnemyControl::setSpiderDamageCheck(int i, bool check)
{
	m_pSpider->setDamageCheck(i, check);
}

bool cEnemyControl::getSpiderDamageCheck(int i)
{
	return m_pSpider->getDamageCheck(i);
}

void cEnemyControl::setSpiderTimeCheck(int i, bool check)
{
	m_pSpider->setTimeCheck(i, check);
}

bool cEnemyControl::getSpiderTimeCheck(int i)
{
	return m_pSpider->getTimeCheck(i);
}

void cEnemyControl::setSpiderDamageTimeCheck(int i, float time)
{
	m_pSpider->setDamageTimeCheck(i, time);
}

float cEnemyControl::getSpiderDamageTimeCheck(int i)
{
	return m_pSpider->getDamageTimeCheck(i);
}

cOBB * cEnemyControl::getBossOBB()
{
	return m_pBossAniController->getOBB();
}

E_BOSS_STATE cEnemyControl::getBossCondition()
{
	return m_pBossAniController->getCondition();
}

std::vector<Enemy_Sphere> cEnemyControl::getALLEnemyCenter()
{
	std::vector<Enemy_Sphere> ALL_Mon;
	Enemy_Sphere m_sphre;
	for (int i = 0; i < getWolfVectorSize(); i++)
	{
		m_sphre.vCenter = m_pWorg->getOBBCenter(i);
		m_sphre.bIsPicked = false;
		m_sphre.fRadius = m_pWorg->getOBBhalf(i);
		m_sphre.Mons = m_pWorg->getMonsterKind();
		m_sphre.HP = m_pWorg->getMonsterHP(i);
		m_sphre.Max_HP = m_pWorg->getMonsterMaxHP(i);
		ALL_Mon.push_back(m_sphre);
	}
	for (int i = 0; i < getSpiderVectorSize(); i++)
	{
		m_sphre.vCenter = m_pSpider->getOBBCenter(i);
		m_sphre.bIsPicked = false;
		m_sphre.fRadius = m_pSpider->getOBBhalf(i);
		m_sphre.Mons = m_pSpider->getMonsterKind();
		m_sphre.HP = m_pSpider->getMonsterHP(i);
		m_sphre.Max_HP = m_pSpider->getMonsterMaxHP(i);
		ALL_Mon.push_back(m_sphre);
	}
	m_sphre.vCenter = m_pBossAniController->getOBBCenter();
	m_sphre.bIsPicked = false;
	m_sphre.fRadius = m_pBossAniController->getOBBhalf();
	m_sphre.Mons = getArthasKind();
	m_sphre.HP = getMonsterHP();
	m_sphre.Max_HP = getMonsterMaxHP();
	ALL_Mon.push_back(m_sphre);
	return ALL_Mon;
}

void cEnemyControl::WeaponHit(cOBB * PlayerWeapon)
{
	for (int i = 0; i < getSpiderVectorSize(); i++)
	{
		m_pSpider->getWeaponHit(i, PlayerWeapon);
	}
	for (int i = 0; i < getWolfVectorSize(); i++)
	{
		m_pWorg->getWeaponHit(i, PlayerWeapon);
	}
	getWeaponHitBOSS(PlayerWeapon);
}

void cEnemyControl::getWeaponHitBOSS(cOBB * PlayerWeapon)
{
	if (PlayerWeapon)
	{
		if (PlayerWeapon->getCheck(0).x != -431602080 && PlayerWeapon->getCheck(0).x != -431602080)
		{
			if (PlayerWeapon->IsCollision(m_pBossAniController->GetBossOBB(), PlayerWeapon))
			{
				m_vecBoss[0].stat.HP -= 100;
			}
		}
	}
}


void cEnemyControl::SetUp() {
	m_pSpider = new cBoneSpider;
	//m_pSpider->addMonster(1, 0, 4);

	m_pDruid = new cArchDruid;
	//m_pDruid->addMonster(-4, 0, -4);

	m_pWorg = new cLightningWorg;
	//m_pWorg->addMonster(4, 0, -4);

	if (m_pSpider) m_pSpider->SetUp();
	if (m_pDruid) m_pDruid->SetUp();

	BossSetup();

	D3DXFONT_DESC stFD;
	ZeroMemory(&stFD, sizeof(D3DXFONT_DESC));
	stFD.Height = 50;
	stFD.Width = 25;
	stFD.Weight = FW_MEDIUM;
	stFD.Italic = false;
	stFD.CharSet = DEFAULT_CHARSET;
	stFD.OutputPrecision = OUT_DEFAULT_PRECIS;
	stFD.PitchAndFamily = FF_DONTCARE;

	//strcpy_s(stFD.FaceName, "굴림체");

	AddFontResource("font/umberto.ttf");
	strcpy_s(stFD.FaceName, "umberto");

	D3DXCreateFontIndirect(g_pD3DDevice, &stFD, &m_pFont);

}

void cEnemyControl::Update(D3DXVECTOR3 d, iMap* pMap) {
	BossUpdate();
	BossPlayerRot(d);
	BossRagPlayerRot(d);
	//enemy
	if (m_pSpider) {
		m_pSpider->Update(pMap);
		m_pSpider->MonsterInsic(d);
	}

	if (m_pDruid) {
		m_pDruid->Update(pMap);
		m_pDruid->MonsterInsic(d);
	}

	if (m_pWorg) {
		m_pWorg->Update(pMap);
		m_pWorg->MonsterInsic(d);
	}

	SummonsEnemy();
}

void cEnemyControl::Render() {
	if (m_pSpider) m_pSpider->Render();
	if (m_pDruid) m_pDruid->Render();
	if (m_pWorg) m_pWorg->Render();

	BossRender();
	if (m_pFont)
	{
		char str[128];
		sprintf(str, "bossHP : %f ", m_vecBoss[0].stat.HP);

		std::string sText(str);
		RECT rc;
		SetRect(&rc, 100, 570, 300, 200);

		m_pFont->DrawText(NULL,
			sText.c_str(),
			sText.length(),
			&rc,
			DT_LEFT | DT_TOP | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 255));
	}

}

void cEnemyControl::BossSetup()
{
	m_pBossAniController = new cBossAniController();
	m_pBossAniController->SetUp();

	m_pBossRagController = new cBossRagController();
	m_pBossRagController->SetUp();

	m_pBossSkill = new cBossSkill;
	stBoss		stBoss1;
	stBoss1.count = 0;
	stBoss1.stat.ATK = 100;
	stBoss1.stat.DEF = 20;
	stBoss1.stat.HP = 500;
	stBoss1.chk = false;
	stBoss1.kind = BOSS_ARTHAS;
	stBoss1.e_boss_state = E_BOSS_START;
	stBoss1.particle = new cArthasPaticle(700, 20);
	stBoss1.particle->init("Particle/T_VFX_SWIRL64B_A_CONTRAST2.png");

	m_vecBoss.push_back(stBoss1);


<<<<<<< HEAD
=======
	stBoss.count = 0;
	stBoss.stat.ATK = 100;
	stBoss.stat.DEF = 20;
	stBoss.stat.HP = 500;
	stBoss.stat.Max_HP = 500;
	stBoss.chk = false;
	stBoss.kind = BOSS_ARTHAS;
	stBoss.e_boss_state = E_BOSS_START;
	m_vecBoss.push_back(stBoss);
>>>>>>> e46814df4a297aacb26cf85753cb1b1d29878a3b
	//===============================위가 리치왕, 아래가 라그나로스 스탯//
	stBoss_rag.count = 0;
	stBoss_rag.stat.ATK = 100;
	stBoss_rag.stat.DEF = 20;
	stBoss_rag.stat.HP = 500;
	stBoss_rag.chk = false;
	stBoss_rag.kind = BOSS_RAGNALOS;
	stBoss_rag.e_boss_rag_state = E_BOSS_RAG_STAND;
	m_vecBoss_rag.push_back(stBoss_rag);
}

void cEnemyControl::BossUpdate()
{
	cEnemyManager::Update();

	//리치왕 업데이트
	if (m_pBossAniController)
		m_pBossAniController->Update(&m_vecBoss[0].e_boss_state);

	m_vecBoss[0].particle->update(1.0001f);
	//라그나로스 업데이트
	if (m_pBossRagController)
		m_pBossRagController->Update(&m_vecBoss_rag[0].e_boss_rag_state);

	if (m_pBossSkill)
		m_pBossSkill->Update(&m_vecBoss[0].e_boss_state, &m_vecBoss_rag[0].e_boss_rag_state);

	if (!m_vecBoss[0].chk)
	{
		if (m_vecBoss[0].e_boss_state == E_BOSS_SPELL2)
		{
			nCount++;

			if (nCount > 7)
			{
				nMonsterX = rand() % 15;
				nMonsterY = rand() % 15;
				m_pSpider->addMonster(nMonsterX, 0, nMonsterY);
				nCount = 0;
			}
		}
		/*if (m_vecBoss_rag[0].e_boss_rag_state == E_BOSS_RAG_SPELL)
		{
		nCount++;
		if (nCount > 7)
		{
		nMonsterX = rand() % 15;
		nMonsterY = rand() % 15;
		m_pGuardFel->addMonster(nMonsterX, 0, nMonsterY);
		nCount = 0;
		}
		}*/
		if (m_vecBoss[0].e_boss_state == E_BOSS_SPELL1)
		{
			m_pBossAniController->Skill();
		}
	}


	BossPlayerCheck();

	if (m_vecBoss[0].e_boss_state == E_BOSS_DEATH)
	{

		BossRagPlayerCheck();
	}

	// 체력 테스트
	if (g_pKeyManager->isOnceKeyDown('L'))
	{
		m_vecBoss[0].stat.HP = m_vecBoss[0].stat.HP - 500;
	}
	if (g_pKeyManager->isOnceKeyDown('K'))
	{
		m_vecBoss_rag[0].stat.HP = m_vecBoss_rag[0].stat.HP - 500;
	}
	if (g_pKeyManager->isStayKeyDown(VK_F11))
	{
		m_vecBoss[0].stat.HP -= 10;
	}

	if (m_vecBoss[0].stat.HP <= 0)
	{
		m_vecBoss[0].e_boss_state = E_BOSS_DEATH;
		a++;
	}
	if (m_vecBoss_rag[0].stat.HP <= 0)
	{
		m_vecBoss_rag[0].e_boss_rag_state = E_BOSS_RAG_DEATH;
	}
	if (a == 50)
	{
		m_vecBoss_rag[0].e_boss_rag_state = E_BOSS_RAG_START;
	}
}

void cEnemyControl::BossRender()
{
<<<<<<< HEAD
	/*D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, -5, 0, 0);
	D3DXMATRIXA16 world = (matT);
*/	
	
	D3DXMATRIXA16 matWW;
	if (m_pBossAniController)
		m_pBossAniController->Render(matWW);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWW);
	if(m_vecBoss[0].e_boss_state == E_BOSS_WHIRLWIND && m_vecBoss[0].e_boss_state != E_BOSS_DEATH)
	m_vecBoss[0].particle->render();
	//==============================================

	/*D3DXMATRIXA16 matT2;
	D3DXMatrixTranslation(&matT2, 5, 0, 0);
	D3DXMATRIXA16 world2 =  matT2;*/
	D3DXMATRIXA16 matW2;
	D3DXMatrixIdentity(&matW2);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matW2);
	if (m_pBossRagController && m_vecBoss[0].e_boss_state == E_BOSS_DEATH)
		m_pBossRagController->Render(nullptr);
=======

	/*D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, -5, 0, 0);
	D3DXMATRIXA16 world = (matT);
	*/	D3DXMATRIXA16 matW;
D3DXMatrixIdentity(&matW);
g_pD3DDevice->SetTransform(D3DTS_WORLD, &matW);
if (m_pBossAniController)
m_pBossAniController->Render(nullptr);

//==============================================

/*D3DXMATRIXA16 matT2;
D3DXMatrixTranslation(&matT2, 5, 0, 0);
D3DXMATRIXA16 world2 =  matT2;*/
D3DXMATRIXA16 matW2;
D3DXMatrixIdentity(&matW2);
g_pD3DDevice->SetTransform(D3DTS_WORLD, &matW2);
if (m_pBossRagController && m_vecBoss[0].e_boss_state == E_BOSS_DEATH)
m_pBossRagController->Render(nullptr);
>>>>>>> e46814df4a297aacb26cf85753cb1b1d29878a3b
}

void cEnemyControl::BossPlayerCheck()
{
	if (m_vecBoss[0].e_boss_state != E_BOSS_DEATH && m_vecBoss[0].e_boss_state != E_BOSS_START)
	{
		m_vecBoss[0].m_vPos = m_pBossAniController->GetvBossPos();

		D3DXVECTOR3 Dir;
		float Distance;
		D3DXVec3Normalize(&Dir, &(m_vPlayerPos - m_vecBoss[0].m_vPos));
		Distance = fabs(D3DXVec3Length(&(m_vPlayerPos - m_vecBoss[0].m_vPos)));

		if (Distance <= 7.0f && Distance >= 2.0f &&
			(m_vecBoss[0].e_boss_state == E_BOSS_WALK ||
				m_vecBoss[0].e_boss_state == E_BOSS_STAND))
		{
			m_vecBoss[0].count++;
			if (m_vecBoss[0].count > 80)
			{
				m_vecBoss[0].chk = true;
				m_vecBoss[0].e_boss_state = E_BOSS_WALK;
				if (m_vecBoss[0].count> 100)
					m_vecBoss[0].m_vPos = m_vecBoss[0].m_vPos + (Dir*0.05f);
			}

			m_pBossAniController->SetvBossPos(m_vecBoss[0].m_vPos);
			m_pBossAniController->SetBossDir(Dir);
		}

		if (Distance > 7.0f)
		{
			m_vecBoss[0].e_boss_state = E_BOSS_STAND;
		}

		if (Distance < 2.0f &&
			(m_vecBoss[0].e_boss_state != E_BOSS_ATT &&
				m_vecBoss[0].e_boss_state != E_BOSS_ATT2))
		{
			skillDelay++;

			if (skillDelay > 40)
			{
				delay1 = rand() % 15;
				delay2 = rand() % 15;
				if (delay1 > 1 && delay1 < 7)
				{
					m_vecBoss[0].count += 5;
					if (m_vecBoss[0].count > 5)
					{
						m_vecBoss[0].e_boss_state = E_BOSS_ATT;
						m_vecBoss[0].count = 0;
					}
					if (m_vecBoss[0].stat.HP <= 50)
					{
						m_vecBoss[0].e_boss_state = E_BOSS_WHIRLWIND;
					}
					m_vecBoss[0].chk = false;
				}
				if (delay2 > 8 && delay2 < 15)
				{
					m_vecBoss[0].count += 5;
					if (m_vecBoss[0].count > 6)
					{
						m_vecBoss[0].e_boss_state = E_BOSS_ATT2;
					}
					if (m_vecBoss[0].stat.HP <= 100)
					{
						m_vecBoss[0].e_boss_state = E_BOSS_SPELL2;
						m_vecBoss[0].count = 0;
					}
					m_vecBoss[0].chk = false;
				}
				if (m_vecBoss[0].stat.HP <= 0)
				{
					m_vecBoss[0].e_boss_state = E_BOSS_DEATH;
					D3DXVec3Normalize(&dv, &(m_vPlayerPos - m_vecBoss[0].m_vPos));
					m_vecBoss[0].chk = false;
					return;
				}
				skillDelay = 0;
			}
		}

	}
	/*if (m_vecBoss[0].e_boss_state == E_BOSS_DEATH)
	{
	m_pBossAniController->SetBossDir(dv);
	}*/
	//if (m_vPlayerPos != D3DXVECTOR3(0, 0, 0) && m_vecBoss[0].e_boss_state != E_BOSS_DEATH)
	//{
	//	for (size_t i = 0; i < m_vecBoss.size(); i++)
	//	{
	//		m_vecBoss[i].m_vPos = m_pBossAniController->GetvBossPos();
	//		
	//		
	//		m_vecBoss[i].pb = m_vPlayerPos - m_vecBoss[i].m_vPos;
	//		m_vecBoss[i].dist = fabs(D3DXVec3Length(&m_vecBoss[i].pb));
	//		D3DXVECTOR3 vDir = m_vPlayerPos - m_vecBoss[i].m_vPos;

	//		//vDir.y = m_vecBoss[i].m_vDir.y = 0.f;

	//		D3DXVec3Normalize(&vDir, &vDir);

	//		if (m_vecBoss[i].dist <= 7.f)
	//		{
	//			m_vecBoss[i].count++;
	//			if (m_vecBoss[i].count > 100)
	//			{
	//				m_vecBoss[i].chk = true;	
	//				
	//				m_vecBoss[i].e_boss_state = E_BOSS_WALK;
	//			}
	//		}
	//		else
	//		{
	//			if (m_vecBoss[i].chk)
	//			{
	//				D3DXVec3Normalize(&v, &m_vecBoss[i].pb);
	//			}
	//			m_vecBoss[i].chk = false;
	//			//m_vecBoss[i].chkDist = false;
	//		}
	//		if (!m_vecBoss[i].chk && m_vecBoss[i].dist > 7.f)
	//		{
	//			//if (m_vecBoss[i].chkDist)
	//			{
	//				m_pBossAniController->SetBossDir(v);
	//				return; 
	//			}

	//		}
	//		if (m_vecBoss[i].chk)
	//		{
	//			//if (!m_vecBoss[i].chk) return;

	//			//m_vecBoss[i].chkDist = true;
	//			D3DXMATRIXA16 matT, matR;
	//			D3DXMatrixIdentity(&matT);
	//			D3DXMatrixIdentity(&matR);

	//			
	//			//D3DXVec3Normalize(&m_vecBoss[i].m_vDir, &m_vecBoss[i].m_vDir);

	//			//float fDot = D3DXVec3Dot(&vDir, &m_vecBoss[i].m_vDir);

	//			if (m_vecBoss[i].dist <= 2.f)
	//			{
	//				m_vecBoss[i].count = 0;
	//				skillDelay++;
	//				if (skillDelay > 5)
	//				{
	//					delay1 = rand() % 15;
	//					delay2 = rand() % 15;
	//					if (delay1 > 1 && delay1 < 7)
	//					{
	//						m_vecBoss[i].e_boss_state = E_BOSS_ATT;
	//						if (m_vecBoss[i].stat.HP <= 50)
	//						{
	//							m_vecBoss[i].e_boss_state = E_BOSS_WHIRLWIND;
	//						}
	//						m_vecBoss[i].chk = false;
	//					}
	//					if (delay2 > 8 && delay2 < 15)
	//					{
	//						m_vecBoss[i].e_boss_state = E_BOSS_ATT2;
	//						if (m_vecBoss[i].stat.HP <= 100)
	//						{
	//							m_vecBoss[i].e_boss_state = E_BOSS_SPELL2;
	//						}
	//						m_vecBoss[i].chk = false;
	//					}
	//					skillDelay = 0;
	//				}
	//				return;

	//			}
	//			else
	//			{
	//				m_vecBoss[i].m_vPos = m_vecBoss[i].m_vPos +(vDir * 0.1f);
	//				m_pBossAniController->SetvBossPos(m_vecBoss[i].m_vPos);
	//			/*	if (fDot <= 0.95f)
	//				{
	//					D3DXVECTOR3 vCross;
	//					D3DXVec3Cross(&vCross, &m_vecBoss[i].m_vDir, &vDir);
	//					D3DXVec3Normalize(&vCross, &vCross);

	//					if (vCross.y > 0.f)
	//					{
	//						D3DXMATRIXA16 matR;
	//						D3DXMatrixIdentity(&matR);
	//						D3DXMatrixRotationY(&matR, 1.f);
	//						D3DXVec3TransformNormal(&m_vecBoss[i].m_vDir, &m_vecBoss[i].m_vDir, &matR);
	//					}
	//					else
	//					{
	//						D3DXMATRIXA16 matR;
	//						D3DXMatrixIdentity(&matR);
	//						D3DXMatrixRotationY(&matR, -1.f);
	//						D3DXVec3TransformNormal(&m_vecBoss[i].m_vDir, &m_vecBoss[i].m_vDir, &matR);
	//					}
	//				}
	//				else
	//				{
	//					m_vecBoss[i].m_vDir = vDir;
	//				}*/

	//			}

	//			m_pBossAniController->SetBossDir(vDir);
	//		}

	//		//D3DXVECTOR3 boss_playerPos;
	//		//boss_playerPos = m_vPlayerPos - m_vecBoss[i].m_vPos;
	//		//D3DXVec3Normalize(&boss_playerPos, &boss_playerPos);
	//		

	//		//D3DXVec3TransformNormal(&m_vecBoss[i].m_vDir, &m_vecBoss[i].m_vDir, &matR);

	//	}
	//}
}

void cEnemyControl::BossPlayerRot(D3DXVECTOR3 d)
{
	m_vPlayerPos = d;
}

void cEnemyControl::BossRagPlayerCheck()
{
	//	if (m_vPlayerPos != D3DXVECTOR3(0, 0, 0) && m_vecBoss_rag[0].e_boss_rag_state != E_BOSS_RAG_DEATH)
	//	{
	//		for (size_t i = 0; i < m_vecBoss_rag.size(); i++)
	//		{
	//			m_vecBoss_rag[i].m_vPos = m_pBossRagController->GetvBossPos();
	//			if (m_vPlayerPos < m_vecBoss_rag[i].m_vPos)
	//			{
	//				m_vecBoss_rag[i].pb = m_vecBoss_rag[i].m_vPos - m_vPlayerPos;
	//			}
	//			else
	//			{
	//				m_vecBoss_rag[i].pb = m_vPlayerPos - m_vecBoss_rag[i].m_vPos;
	//				m_vecBoss_rag[i].dist = D3DXVec3Length(&m_vecBoss_rag[i].pb);
	//			}
	//
	//			if (m_vecBoss_rag[i].dist < 5.f)
	//			{
	//				m_vecBoss_rag[i].count++;
	//				if (m_vecBoss_rag[i].count > 100)
	//				{
	//					m_vecBoss_rag[i].chk = true;
	//				}
	//			}
	//			else m_vecBoss_rag[i].chk = false;
	//
	//			if (m_vecBoss_rag[i].chk)
	//			{
	//				//if (!m_vecBoss_rag[i].chk) return;
	//
	//				/*D3DXMATRIXA16 matT, matR;
	//				D3DXMatrixIdentity(&matT);
	//				D3DXMatrixIdentity(&matR);
	//*/
	//				/*D3DXVECTOR3 vDir = m_vPlayerPos - m_vecBoss_rag[i].m_vPos;
	//
	//				vDir.y = m_vecBoss_rag[i].m_vDir.y = 0.f;
	//
	//				D3DXVec3Normalize(&vDir, &vDir);
	//				D3DXVec3Normalize(&m_vecBoss_rag[i].m_vDir, &m_vecBoss_rag[i].m_vDir);
	//
	//				float fDot = D3DXVec3Dot(&vDir, &m_vecBoss_rag[i].m_vDir);*/
	//
	//				if (m_vecBoss_rag[i].dist <= 2.f)
	//				{
	//					m_vecBoss_rag[i].count = 0;
	//					skillDelay++;
	//					if (skillDelay > 5)
	//					{
	//						delay1 = rand() % 15;
	//						delay2 = rand() % 15;
	//						if (delay1 > 1 && delay1 < 7)
	//						{
	//							m_vecBoss_rag[i].e_boss_rag_state = E_BOSS_RAG_ATT;
	//							m_vecBoss_rag[i].chk = false;
	//						}
	//						if (delay2 > 8 && delay2 < 15)
	//						{
	//							m_vecBoss_rag[i].e_boss_rag_state = E_BOSS_RAG_SPELL;
	//							m_vecBoss_rag[i].chk = false;
	//						}
	//						skillDelay = 0;
	//					}
	//					return;
	//
	//				}
	//				/*else
	//				{
	//					m_vecBoss_rag[i].m_vPos += m_vecBoss_rag[i].m_vDir * 0.1f;
	//
	//					if (fDot <= 0.95f)
	//					{
	//						D3DXVECTOR3 vCross;
	//						D3DXVec3Cross(&vCross, &m_vecBoss_rag[i].m_vDir, &vDir);
	//						D3DXVec3Normalize(&vCross, &vCross);
	//
	//						if (vCross.y > 0.f)
	//						{
	//							D3DXMATRIXA16 matR;
	//							D3DXMatrixIdentity(&matR);
	//							D3DXMatrixRotationY(&matR, 1.f);
	//							D3DXVec3TransformNormal(&m_vecBoss_rag[i].m_vDir, &m_vecBoss_rag[i].m_vDir, &matR);
	//						}
	//						else
	//						{
	//							D3DXMATRIXA16 matR;
	//							D3DXMatrixIdentity(&matR);
	//							D3DXMatrixRotationY(&matR, -1.f);
	//							D3DXVec3TransformNormal(&m_vecBoss_rag[i].m_vDir, &m_vecBoss_rag[i].m_vDir, &matR);
	//						}
	//					}
	//					else
	//					{
	//						m_vecBoss_rag[i].m_vDir = vDir;
	//					}
	//				}*/
	//
	//				m_pBossRagController->SetvBossPos(m_vecBoss_rag[i].m_vPos);
	//			}
	//
	//			/*D3DXVECTOR3 boss_playerPos;
	//			boss_playerPos = m_vPlayerPos - m_vecBoss_rag[i].m_vPos;
	//			D3DXVec3Normalize(&boss_playerPos, &boss_playerPos);
	//			m_pBossRagController->SetBossDir(boss_playerPos);*/
	//
	//			//D3DXVec3TransformNormal(&m_vecBoss[i].m_vDir, &m_vecBoss[i].m_vDir, &matR);
	//
	//		}
	//	}

	if (m_vecBoss_rag[0].e_boss_rag_state != E_BOSS_RAG_DEATH && m_vecBoss_rag[0].e_boss_rag_state != E_BOSS_RAG_START)
	{
		m_vecBoss_rag[0].m_vPos = m_pBossRagController->GetvBossPos();

		D3DXVECTOR3 Dir;
		float Distance;
		D3DXVec3Normalize(&Dir, &(m_vPlayerPos - m_vecBoss_rag[0].m_vPos));
		Distance = fabs(D3DXVec3Length(&(m_vPlayerPos - m_vecBoss_rag[0].m_vPos)));
		if (Distance <= 7.0f &&
			m_vecBoss_rag[0].e_boss_rag_state == E_BOSS_RAG_STAND)
		{
			m_vecBoss_rag[0].count++;
			if (m_vecBoss_rag[0].count > 80)
			{
				m_vecBoss_rag[0].chk = true;
			}

			//m_pBossRagController->SetvBossPos(m_vecBoss_rag[0].m_vPos);
			//m_pBossRagController->SetBossDir(Dir);
		}

		if (Distance > 7.0f)
		{
			m_vecBoss_rag[0].e_boss_rag_state = E_BOSS_RAG_STAND;
			m_vecBoss_rag[0].chk = false;
		}

		if (Distance < 5.0f)
		{
			skillDelay++;

			if (skillDelay > 40)
			{
				delay1 = rand() % 15;
				delay2 = rand() % 15;
				if (delay1 > 1 && delay1 < 7)
				{
					m_vecBoss_rag[0].count += 5;
					if (m_vecBoss_rag[0].count > 5)
					{
						m_vecBoss_rag[0].e_boss_rag_state = E_BOSS_RAG_ATT;
						m_vecBoss_rag[0].count = 0;
					}
					if (m_vecBoss_rag[0].stat.HP <= 50)
					{
						m_vecBoss_rag[0].e_boss_rag_state = E_BOSS_RAG_MERGE;
					}
					//m_vecBoss_rag[0].chk = false;
				}
				if (delay2 > 8 && delay2 < 15)
				{
					m_vecBoss_rag[0].count += 5;
					if (m_vecBoss_rag[0].count > 6)
					{
						m_vecBoss_rag[0].e_boss_rag_state = E_BOSS_RAG_SPELL;
					}
					if (m_vecBoss_rag[0].stat.HP <= 100)
					{
						m_vecBoss_rag[0].e_boss_rag_state = E_BOSS_RAG_ATT;
						m_vecBoss_rag[0].count = 0;
					}
					//m_vecBoss_rag[0].chk = false;
				}
				skillDelay = 0;
			}
		}

	}
}

void cEnemyControl::BossRagPlayerRot(D3DXVECTOR3 d)
{
	m_vPlayerPos = d;
}

void cEnemyControl::Picking()
{
}

void cEnemyControl::SetupUI()
{
}

void cEnemyControl::RenderUI()
{
}

void cEnemyControl::SummonsEnemy() {

	if (g_pKeyManager->isOnceKeyDown('X')) {
		int x = rand() % 15;
		int z = rand() % 15;
		m_pSpider->addMonster(x, 0, z);
		m_pDruid->addMonster(-x, 0, -z);
		m_pWorg->addMonster(x, 0, -z);
	}
}
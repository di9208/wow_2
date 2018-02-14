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
	, isboss(false)
	, m_Change(false)
	, israg(false)
	, spiderChk(false)
	, wolfChk(false)
	, RAG_attack_time(0.0f)
	, RAG_hit_on(false)
	, BOSS_attack_time(0.0f)
	, BOSS_hit_on(false)
{
	D3DXMatrixIdentity(&m_world);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matragR);
	g_pSoundManager->Setup();
	g_pSoundManager->addSound("arthas_att", "sound/boss/arthas_att.mp3", true, false);
	g_pSoundManager->addSound("arthas_whirlwind", "sound/boss/arthas_whirlwind.wav", true, false);
	g_pSoundManager->addSound("ragnaros_att", "sound/boss/ragnaros_att.wav", true, false);
	g_pSoundManager->addSound("ragnaros_death", "sound/boss/ragnaros_death.ogg", true, false);
	g_pSoundManager->addSound("ragnaros_start", "sound/boss/ragnaros_start.wav", true, false);
	g_pSoundManager->addSound("arthas_att2", "sound/boss/arthas_att2.mp3", true, false);

	g_pSoundManager->addSound("HAMMER", "player/Sound/HAMMER.mp3", false, false);
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

float cEnemyControl::getWolfATK(int i)
{
	return m_pWorg->getATK(i);
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

float cEnemyControl::getSpiderATK(int i)
{
	return m_pSpider->getATK(i);
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

int cEnemyControl::getDruidVectorSize()
{
	return m_pDruid->getVectorSize();
}

cOBB * cEnemyControl::getDruidOBB(int i)
{
	return m_pDruid->getOBB(i);
}

cOBB * cEnemyControl::getBulletOBB(int i)
{
	return m_pDruid->getBULLET(i);
}

float cEnemyControl::getDruidATK(int i)
{
	return m_pDruid->getATK(i);
}

MONSTER_STATUS cEnemyControl::getDruidCondition(int i)
{
	return m_pDruid->getCondition(i);
}

void cEnemyControl::setDruidDamageCheck(int i, bool check)
{
	m_pDruid->setDamageCheck(i, check);
}

bool cEnemyControl::getDruidDamageCheck(int i)
{
	return m_pDruid->getDamageCheck(i);
}

void cEnemyControl::setDruidTimeCheck(int i, bool check)
{
	m_pDruid->setTimeCheck(i, check);
}

bool cEnemyControl::getDruidTimeCheck(int i)
{
	return m_pDruid->getTimeCheck(i);
}

void cEnemyControl::setDruidDamageTimeCheck(int i, float time)
{
	m_pDruid->setDamageTimeCheck(i, time);
}

float cEnemyControl::getDruidDamageTimeCheck(int i)
{
	return m_pDruid->getDamageTimeCheck(i);
}

cOBB * cEnemyControl::getBossOBB()
{
	return m_pBossAniController->getOBB();
}

E_BOSS_STATE cEnemyControl::getBossCondition()
{
	return m_pBossAniController->getCondition();
}

cOBB * cEnemyControl::getRagOBB()
{
	return m_pBossRagController->getOBB();
}

E_BOSS_RAG_STATE cEnemyControl::getRagCondition()
{
	return m_pBossRagController->getCondition();
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
	for (int i = 0; i < getDruidVectorSize(); i++)
	{
		m_sphre.vCenter = m_pDruid->getOBBCenter(i);
		m_sphre.bIsPicked = false;
		m_sphre.fRadius = m_pDruid->getOBBhalf(i);
		m_sphre.Mons = m_pDruid->getMonsterKind();
		m_sphre.HP = m_pDruid->getMonsterHP(i);
		m_sphre.Max_HP = m_pDruid->getMonsterMaxHP(i);
		ALL_Mon.push_back(m_sphre);
	}
	m_sphre.vCenter = m_pBossAniController->getOBBCenter();
	m_sphre.bIsPicked = false;
	m_sphre.fRadius = m_pBossAniController->getOBBhalf();
	m_sphre.Mons = getArthasKind();
	m_sphre.HP = getMonsterHP();
	m_sphre.Max_HP = getMonsterMaxHP();
	ALL_Mon.push_back(m_sphre);

	m_sphre.vCenter = m_pBossRagController->getOBBCenter();
	m_sphre.bIsPicked = false;
	m_sphre.fRadius = m_pBossRagController->getOBBhalf();
	m_sphre.Mons = getRagKind();
	m_sphre.HP = getRagHP();
	m_sphre.Max_HP = getRagMaxHP();
	ALL_Mon.push_back(m_sphre);
	return ALL_Mon;
}

void cEnemyControl::WeaponHit(cOBB * PlayerWeapon, float damage)
{
	for (int i = 0; i < getSpiderVectorSize(); i++)
	{
		m_pSpider->getWeaponHit(i, PlayerWeapon,damage);
	}
	for (int i = 0; i < getWolfVectorSize(); i++)
	{
		m_pWorg->getWeaponHit(i, PlayerWeapon, damage);
	}
	for (int i = 0; i < getDruidVectorSize(); i++)
	{
		m_pDruid->getWeaponHit(i, PlayerWeapon,damage);
	}
	getWeaponHitBOSS(PlayerWeapon,damage);
	getWeaponHitRag(PlayerWeapon, damage);
}

void cEnemyControl::getWeaponHitBOSS(cOBB * PlayerWeapon,float damage)
{
	if (m_vecBoss[0].stat.Hurt == false)
	{
		if (PlayerWeapon)
		{
			if (PlayerWeapon->getCheck(0).x != -431602080 && PlayerWeapon->getCheck(0).x != -431602080)
			{
				if (PlayerWeapon->IsCollision(m_pBossAniController->GetBossOBB(), PlayerWeapon))
				{
					BOSS_attack_time = g_pTimeManager->GetLastUpdateTime();
					BOSS_hit_on = true;

					m_vecBoss[0].stat.Hurt = true;
				}
			}
		}
	}
	else
	{
		if (BOSS_hit_on)
		{
			if (BOSS_attack_time + 0.5f < g_pTimeManager->GetLastUpdateTime())
			{
				BOSS_hit_on = false;
				g_pSoundManager->play("HAMMER", 2.0f);
				m_vecBoss[0].stat.HP -= damage;
			}
		}
	}
}

void cEnemyControl::WeaponHit_AFTER(cOBB * PlayerWeapon)
{
	for (int i = 0; i < getSpiderVectorSize(); i++)
	{
		m_pSpider->setHurt(i, false);
	}
	for (int i = 0; i < getWolfVectorSize(); i++)
	{
		m_pWorg->setHurt(i, false);
	}
	for (int i = 0; i < getDruidVectorSize(); i++)
	{
		m_pDruid->setHurt(i, false);
	}
	getWeaponHitBOSS_After();
	getWeaponHitRag_After();
}

void cEnemyControl::getWeaponHitBOSS_After()
{
	m_vecBoss[0].stat.Hurt = false;
}

void cEnemyControl::getWeaponHitRag(cOBB * PlayerWeapon, float damage)
{
	if (m_vecBoss_rag[0].stat.Hurt == false)
	{
		if (PlayerWeapon)
		{
			if (PlayerWeapon->getCheck(0).x != -431602080 && PlayerWeapon->getCheck(0).x != -431602080)
			{
				if (PlayerWeapon->IsCollision(m_pBossRagController->getOBB(), PlayerWeapon))
				{
					/*		g_pSoundManager->play("HAMMER", 2.0f);
					m_vecBoss_rag[0].stat.HP -= damage;*/
					RAG_attack_time = g_pTimeManager->GetLastUpdateTime();
					RAG_hit_on = true;
					m_vecBoss_rag[0].stat.Hurt = true;
				}
			}
		}
	}
	else
	{
		if (RAG_hit_on)
		{
			if (RAG_attack_time + 0.5f < g_pTimeManager->GetLastUpdateTime())
			{
				g_pSoundManager->play("HAMMER", 2.0f);
				RAG_hit_on = false;
				m_vecBoss_rag[0].stat.HP -= damage;
			}
		}
	}
}

void cEnemyControl::getWeaponHitRag_After()
{
	m_vecBoss_rag[0].stat.Hurt = false;
}

float cEnemyControl::Boss_ATK()
{
	return m_vecBoss[0].stat.ATK;
}

float cEnemyControl::Rag_ATK()
{
	return m_vecBoss[0].stat.ATK;
}


void cEnemyControl::SetUp(std::vector<tagMon> Monster) {
	
	m_pSpider = new cBoneSpider;
	for (int i = 0; i < Monster.size(); i++)
	{
		if (Monster[i].kind == KIND_SPIDER)
		{
			m_pSpider->addMonster(Monster[i].name, Monster[i].pos.x, Monster[i].pos.y, Monster[i].pos.z);
		}
	}

	m_pDruid = new cArchDruid;
	for (int i = 0; i < Monster.size(); i++)
	{
		if (Monster[i].kind == KIND_DRUID)
		{
			m_pDruid->addMonster(Monster[i].name, Monster[i].pos.x, Monster[i].pos.y, Monster[i].pos.z);
		}
	}

	m_pWorg = new cLightningWorg;
	for (int i = 0; i < Monster.size(); i++)
	{
		if (Monster[i].kind == KIND_WORG)
		{
			m_pWorg->addMonster(Monster[i].name, Monster[i].pos.x, Monster[i].pos.y, Monster[i].pos.z);
		}
	}
	

	if (m_pSpider) m_pSpider->SetUp();
	if (m_pDruid) m_pDruid->SetUp();
	if (m_pWorg) m_pWorg->SetUp();

	for (int i = 0; i < Monster.size(); i++)
	{
		if (Monster[i].kind == KIND_BOSS_ARTHAS)
		{
			isboss = true;
		}
	}
	for (int i = 0; i < Monster.size(); i++)
	{
		if (Monster[i].kind == KIND_BOSS_RAGNALOS)
		{
			israg = true;
		}
	}
	
	BossSetup(Monster);
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

void cEnemyControl::Update(D3DXVECTOR3 d, iMap* pMap, std::vector<tagMon> Monster) {
	if (isboss)
	{
		BossUpdate(Monster);
		BossPlayerRot(d);
		//BossRagPlayerRot(d);
	}
	if (israg)
	{
		ragUpdate();
		BossRagPlayerRot(d);
	}
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
	if (isboss)
	{
		BossRender();
	}
	if (israg)
	{
		ragRender();
	}
	if (m_pFont)
	{
		/*char str[128];
		sprintf(str, "bossHP : %f ", m_vecBoss[0].stat.HP);

		std::string sText(str);
		RECT rc;
		SetRect(&rc, 100, 570, 300, 200);

		m_pFont->DrawText(NULL,
			sText.c_str(),
			sText.length(),
			&rc,
			DT_LEFT | DT_TOP | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 255));*/
	}

}

void cEnemyControl::ragSetup(std::vector<tagMon> Monster)
{
	m_pBossRagController = new cBossRagController();
	m_pBossRagController->SetUp(Monster);

	stBoss_rag.count = 0;
	stBoss_rag.stat.ATK = 100;
	stBoss_rag.stat.DEF = 20;
	stBoss_rag.stat.HP = 1000;
	stBoss_rag.stat.Max_HP = 1000;
	stBoss_rag.chk = false;
	stBoss_rag.kind = KIND_BOSS_RAGNALOS;
	stBoss_rag.e_boss_rag_state = E_BOSS_RAG_STAND;
	stBoss_rag.particle = new cRagPaticle(500, 20);
	stBoss_rag.particle->init("Particle/T_VFX_SWIRL64B_A_CONTRAST2.png");

	m_vecBoss_rag.push_back(stBoss_rag);
}

void cEnemyControl::BossSetup(std::vector<tagMon> Monster)
{
	m_pBossAniController = new cBossAniController();
	m_pBossAniController->SetUp(Monster);


	m_pBossSkill = new cBossSkill;
	stBoss		stBoss1;
	stBoss1.count = 0;
	stBoss1.stat.ATK = 20;
	stBoss1.stat.DEF = 20;
	stBoss1.stat.HP = 500;
	stBoss1.stat.Max_HP = 500;
	stBoss1.chk = false;
	stBoss1.kind = KIND_BOSS_ARTHAS;
	stBoss1.e_boss_state = E_BOSS_START;
	stBoss1.particle = new cArthasPaticle(700, 20);
	stBoss1.particle->init("Particle/T_VFX_SWIRL64B_A_CONTRAST2.png");

	m_vecBoss.push_back(stBoss1);
	ragSetup(Monster);
	//===============================위가 리치왕, 아래가 라그나로스 스탯//
	/*stBoss_rag.count = 0;
	stBoss_rag.stat.ATK = 100;
	stBoss_rag.stat.DEF = 20;
	stBoss_rag.stat.HP = 500;
	stBoss_rag.stat.Max_HP = 500;
	stBoss_rag.chk = false;
	stBoss_rag.kind = KIND_BOSS_RAGNALOS;
	stBoss_rag.e_boss_rag_state = E_BOSS_RAG_STAND;
	stBoss_rag.particle = new cRagPaticle(500,20);
	stBoss_rag.particle->init("Particle/T_VFX_SWIRL64B_A_CONTRAST2.png");

	m_vecBoss_rag.push_back(stBoss_rag);*/
}

void cEnemyControl::BossUpdate(std::vector<tagMon> Monster)
{
	cEnemyManager::Update();

	//리치왕 업데이트
	if (m_pBossAniController)
		m_pBossAniController->Update(&m_vecBoss[0].e_boss_state);

	m_vecBoss[0].particle->update(1.0001f);

	//라그나로스 업데이트
	
	if (m_pBossSkill)
		m_pBossSkill->Update(&m_vecBoss[0].e_boss_state, &m_vecBoss_rag[0].e_boss_rag_state);

	if (!m_vecBoss[0].chk)
	{
		if (m_vecBoss[0].e_boss_state == E_BOSS_SPELL2)
		{
			nCount++;

			if (nCount > 20)
			{
				nMonsterX = m_vecBoss[0].m_vPos.x;
				nMonsterY = m_vecBoss[0].m_vPos.z;
				m_pSpider->addMonster(nMonsterX + 2, 0, nMonsterY + 3);
				m_pSpider->addMonster(nMonsterX + 3, 0, nMonsterY);
				m_pSpider->addMonster(nMonsterX + 4, 0, nMonsterY -3);
				m_pSpider->addMonster(nMonsterX - 2, 0, nMonsterY -3);
				m_pSpider->addMonster(nMonsterX - 5, 0, nMonsterY +3);
				nCount = 0;
			}
		}
		if (m_vecBoss[0].e_boss_state == E_BOSS_SPELL1)
		{
			m_pBossAniController->Skill();
		}
	}
	

	BossPlayerCheck();

	

	// 체력 테스트
	if (g_pKeyManager->isOnceKeyDown('L'))
	{
		m_vecBoss[0].stat.HP = m_vecBoss[0].stat.HP - 450;
	}
	if (g_pKeyManager->isOnceKeyDown('K'))
	{
		m_vecBoss_rag[0].stat.HP = m_vecBoss_rag[0].stat.HP - 450;
	}

	if (g_pKeyManager->isStayKeyDown(VK_F11))
	{
		m_vecBoss_rag[0].stat.HP -= 10;
	}

	if (m_vecBoss[0].stat.HP <= 0)
	{
		m_vecBoss[0].e_boss_state = E_BOSS_DEATH;
		a++;
	}
	
	if (m_vecBoss[0].e_boss_state == E_BOSS_DEATH && a == 150 )
	{
		//m_vecBoss_rag[0].e_boss_rag_state = E_BOSS_RAG_START;
		m_Change = true;
	}
}

void cEnemyControl::BossRender()
{

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
	

	
	//D3DXMatrixIdentity(&matW2);
	
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &matW2);
	//m_vecBoss_rag[0].particle->render();


}

void cEnemyControl::ragRender()
{
	D3DXMATRIXA16 matW2;
	if (m_pBossRagController && m_vecBoss[0].e_boss_state == E_BOSS_DEATH)
		m_pBossRagController->Render(matW2);
}

void cEnemyControl::ragUpdate()
{
	if (m_vecBoss[0].e_boss_state == E_BOSS_DEATH)
	{
		if (m_pBossRagController)
			m_pBossRagController->Update(&m_vecBoss_rag[0].e_boss_rag_state);

		m_vecBoss_rag[0].particle->update(1.0f);
	}

	if (!m_vecBoss_rag[0].chk)
	{
		if (m_vecBoss_rag[0].e_boss_rag_state == E_BOSS_RAG_SPELL)
		{
			nCount++;

			if (nCount > 50)
			{
				nMonsterX = m_vecBoss_rag[0].m_vPos.x;
				nMonsterY = m_vecBoss_rag[0].m_vPos.z;
				m_pWorg->addMonster(nMonsterX + 2, 0, nMonsterY + 3);
				m_pWorg->addMonster(nMonsterX + 3, 0, nMonsterY);
				m_pWorg->addMonster(nMonsterX + 4, 0, nMonsterY +5);
				m_pWorg->addMonster(nMonsterX - 2, 0, nMonsterY +4);
				m_pWorg->addMonster(nMonsterX - 5, 0, nMonsterY + 3);
				nCount = 0;
			}
		}

	}

	if (m_vecBoss[0].e_boss_state == E_BOSS_DEATH)
	{

		BossRagPlayerCheck();
	}
	if (m_vecBoss_rag[0].stat.HP <= 0)
	{
		m_vecBoss_rag[0].e_boss_rag_state = E_BOSS_RAG_DEATH;
		g_pSoundManager->play("ragnaros_death", 1.f);
	}
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
						g_pSoundManager->play("arthas_att", 1.f);
						m_vecBoss[0].e_boss_state = E_BOSS_ATT;
						m_vecBoss[0].count = 0;
						
					}
					if (m_vecBoss[0].stat.HP <= 200)
					{
						m_vecBoss[0].e_boss_state = E_BOSS_WHIRLWIND;
						if(m_vecBoss[0].e_boss_state == E_BOSS_WHIRLWIND)
						g_pSoundManager->play("arthas_whirlwind", 1.f);
						//else g_pSoundManager->stop("arthas_whirlwind");
					}
					m_vecBoss[0].chk = false;
				}
				if (delay2 > 8 && delay2 < 15)
				{
					m_vecBoss[0].count += 5;
					if (m_vecBoss[0].count > 6)
					{
						g_pSoundManager->play("arthas_att2", 1.f);
						m_vecBoss[0].e_boss_state = E_BOSS_ATT2;
					}
					if (m_vecBoss[0].stat.HP <= 100)
					{
						if(!spiderChk)	m_vecBoss[0].e_boss_state = E_BOSS_SPELL2;
						m_vecBoss[0].count = 0;
						spiderChk = true;
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
}

void cEnemyControl::BossPlayerRot(D3DXVECTOR3 d)
{
	m_vPlayerPos = d;
}

void cEnemyControl::BossRagPlayerCheck()
{
	
	if (m_vecBoss_rag[0].e_boss_rag_state != E_BOSS_RAG_DEATH && m_vecBoss_rag[0].e_boss_rag_state != E_BOSS_RAG_START)
	{
		m_vecBoss_rag[0].m_vPos = m_pBossRagController->GetvBossPos();

		D3DXVECTOR3 Dir;
		float Distance;
		D3DXVec3Normalize(&Dir, &(m_vPlayerPos - m_vecBoss_rag[0].m_vPos));
		Distance = fabs(D3DXVec3Length(&(m_vPlayerPos - m_vecBoss_rag[0].m_vPos)));
		if (
			m_vecBoss_rag[0].e_boss_rag_state == E_BOSS_RAG_STAND)
		{
			m_vecBoss_rag[0].count++;
			if (m_vecBoss_rag[0].count > 50)
			{
				m_vecBoss_rag[0].chk = true;
			}

			m_pBossRagController->SetvBossPos(m_vecBoss_rag[0].m_vPos);
			m_pBossRagController->SetBossDir(Dir);
		}

		if (Distance > 10.0f)
		{
			m_vecBoss_rag[0].e_boss_rag_state = E_BOSS_RAG_STAND;
			m_vecBoss_rag[0].chk = false;
		}

		if (Distance < 10.0f)
		{
			
			skillDelay++;

			if (skillDelay > 70)
			{
				delay1 = rand() % 15;
				delay2 = rand() % 1000;
				
					m_vecBoss_rag[0].count += 1;
					if (delay2 >= 800 && delay2 < 1000)
					{
						if (!wolfChk)
						{
							m_vecBoss_rag[0].e_boss_rag_state = E_BOSS_RAG_SPELL;
						}
						wolfChk = true;
					}

					if (delay2 >= 0 && delay2 < 800)
					{
						
						m_vecBoss_rag[0].e_boss_rag_state = E_BOSS_RAG_ATT;
						m_vecBoss_rag[0].count = 0;
						g_pSoundManager->play("ragnaros_att", 1.f);
					}
					
					m_vecBoss_rag[0].chk = false;
				
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
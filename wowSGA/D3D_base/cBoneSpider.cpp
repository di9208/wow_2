#include "stdafx.h"
#include "cBoneSpider.h"
#include "cSkinnedMesh.h"
#include "iMap.h"
#include "cOBB.h"
#include <time.h>
#include "cUIImage.h"


cBoneSpider::cBoneSpider()
	: m_vecSkinnedMesh(NULL)
	, m_pFont(NULL)
	, m_pFont2(NULL)
	, m_pSprite(NULL)
	, Root(nullptr)
	, attack_time(0.0f)
	, hit_on(false)
{
	g_pSoundManager->Setup();
	g_pSoundManager->addSound("SpiderHit", "sound/monster/bonespider/wound.mp3", false, false);
	D3DXMatrixIdentity(&matWorld);
	m_pSkillOn = false;
	nCount = 0;
}

cBoneSpider::~cBoneSpider()
{
	SAFE_RELEASE(m_pFont);
	SAFE_RELEASE(m_pFont2);
	SAFE_RELEASE(m_pSprite);
	for (size_t i = 0; i < m_vecSkinnedMesh.size(); i++)
	{
		for (size_t j = 0; j < m_vecSkinnedMesh[i].m_ItemSprite.size(); j++) {
			SAFE_RELEASE(m_vecSkinnedMesh[i].m_ItemSprite[j].m_pTexture);
		}
		SAFE_RELEASE(m_vecSkinnedMesh[i].m_pMeshSphere);
		SAFE_DELETE(m_vecSkinnedMesh[i].Particle);
		SAFE_DELETE(m_vecSkinnedMesh[i].MonsterOBB);
		SAFE_DELETE(m_vecSkinnedMesh[i].m);
	}
}

void cBoneSpider::getWeaponHit(int i, cOBB * PlayerWeapon,float Damage)
{
	if (m_vecSkinnedMesh[i].Hurt == false)
	{
		if (PlayerWeapon)
		{
			if (PlayerWeapon->getCheck(0).x != -431602080 && PlayerWeapon->getCheck(0).x != -431602080)
			{
				if (PlayerWeapon->IsCollision(m_vecSkinnedMesh[i].MonsterOBB, PlayerWeapon))
				{
					attack_time = g_pTimeManager->GetLastUpdateTime();
					hit_on = true;
					m_vecSkinnedMesh[i].Hurt = true;
				}
			}
		}
	}
	else
	{
		if (hit_on)
		{
			if (attack_time + 0.5f < g_pTimeManager->GetLastUpdateTime())
			{
				g_pSoundManager->play("HAMMER", 2.0f);
				hit_on = false;
				m_vecSkinnedMesh[i].t.HP -= Damage;
			}
		}
	}
}

void cBoneSpider::addMonster(float x, float y, float z) {
	//몬스터를 생성해줌

	Monster.m = new cSkinnedMesh;
	Monster.m->Setup("Monster/bonespider", "1.x");
	Monster.ENUM_MONSTER = MONSTER_STATUS::MONSTER_STAND;
	Monster.ENUM_MONSTER_KIND = MONSTER_KIND::KIND_SPIDER;
	Monster.m_vPos = D3DXVECTOR3(x, y + 0.3, z);
	Monster.m_vDir = D3DXVECTOR3(0, 0, 1);
	Monster.t.HP = 80;
	Monster.MaxHP = 80;
	Monster.t.ATK = 8;
	Monster.t.DEF = 8;
	Monster.t.Speed = 0.07f;
	Monster.attackSpeed = 110;
	Monster.t.Gold = rand() % 100 + 1500;
	Monster.m_Sphere.vCenter = D3DXVECTOR3(x, y + 0.3, z);
	Monster.m_Sphere.fRadius = 10.f;
	Monster.m_Sphere.bIsPicked = false;
	Monster.MaxRange = 7.f;
	Monster.range = 1.5f;
	Monster.time = 0;
	Monster.death = false;
	Monster.deathTime = 0;
	Monster.attackTime = 100;
	Monster.termCount = 0;
	Monster.RunCount = rand() % 250 + 10;
	Monster.Damage = false;
	Monster.Damage_time = 0.0f;
	Monster.TimeCheck = 0.0f;

	Monster.Particle = new cMonsterParticle(512, 20);
	Monster.Particle->init("Particle/alpha_tex.tga");
	D3DXMatrixIdentity(&Monster.matWorld);
	D3DXMATRIXA16 matTT, matSS;
	D3DXMatrixScaling(&matSS, 0.0f, 0.0f, 0.0f);
	D3DXMatrixTranslation(&matTT, x, y + 0.3, z);
	Monster.matWorld = matSS * matTT;

	ZeroMemory(&Monster.m_stMtlNone, sizeof(D3DMATERIAL9));
	Monster.m_stMtlNone.Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	Monster.m_stMtlNone.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	Monster.m_stMtlNone.Specular = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

	ZeroMemory(&Monster.m_stMtlPicked, sizeof(D3DMATERIAL9));
	Monster.m_stMtlPicked.Ambient = D3DXCOLOR(0.0f, 0.8f, 0.8f, 1.0f);
	Monster.m_stMtlPicked.Diffuse = D3DXCOLOR(0.0f, 0.8f, 0.8f, 1.0f);
	Monster.m_stMtlPicked.Specular = D3DXCOLOR(0.0f, 0.8f, 0.8f, 1.0f);

	D3DXMATRIXA16	World, matS, matR, matT;
	D3DXMatrixRotationX(&matR, D3DX_PI / 2.0f);
	D3DXMatrixScaling(&matS, 0.009f, 0.009f, 0.009f);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, 0, 0, -0.3);
	World = matS * matR * matT;

	Monster.MonsterOBB = new cOBB;
	Monster.MonsterOBB->Setup(Monster.m, &World);



	D3DXCreateSphere(g_pD3DDevice, Monster.m_Sphere.fRadius, 10, 10,
		&Monster.m_pMeshSphere, NULL);

	m_vecSkinnedMesh.push_back(Monster);


	//SetupUI(0, 4);
}

void cBoneSpider::addMonster(std::string key, float x, float y, float z)
{
	Monster.m = g_pSkinnedMeshManager->Find(key);
	
	Monster.ENUM_MONSTER = MONSTER_STATUS::MONSTER_STAND;
	Monster.ENUM_MONSTER_KIND = MONSTER_KIND::KIND_SPIDER;
	Monster.m_vPos = D3DXVECTOR3(x, y + 0.3, z);
	Monster.m_vDir = D3DXVECTOR3(0, 0, 1);
	Monster.t.HP = 80;
	Monster.MaxHP = 80;
	Monster.t.ATK = 8;
	Monster.t.DEF = 8;
	Monster.t.Speed = 0.07f;
	Monster.attackSpeed = 110;
	Monster.t.Gold = rand() % 100 + 1500;
	Monster.m_Sphere.vCenter = D3DXVECTOR3(x, y + 0.3, z);
	Monster.m_Sphere.fRadius = 10.f;
	Monster.m_Sphere.bIsPicked = false;
	Monster.MaxRange = 7.f;
	Monster.range = 1.5f;
	Monster.time = 0;
	Monster.death = false;
	Monster.deathTime = 0;
	Monster.attackTime = 100;
	Monster.termCount = 0;
	Monster.RunCount = rand() % 250 + 10;
	Monster.Damage = false;
	Monster.Damage_time = 0.0f;
	Monster.TimeCheck = 0.0f;

	Monster.Particle = new cMonsterParticle(512, 20);
	Monster.Particle->init("Particle/alpha_tex.tga");
	D3DXMatrixIdentity(&Monster.matWorld);
	D3DXMATRIXA16 matTT, matSS;
	D3DXMatrixScaling(&matSS, 0.0f, 0.0f, 0.0f);
	D3DXMatrixTranslation(&matTT, x, y + 0.3, z);
	Monster.matWorld = matSS * matTT;

	ZeroMemory(&Monster.m_stMtlNone, sizeof(D3DMATERIAL9));
	Monster.m_stMtlNone.Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	Monster.m_stMtlNone.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	Monster.m_stMtlNone.Specular = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

	ZeroMemory(&Monster.m_stMtlPicked, sizeof(D3DMATERIAL9));
	Monster.m_stMtlPicked.Ambient = D3DXCOLOR(0.0f, 0.8f, 0.8f, 1.0f);
	Monster.m_stMtlPicked.Diffuse = D3DXCOLOR(0.0f, 0.8f, 0.8f, 1.0f);
	Monster.m_stMtlPicked.Specular = D3DXCOLOR(0.0f, 0.8f, 0.8f, 1.0f);

	D3DXMATRIXA16	World, matS, matR, matT;
	D3DXMatrixRotationX(&matR, D3DX_PI / 2.0f);
	D3DXMatrixScaling(&matS, 0.009f, 0.009f, 0.009f);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, 0, 0, -0.3);
	World = matS * matR * matT;

	Monster.MonsterOBB = new cOBB;
	Monster.MonsterOBB->Setup(Monster.m, &World);



	D3DXCreateSphere(g_pD3DDevice, Monster.m_Sphere.fRadius, 10, 10,
		&Monster.m_pMeshSphere, NULL);

	m_vecSkinnedMesh.push_back(Monster);
}


void cBoneSpider::SetUp() {

	D3DXFONT_DESC stFD;
	srand(time(NULL));
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	ZeroMemory(&stFD, sizeof(D3DXFONT_DESC));
	stFD.Height = 20;
	stFD.Width = 10;
	stFD.Weight = FW_MEDIUM;
	stFD.Italic = false;
	stFD.CharSet = DEFAULT_CHARSET;
	stFD.OutputPrecision = OUT_DEFAULT_PRECIS;
	stFD.PitchAndFamily = FF_DONTCARE;

	strcpy_s(stFD.FaceName, "굴림체");

	//AddFontResource("font/umberto.ttf");
	//strcpy_s(stFD.FaceName, "umberto");

	D3DXCreateFontIndirect(g_pD3DDevice, &stFD, &m_pFont);
}


void cBoneSpider::Update(iMap* pMap) {
	//거미 업데이트
	if (m_vecSkinnedMesh.size() != 0)
	{
		for (size_t i = 0; i < m_vecSkinnedMesh.size(); i++) {
			//몬스터 죽음

			matUpdate(i, pMap);
			m_vecSkinnedMesh[i].m->Update();
			m_vecSkinnedMesh[i].Particle->update(2.0f);
			m_vecSkinnedMesh[i].MonsterOBB->Update(&m_vecSkinnedMesh[i].matRT);
			MonsterAI(i);						//몬스터의 패턴, 스킬

			if (m_vecSkinnedMesh[i].t.HP <= 0) m_vecSkinnedMesh[i].ENUM_MONSTER = MONSTER_STATUS::MONSTER_DEATH;
			MonsterStatus(i); 					//몬스터 상태, 애니메이tus
		}
	}
	/*if (Root)
	{
		Root->Update();
	}	*/
}


void cBoneSpider::Render() {

	if (m_vecSkinnedMesh.size() != 0)
	{
		for (size_t i = 0; i < m_vecSkinnedMesh.size(); i++) {
			m_vecSkinnedMesh[i].m->Render(NULL, &m_vecSkinnedMesh[i].matWorld);
			D3DXMATRIXA16 matT;
			D3DXMatrixTranslation(&matT, 0, 0, -0.3);
			g_pD3DDevice->SetTransform(D3DTS_WORLD, &(m_vecSkinnedMesh[i].matWorld*matT));

			m_vecSkinnedMesh[i].Particle->render();
			D3DCOLOR c = D3DCOLOR_XRGB(255, 255, 255);

			SphereRender(i, m_vecSkinnedMesh[i].matWorld);
			m_vecSkinnedMesh[i].MonsterOBB->Render_Debug(c, nullptr, nullptr);


			/*if (m_vecSkinnedMesh[i].death) {
				RenderUI(i);
			}*/
		}
	}
}

void cBoneSpider::MonsterInsic(D3DXVECTOR3 d) {
	m_vPlayerPos = d;
}

void cBoneSpider::HarmDamage(int Damage, size_t i) {
	//인자1 : 들어올 데미지, i 타겟이 된 몬스터
	if (m_vecSkinnedMesh[i].t.HP > (Damage - m_vecSkinnedMesh[i].t.DEF))
		m_vecSkinnedMesh[i].t.HP -= (Damage - m_vecSkinnedMesh[i].t.DEF);
	else m_vecSkinnedMesh[i].t.HP = 0;
}

//거미 상태
void cBoneSpider::MonsterStatus(size_t i) {
	switch (m_vecSkinnedMesh[i].ENUM_MONSTER)
	{
	case MONSTER_STAND:
		m_vecSkinnedMesh[i].m->Play("Stand");
		break;

	case MONSTER_RUN:
		m_vecSkinnedMesh[i].m->Play("Run");
		break;

	case MONSTER_ATTACK:
		m_vecSkinnedMesh[i].m->PlayOneShot("Attack");
		break;
	case MONSTER_DEATH:
		m_vecSkinnedMesh[i].m->PlayOneShotAfterHold("Death");
		MonsterDeath(i);
		break;
	default:
		m_vecSkinnedMesh[i].m->Play("Stand");
		break;
	}

}

void cBoneSpider::SetupUI(size_t m_MonsterItem) {
	cUIImage* main = new cUIImage;
	main->SetTexture("bonespiderInven","UI/UI_Enemy_Invectory.png");
	main->SetPos(D3DXVECTOR3(20, 150, 0));

	Root = main;
	if (m_MonsterItem >= 0)
	{
		cUIImage* item = new cUIImage;
		char str[1024];
		itoa(0, str, 10);
		std::string key = std::string("gold") + std::string(str);
		item->SetTexture(key, "UI/gold.png");
		item->SetPos(D3DXVECTOR3(27, (44) + 51 + (14), 0));
		Root->AddChild(item);
	}
	if (m_MonsterItem >= 1)
	{
		cUIImage* item = new cUIImage;
		char str[1024];
		itoa(1, str, 10);
		std::string key = std::string("spider") + std::string(str);
		item->SetTexture(key, "UI/spider.png");
		item->SetPos(D3DXVECTOR3(27, (44 * 2) + 50 + (2 * 14), 0));
		Root->AddChild(item);
	}
}

void cBoneSpider::RenderUI(size_t i) {
	if (Root)
		Root->Render(m_pSprite);
	if (m_pFont && m_MonsterItem >= 0)
	{
		char str[128];
		sprintf(str, "골드 : %.f ", m_vecSkinnedMesh[i].t.Gold);

		std::string sText(str);
		RECT rc;
		SetRect(&rc, 110, 150 + 120, 300, 200);
		m_pFont->DrawText(NULL,
			sText.c_str(),
			sText.length(),
			&rc,
			DT_LEFT | DT_TOP | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 255));
	}
	if (m_pFont2 && m_MonsterItem >= 1)
	{
		std::string sText("거미줄");
		RECT rc;
		SetRect(&rc, 110, 150 + 180, 300, 200);
		m_pFont->DrawText(NULL,
			sText.c_str(),
			sText.length(),
			&rc,
			DT_LEFT | DT_TOP | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 255));
	}
}

void cBoneSpider::MonsterDeath(size_t i) {
	//HP가 0이 되면 죽는 모션이 나온다.
	m_vecSkinnedMesh[i].deathTime++;


	if (!m_vecSkinnedMesh[i].death) {
		m_MonsterItem = rand() % 2;
		SetupUI(m_MonsterItem);
		m_vecSkinnedMesh[i].death = true;
	}
	//죽는 모션 후 일정시간이 지나면 해당 애니메이션은 정지시킨다.
	else {
		if (m_vecSkinnedMesh[i].deathTime > 100) {
			SAFE_RELEASE(m_vecSkinnedMesh[i].m_pMeshSphere);
			SAFE_DELETE(m_vecSkinnedMesh[i].m);
			m_vecSkinnedMesh.erase(m_vecSkinnedMesh.begin() + i);
		}
	}
}

//거미 AI1
void cBoneSpider::MonsterAI(size_t i) {
	D3DXVECTOR3 pos[100], dir[100];
	pos[i] = m_vecSkinnedMesh[i].m_vPos;
	dir[i] = m_vecSkinnedMesh[i].m_vDir;
	if (m_vPlayerPos < pos[i]) m_vecSkinnedMesh[i].sum = pos[i] - m_vPlayerPos;
	else m_vecSkinnedMesh[i].sum = m_vPlayerPos - pos[i];

	m_vecSkinnedMesh[i].distance = D3DXVec3Length(&m_vecSkinnedMesh[i].sum);

	//적이 인식범위 안에 들어왔는지 확인, 물론 죽은 상태는 아니어야 함
	if (m_vecSkinnedMesh[i].distance < m_vecSkinnedMesh[i].MaxRange &&
		m_vecSkinnedMesh[i].distance > m_vecSkinnedMesh[i].range &&
		m_vecSkinnedMesh[i].ENUM_MONSTER != MONSTER_DEATH) {

		//적의 방향을 보기 위한 코드
		D3DXMATRIXA16 matR;
		D3DXMatrixIdentity(&matR);

		D3DXVECTOR3 vDir = m_vPlayerPos - pos[i];

		vDir.y = dir[i].y = 0.F;

		D3DXVec3Normalize(&vDir, &vDir);
		D3DXVec3Normalize(&dir[i], &dir[i]);

		float fDot = D3DXVec3Dot(&vDir, &dir[i]);

		if (fDot <= 0.95f)
		{
			D3DXVECTOR3 vCross;
			D3DXVec3Cross(&vCross, &dir[i], &vDir);
			D3DXVec3Normalize(&vCross, &vCross);

			if (vCross.y > 0.F)
			{
				D3DXMATRIXA16 matR;
				D3DXMatrixIdentity(&matR);
				D3DXMatrixRotationY(&matR, 0.5F);
				D3DXVec3TransformNormal(&dir[i], &dir[i], &matR);

			}
			else
			{
				D3DXMATRIXA16 matR;
				D3DXMatrixIdentity(&matR);
				D3DXMatrixRotationY(&matR, -0.5F);
				D3DXVec3TransformNormal(&dir[i], &dir[i], &matR);
			}
		}
		else
		{
			dir[i] = vDir;
		}

		//적이 인식범위 안에 들어왔다면 카운트 발동
		m_vecSkinnedMesh[i].time++;

		//공격상태가 아니라면 일정시간이 지난 후 따라감
		if (m_vecSkinnedMesh[i].time > 50 &&
			m_vecSkinnedMesh[i].ENUM_MONSTER != MONSTER_ATTACK &&
			m_vecSkinnedMesh[i].ENUM_MONSTER != MONSTER_DEATH) {
			m_vecSkinnedMesh[i].ENUM_MONSTER = MONSTER_RUN;
			if (m_vecSkinnedMesh[i].attackTime < m_vecSkinnedMesh[i].attackSpeed - 1) m_vecSkinnedMesh[i].attackTime++;
			pos[i] += dir[i] * m_vecSkinnedMesh[i].t.Speed;
			m_vecSkinnedMesh[i].m_vPos = pos[i];
			m_vecSkinnedMesh[i].m_vDir = dir[i];
		}

		//일정시간이 지나지 않았다면 스탠드 상태
		else if (m_vecSkinnedMesh[i].time <= 50 &&
			m_vecSkinnedMesh[i].ENUM_MONSTER != MONSTER_ATTACK &&
			m_vecSkinnedMesh[i].ENUM_MONSTER != MONSTER_DEATH) {
			if (m_vecSkinnedMesh[i].attackTime < m_vecSkinnedMesh[i].attackSpeed - 1) m_vecSkinnedMesh[i].attackTime++;
			m_vecSkinnedMesh[i].ENUM_MONSTER = MONSTER_STAND;
		}
	}

	//적이 인식범위 밖으로 빠져나갔다면 행동을 멈춘다.
	if (m_vecSkinnedMesh[i].distance > m_vecSkinnedMesh[i].MaxRange &&
		m_vecSkinnedMesh[i].ENUM_MONSTER != MONSTER_DEATH) {
		m_vecSkinnedMesh[i].time = 0;
		//if (m_vecSkinnedMesh[i].ENUM_MONSTER != MONSTER_RUN) m_vecSkinnedMesh[i].ENUM_MONSTER = MONSTER_STAND;
		srand(time(NULL));

		D3DXVECTOR3 vDir, m_vDir, vCenter;
		m_vDir = m_vecSkinnedMesh[i].m_vDir;
		vCenter = m_vecSkinnedMesh[i].m_vPos;
		if (m_vecSkinnedMesh[i].RunCount < 0) {
			vDir.y = 0.f;

			D3DXMATRIXA16 matR;
			D3DXMatrixIdentity(&matR);
			if (rand() % 4 == 0)	D3DXMatrixRotationY(&matR, rand() % 180);
			else if (rand() % 4 == 1)D3DXMatrixRotationY(&matR, -rand() % 180);
			else if (rand() % 4 == 2)D3DXMatrixRotationY(&matR, rand() % 180);
			else if (rand() % 4 == 3)D3DXMatrixRotationY(&matR, -rand() % 180);
			D3DXVec3TransformNormal(&m_vDir, &m_vDir, &matR);


			m_vecSkinnedMesh[i].termCount++;
			m_vecSkinnedMesh[i].ENUM_MONSTER = MONSTER_STAND;

			if (m_vecSkinnedMesh[i].termCount > rand() % 300 + 50) {
				m_vecSkinnedMesh[i].termCount = 0;
				m_vecSkinnedMesh[i].RunCount = rand() % 250 + 10;
			}
		}
		D3DXVec3Normalize(&vDir, &vDir);
		D3DXVec3Normalize(&m_vDir, &m_vDir);

		m_vecSkinnedMesh[i].RunCount--;
		if (m_vecSkinnedMesh[i].RunCount > 0) {
			m_vecSkinnedMesh[i].termCount = 0;
			vCenter += m_vDir * m_vecSkinnedMesh[i].t.Speed;
			m_vecSkinnedMesh[i].m_vPos = vCenter;
			m_vecSkinnedMesh[i].m_vDir = m_vDir;
			m_vecSkinnedMesh[i].ENUM_MONSTER = MONSTER_RUN;
		}
	}

	//어택타임이 넘어가면 어택타임을 0으로 초기화하고, 공격모드를 취소함
	if (m_vecSkinnedMesh[i].attackTime >= m_vecSkinnedMesh[i].attackSpeed) {
		m_vecSkinnedMesh[i].attackTime = 0;
	}

	//공격의 인식거리
	if (m_vecSkinnedMesh[i].distance <= m_vecSkinnedMesh[i].range ||
		m_vecSkinnedMesh[i].ENUM_MONSTER == MONSTER_ATTACK)
	{
		//공격 범위안에 들어온다면, 이동을 멈추고 공격을 준비한다.
		m_vecSkinnedMesh[i].time = 0;
		m_vecSkinnedMesh[i].attackTime++;

		//어택타임이 차면 공격
		if (m_vecSkinnedMesh[i].attackTime < 50 &&
			m_vecSkinnedMesh[i].ENUM_MONSTER != MONSTER_DEATH) {
			if (m_vecSkinnedMesh[i].attackTime < 2) {
				g_pSoundManager->play("SpiderHit", 1.0f);
			}
			m_vecSkinnedMesh[i].ENUM_MONSTER = MONSTER_ATTACK;
		}
		//하거나 쉬도록 함
		else if (m_vecSkinnedMesh[i].attackTime > 50 &&
			m_vecSkinnedMesh[i].ENUM_MONSTER != MONSTER_DEATH) {
			m_vecSkinnedMesh[i].ENUM_MONSTER = MONSTER_STAND;
		}
	}
}


//스피어 렌더(골드, 몬스터)
void cBoneSpider::SphereRender(size_t i, D3DXMATRIXA16& m_matWorld) {
	//스피어부분 렌더
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetMaterial(m_vecSkinnedMesh[i].m_Sphere.bIsPicked ?
		&m_vecSkinnedMesh[i].m_stMtlPicked : &m_vecSkinnedMesh[i].m_stMtlNone);
	//m_vecSkinnedMesh[i].m_pMeshSphere->DrawSubset(0);
}

void cBoneSpider::matUpdate(size_t i, iMap* pMap) {
	D3DXMATRIXA16 matR, matS, matT;
	D3DXMatrixScaling(&matS, 0.07f, 0.07f, 0.07f);

	D3DXMatrixRotationY(&matR, D3DX_PI * 1.5);

	D3DXVECTOR3 dir;
	D3DXVec3TransformNormal(&dir, &m_vecSkinnedMesh[i].m_vDir, &matR);

	D3DXVECTOR3 vUp(0, 1, 0);
	D3DXVECTOR3 vRight;
	D3DXVec3Cross(&vRight, &vUp, &dir);
	D3DXVec3Normalize(&vRight, &vRight);
	D3DXVec3Cross(&vUp, &dir, &vRight);
	D3DXMatrixLookAtLH(&matR, &D3DXVECTOR3(0, 0, 0), &dir, &vUp);
	D3DXMatrixTranspose(&matR, &matR);

	D3DXVECTOR3 vTempPos[100];
	vTempPos[i] = m_vecSkinnedMesh[i].m_vPos;

	D3DXMatrixIdentity(&matT);
	if (pMap)
	{
		if (pMap->GetHeight(vTempPos[i].x, vTempPos[i].y, vTempPos[i].z))
		{
			if (m_vecSkinnedMesh[i].ENUM_MONSTER != MONSTER_DEATH)
			{
				m_vecSkinnedMesh[i].m_vPos = vTempPos[i];
			}
			else {
				m_vecSkinnedMesh[i].m_vPos.x = vTempPos[i].x;
				m_vecSkinnedMesh[i].m_vPos.z = vTempPos[i].z;
			}
		}
	}
	else
	{
		m_vecSkinnedMesh[i].m_vPos = vTempPos[i];
	}

	D3DXMatrixTranslation(&matT, m_vecSkinnedMesh[i].m_vPos.x, m_vecSkinnedMesh[i].m_vPos.y + 0.45, m_vecSkinnedMesh[i].m_vPos.z);
	m_vecSkinnedMesh[i].matRT = matR * matT;
	m_vecSkinnedMesh[i].matWorld = matS * matR * matT;
}

D3DXVECTOR3 cBoneSpider::getOBBCenter(int i)
{
	return m_vecSkinnedMesh[i].MonsterOBB->GetCenterPos();
}

float cBoneSpider::getOBBhalf(int i)
{
	return m_vecSkinnedMesh[i].MonsterOBB->getMax();
}
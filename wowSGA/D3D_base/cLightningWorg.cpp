#include "stdafx.h"
#include "cLightningWorg.h"
#include "cSkinnedMesh.h"
#include "cOBB.h"
#include "iMap.h"
#include <time.h>
#include "cUIImage.h"

cLightningWorg::cLightningWorg()
	: m_vecSkinnedMesh(NULL)
	, m_pFont(NULL)
	, m_pSprite(NULL)
	, Root(nullptr)
	, attack_time(0.0f)
	, hit_on(false)
{
	g_pSoundManager->Setup();
	g_pSoundManager->addSound("WorgHit", "sound/monster/litningworg/wound.mp3", false, false);
	g_pSoundManager->addSound("WorgHo", "sound/monster/litningworg/wolf.mp3", false, false);
	D3DXMatrixIdentity(&matWorld);
	m_pSkillOn = false;
	nCount = 0;
}

cLightningWorg::~cLightningWorg()
{
	//SAFE_RELEASE(m_pInvectory);
	SAFE_RELEASE(m_pFont);
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

void cLightningWorg::getWeaponHit(int i, cOBB * PlayerWeapon,float damage)
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
				m_vecSkinnedMesh[i].t.HP -= damage;
			}
		}
	}
}

void cLightningWorg::addMonster(float x, float y, float z) {
	//���͸� ��������

	EnemySkinnedMesh Monster;
	Monster.m = new cSkinnedMesh;
	Monster.m->Setup("Monster/lightningworg", "1.x");
	Monster.ENUM_MONSTER = MONSTER_STATUS::MONSTER_STAND;
	Monster.ENUM_MONSTER_KIND = MONSTER_KIND::KIND_WORG;
	Monster.m_vPos = D3DXVECTOR3(x, y + 0.45, z);
	Monster.m_vDir = D3DXVECTOR3(0, 0, 1);
	Monster.t.HP = 50;
	Monster.MaxHP = 50;
	Monster.t.ATK = 3;
	Monster.t.DEF = 5;
	Monster.t.Speed = 0.08f;
	Monster.attackSpeed = 130;
	Monster.t.Gold = rand() % 100 + 1500;
	Monster.m_Sphere.vCenter = D3DXVECTOR3(x, y + 0.45, z);
	Monster.m_Sphere.fRadius = 10.f;
	Monster.m_Sphere.bIsPicked = false;
	Monster.MaxRange = 10.f;
	Monster.range = 1.f;
	Monster.time = 0;
	Monster.death = false;
	Monster.deathTime = 0;
	Monster.attackTime = 100;
	Monster.termCount = 0;
	Monster.RunCount = rand() % 250 + 10;

	Monster.Particle = new cMonsterParticle(50, 25);
	Monster.Particle->init("Particle/alpha_tex.tga");
	D3DXMatrixIdentity(&Monster.matWorld);
	D3DXMATRIXA16 matTT, matSS;
	D3DXMatrixScaling(&matSS, 0.0f, 0.0f, 0.0f);
	D3DXMatrixTranslation(&matTT, x, y + 0.45, z);
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
	D3DXMatrixScaling(&matS, 0.011f, 0.011f, 0.011f);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, 0, 0.35f, 0.3);
	World = matS * matR * matT;

	Monster.MonsterOBB = new cOBB;
	Monster.MonsterOBB->Setup(Monster.m, &World);

	D3DXCreateSphere(g_pD3DDevice, Monster.m_Sphere.fRadius, 10, 10,
		&Monster.m_pMeshSphere, NULL);

	m_vecSkinnedMesh.push_back(Monster);
}

void cLightningWorg::addMonster(std::string key, float x, float y, float z)
{

	EnemySkinnedMesh Monster;
	Monster.m = g_pSkinnedMeshManager->Find(key);
	//Monster.m->Setup("Monster/lightningworg", "1.x");
	Monster.ENUM_MONSTER = MONSTER_STATUS::MONSTER_STAND;
	Monster.ENUM_MONSTER_KIND = MONSTER_KIND::KIND_WORG;
	Monster.m_vPos = D3DXVECTOR3(x, y + 0.45, z);
	Monster.m_vDir = D3DXVECTOR3(0, 0, 1);
	Monster.t.HP = 50;
	Monster.MaxHP = 50;
	Monster.t.ATK = 3;
	Monster.t.DEF = 5;
	Monster.t.Speed = 0.08f;
	Monster.attackSpeed = 130;
	Monster.t.Gold = rand() % 100 + 1500;
	Monster.m_Sphere.vCenter = D3DXVECTOR3(x, y + 0.45, z);
	Monster.m_Sphere.fRadius = 10.f;
	Monster.m_Sphere.bIsPicked = false;
	Monster.MaxRange = 10.f;
	Monster.range = 1.f;
	Monster.time = 0;
	Monster.death = false;
	Monster.deathTime = 0;
	Monster.attackTime = 100;
	Monster.termCount = 0;
	Monster.RunCount = rand() % 250 + 10;

	Monster.Particle = new cMonsterParticle(512, 25);
	Monster.Particle->init("Particle/alpha_tex.tga");
	D3DXMatrixIdentity(&Monster.matWorld);
	D3DXMATRIXA16 matTT, matSS;
	D3DXMatrixScaling(&matSS, 0.0f, 0.0f, 0.0f);
	D3DXMatrixTranslation(&matTT, x, y + 0.45, z);
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
	D3DXMatrixScaling(&matS, 0.011f, 0.011f, 0.011f);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, 0, 0.35f, 0.3);
	World = matS * matR * matT;

	Monster.MonsterOBB = new cOBB;
	Monster.MonsterOBB->Setup(Monster.m, &World);

	D3DXCreateSphere(g_pD3DDevice, Monster.m_Sphere.fRadius, 10, 10,
		&Monster.m_pMeshSphere, NULL);

	m_vecSkinnedMesh.push_back(Monster);

}


void cLightningWorg::SetUp() {
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

	strcpy_s(stFD.FaceName, "����ü");

	//AddFontResource("font/umberto.ttf");
	//strcpy_s(stFD.FaceName, "umberto");

	D3DXCreateFontIndirect(g_pD3DDevice, &stFD, &m_pFont);
	D3DXCreateFontIndirect(g_pD3DDevice, &stFD, &m_pFont2);
}


void cLightningWorg::Update(iMap* map) {
	//�Ź� ������Ʈ

	if (m_vecSkinnedMesh.size() != 0)
	{
		for (size_t i = 0; i < m_vecSkinnedMesh.size(); i++) {
			matUpdate(i, map);
			m_vecSkinnedMesh[i].m->Update();
			m_vecSkinnedMesh[i].Particle->update(3.0f);
			m_vecSkinnedMesh[i].MonsterOBB->Update(&m_vecSkinnedMesh[i].matRT);
			MonsterAI(i);						//������ ����, ��ų

			//���� ����
			if (m_vecSkinnedMesh[i].t.HP <= 0) m_vecSkinnedMesh[i].ENUM_MONSTER = MONSTER_STATUS::MONSTER_DEATH;
			MonsterStatus(i); 					//���� ����, �ִϸ��̼�
		}
	}
	/*if (Root)
	{
		Root->Update();
	}*/
}


void cLightningWorg::Render() {

	if (m_vecSkinnedMesh.size() != 0)
	{
		for (size_t i = 0; i < m_vecSkinnedMesh.size(); i++) {
			m_vecSkinnedMesh[i].m->Render(NULL, &m_vecSkinnedMesh[i].matWorld);
			D3DXMATRIXA16 matT;
			D3DXMatrixTranslation(&matT, 0, 0.35f, 0);
			g_pD3DDevice->SetTransform(D3DTS_WORLD, &(m_vecSkinnedMesh[i].matWorld*matT));

			m_vecSkinnedMesh[i].Particle->render();
			D3DCOLOR c = D3DCOLOR_XRGB(255, 255, 255);

			SphereRender(i, m_vecSkinnedMesh[i].matWorld);
			m_vecSkinnedMesh[i].MonsterOBB->Render_Debug(c, nullptr, nullptr);

			//�׾��� ��
			/*if (m_vecSkinnedMesh[i].death) {
				RenderUI(i);
			}*/
		}
	}
}

void cLightningWorg::MonsterInsic(D3DXVECTOR3 d) {
	m_vPlayerPos = d;
}

void cLightningWorg::HarmDamage(int Damage, size_t i) {
	//����1 : ���� ������, i Ÿ���� �� ����
	if (m_vecSkinnedMesh[i].t.HP > (Damage - m_vecSkinnedMesh[i].t.DEF))
		m_vecSkinnedMesh[i].t.HP -= (Damage - m_vecSkinnedMesh[i].t.DEF);
	else m_vecSkinnedMesh[i].t.HP = 0;
}

//�Ź� ����
void cLightningWorg::MonsterStatus(size_t i) {
	//ZŰ�� ������ ü�� 100 �ް� ��
	if (g_pKeyManager->isOnceKeyDown('Z')) {
		HarmDamage(205, 0);
	}
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

void cLightningWorg::SetupUI(size_t a) {
	cUIImage* main = new cUIImage;
	main->SetTexture("worgInven", "UI/UI_Enemy_Invectory.png");
	main->SetPos(D3DXVECTOR3(20, 150, 0));

	Root = main;
	if (a >= 0)
	{
		cUIImage* item = new cUIImage;
		char str[1024];
		itoa(0, str, 10);
		std::string key = std::string("gold") + std::string(str);
		item->SetTexture(key, "UI/gold.png");
		item->SetPos(D3DXVECTOR3(27, (44) + 51 + (14), 0));
		Root->AddChild(item);
	}
	if (a >= 1)
	{
		cUIImage* item = new cUIImage;
		char str[1024];
		itoa(1, str, 10);
		std::string key = std::string("worg") + std::string(str);
		item->SetTexture(key, "UI/worg.png");
		item->SetPos(D3DXVECTOR3(27, (44 * 2) + 50 + (2 * 14), 0));
		Root->AddChild(item);
	}
}

void cLightningWorg::RenderUI(size_t i) {
	if (Root)
		Root->Render(m_pSprite);
	if (m_pFont && m_MonsterItem >= 0)
	{
		char str[128];
		sprintf(str, "��� : %.f ", m_vecSkinnedMesh[i].t.Gold);

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
		std::string sText("������ ����");
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

void cLightningWorg::MonsterDeath(size_t i) {
	//HP�� 0�� �Ǹ� �״� ����� ���´�.
	m_vecSkinnedMesh[i].deathTime++;


	if (!m_vecSkinnedMesh[i].death) {
		m_MonsterItem = rand() % 2;
		SetupUI(m_MonsterItem);
		m_vecSkinnedMesh[i].death = true;
	}
	//�״� ��� �� �����ð��� ������ �ش� �ִϸ��̼��� ������Ų��.
	else {
		if (m_vecSkinnedMesh[i].deathTime > 100) {
			SAFE_RELEASE(m_vecSkinnedMesh[i].m_pMeshSphere);
			SAFE_DELETE(m_vecSkinnedMesh[i].m);
			m_vecSkinnedMesh.erase(m_vecSkinnedMesh.begin() + i);
		}
	}
}

//�Ź� AI1
void cLightningWorg::MonsterAI(size_t i) {
	D3DXVECTOR3 pos[100], dir[100];
	pos[i] = m_vecSkinnedMesh[i].m_vPos;
	dir[i] = m_vecSkinnedMesh[i].m_vDir;
	if (m_vPlayerPos < pos[i]) m_vecSkinnedMesh[i].sum = pos[i] - m_vPlayerPos;
	else m_vecSkinnedMesh[i].sum = m_vPlayerPos - pos[i];

	m_vecSkinnedMesh[i].distance = D3DXVec3Length(&m_vecSkinnedMesh[i].sum);

	//���� �νĹ��� �ȿ� ���Դ��� Ȯ��, ���� ���� ���´� �ƴϾ�� ��
	if (m_vecSkinnedMesh[i].distance < m_vecSkinnedMesh[i].MaxRange &&
		m_vecSkinnedMesh[i].distance > m_vecSkinnedMesh[i].range &&
		m_vecSkinnedMesh[i].ENUM_MONSTER != MONSTER_DEATH) {

		//���� ������ ���� ���� �ڵ�
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

		//���� �νĹ��� �ȿ� ���Դٸ� ī��Ʈ �ߵ�
		m_vecSkinnedMesh[i].time++;

		//���ݻ��°� �ƴ϶�� �����ð��� ���� �� ����
		if (m_vecSkinnedMesh[i].time > 90 &&
			m_vecSkinnedMesh[i].ENUM_MONSTER != MONSTER_ATTACK &&
			m_vecSkinnedMesh[i].ENUM_MONSTER != MONSTER_DEATH) {
			m_vecSkinnedMesh[i].ENUM_MONSTER = MONSTER_RUN;
			if (m_vecSkinnedMesh[i].attackTime < m_vecSkinnedMesh[i].attackSpeed - 1) m_vecSkinnedMesh[i].attackTime++;
			pos[i] += dir[i] * m_vecSkinnedMesh[i].t.Speed;
			m_vecSkinnedMesh[i].m_vPos = pos[i];
			m_vecSkinnedMesh[i].m_vDir = dir[i];
		}

		//�����ð��� ������ �ʾҴٸ� ���ĵ� ����
		else if (m_vecSkinnedMesh[i].time <= 90 &&
			m_vecSkinnedMesh[i].ENUM_MONSTER != MONSTER_ATTACK &&
			m_vecSkinnedMesh[i].ENUM_MONSTER != MONSTER_DEATH) {
			if (m_vecSkinnedMesh[i].attackTime < m_vecSkinnedMesh[i].attackSpeed - 1) m_vecSkinnedMesh[i].attackTime++;
			m_vecSkinnedMesh[i].ENUM_MONSTER = MONSTER_STAND;
		}
	}

	//���� �νĹ��� ������ ���������ٸ� �ൿ�� �����.
	if (m_vecSkinnedMesh[i].distance > m_vecSkinnedMesh[i].MaxRange &&
		m_vecSkinnedMesh[i].ENUM_MONSTER != MONSTER_DEATH) {
		m_vecSkinnedMesh[i].time = 0;
		//if (m_vecSkinnedMesh[i].ENUM_MONSTER != MONSTER_RUN) m_vecSkinnedMesh[i].ENUM_MONSTER = MONSTER_STAND;
		srand(time(NULL));

		D3DXVECTOR3 vDir, m_vDir, vCenter;
		m_vDir = m_vecSkinnedMesh[i].m_vDir;
		vCenter = m_vecSkinnedMesh[i].m_vPos;
		if (m_vecSkinnedMesh[i].RunCount < 0) {

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

	//����Ÿ���� �Ѿ�� ����Ÿ���� 0���� �ʱ�ȭ�ϰ�, ���ݸ�带 �����
	if (m_vecSkinnedMesh[i].attackTime >= m_vecSkinnedMesh[i].attackSpeed) {
		m_vecSkinnedMesh[i].attackTime = 0;
	}


	//������ �νİŸ�
	if (m_vecSkinnedMesh[i].distance <= m_vecSkinnedMesh[i].range ||
		m_vecSkinnedMesh[i].ENUM_MONSTER == MONSTER_ATTACK &&
		m_vecSkinnedMesh[i].ENUM_MONSTER != MONSTER_DEATH)
	{
		//���� �����ȿ� ���´ٸ�, �̵��� ���߰� ������ �غ��Ѵ�.
		m_vecSkinnedMesh[i].time = 0;
		m_vecSkinnedMesh[i].attackTime++;

		//����Ÿ���� ���� ����
		if (m_vecSkinnedMesh[i].attackTime < 90 &&
			m_vecSkinnedMesh[i].ENUM_MONSTER != MONSTER_DEATH) {
			if (m_vecSkinnedMesh[i].attackTime < 2) {
				g_pSoundManager->play("WorgHit", 1.0f);
				g_pSoundManager->play("WorgHo", 1.0f);
			}
			m_vecSkinnedMesh[i].ENUM_MONSTER = MONSTER_ATTACK;
		}
		//�ϰų� ������ ��
		else if (m_vecSkinnedMesh[i].attackTime > 90 &&
			m_vecSkinnedMesh[i].ENUM_MONSTER != MONSTER_DEATH) {
			m_vecSkinnedMesh[i].ENUM_MONSTER = MONSTER_STAND;
		}
	}


}


//���Ǿ� ����(���, ����)
void cLightningWorg::SphereRender(size_t i, D3DXMATRIXA16& m_matWorld) {
	//���Ǿ�κ� ����
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetMaterial(m_vecSkinnedMesh[i].m_Sphere.bIsPicked ?
		&m_vecSkinnedMesh[i].m_stMtlPicked : &m_vecSkinnedMesh[i].m_stMtlNone);
	//m_vecSkinnedMesh[i].m_pMeshSphere->DrawSubset(0);
}

void cLightningWorg::matUpdate(size_t i, iMap* pMap) {

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

D3DXVECTOR3 cLightningWorg::getOBBCenter(int i)
{
	return m_vecSkinnedMesh[i].MonsterOBB->GetCenterPos();
}

float cLightningWorg::getOBBhalf(int i)
{
	return m_vecSkinnedMesh[i].MonsterOBB->getMax();
}

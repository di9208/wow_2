#include "stdafx.h"
#include "cBoneSpider.h"
#include "cEnemySkinnedMesh.h"
#include <time.h>

cBoneSpider::cBoneSpider()
: m_vecSkinnedMesh(NULL)
, m_pFont(NULL)
, m_pSprite(NULL)
{
	m_pSkillOn = false;
	nCount = 0;
	D3DXMatrixIdentity(&m_matWorld);
}

cBoneSpider::~cBoneSpider()
{
	SAFE_RELEASE(m_pFont);
	SAFE_RELEASE(m_pSprite);
	//SAFE_RELEASE(m_pInvectory);
	

	for (size_t i = 0; i < m_vecSkinnedMesh.size(); i++)
	{
		for (size_t j = 0; j < m_vecSkinnedMesh[i].m_ItemSprite.size(); j++){
			SAFE_RELEASE(m_vecSkinnedMesh[i].m_ItemSprite[j].m_pTexture);
		}
		SAFE_RELEASE(m_vecSkinnedMesh[i].m_rangeMesh);
		SAFE_RELEASE(m_vecSkinnedMesh[i].m_pMeshSphere);
		SAFE_DELETE(m_vecSkinnedMesh[i].m);
	}
}

//몬스터 생성시 초기화 해주는 것
void cBoneSpider::addMonster(float x, float y, float z){
	//몬스터를 생성해줌
	EnemySkinnedMesh Monster;

	Monster.m = new cEnemySkinnedMesh;
	Monster.m->Setup("Monster/bonespider", "2.X");
	Monster.m->addMonsterPos(&Monster.m->Getwrold(), x, y, z, 0.01f);
	Monster.ENUM_MONSTER = MONSTER_STATUS::MONSTER_STAND;
	Monster.ENUM_MONSTER_KIND = MONSTER_KIND::SPIDER;
	Monster.t.HP = 50;
	Monster.MaxHP = 50;
	Monster.t.ATK = 5;
	Monster.t.DEF = 5;
	Monster.t.Speed = 0.06f;
	Monster.t.Gold = rand() % 100 + 1500;
	Monster.m_Sphere.vCenter = D3DXVECTOR3(x, y, z);
	Monster.m_Sphere.fRadius = 0.5f;
	Monster.m_Sphere.bIsPicked = false;
	Monster.fx = x;
	Monster.fy = y;
	Monster.fz = z;
	Monster.MaxRange = 10.f;
	Monster.range = 2.f;
	Monster.bi = false;
	Monster.time = 0;
	Monster.death = false;
	Monster.deathTime = 0;
	Monster.m_rangeCheck = false;
	Monster.m_rangeSphere.vCenter = D3DXVECTOR3(x, y, z);
	Monster.m_rangeSphere.fRadius = 0.2f;
	Monster.m_rangeSphere.bIsPicked = false;
	
	ZeroMemory(&Monster.m_stMtlNone, sizeof(D3DMATERIAL9));
	Monster.m_stMtlNone.Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	Monster.m_stMtlNone.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	Monster.m_stMtlNone.Specular = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

	ZeroMemory(&Monster.m_stMtlPicked, sizeof(D3DMATERIAL9));
	Monster.m_stMtlPicked.Ambient = D3DXCOLOR(0.0f, 0.8f, 0.8f, 1.0f);
	Monster.m_stMtlPicked.Diffuse = D3DXCOLOR(0.0f, 0.8f, 0.8f, 1.0f);
	Monster.m_stMtlPicked.Specular = D3DXCOLOR(0.0f, 0.8f, 0.8f, 1.0f);

	D3DXCreateSphere(g_pD3DDevice, Monster.m_Sphere.fRadius, 10, 10,
		&Monster.m_pMeshSphere, NULL);

	D3DXCreateSphere(g_pD3DDevice, Monster.m_rangeSphere.fRadius, 10, 10,
		&Monster.m_rangeMesh, NULL);

	m_vecSkinnedMesh.push_back(Monster);
}


void cBoneSpider::SetUp(){
	D3DXFONT_DESC stFD;
	srand(time(NULL));
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

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


void cBoneSpider::Update(){
	//거미 업데이트
	for (size_t i = 0; i < m_vecSkinnedMesh.size(); i++){
		//몬스터 죽음
		if (m_vecSkinnedMesh[i].t.HP <= 0) m_vecSkinnedMesh[i].ENUM_MONSTER = MONSTER_STATUS::MONSTER_DEATH;

		m_vecSkinnedMesh[i].m->Update();
		MonsterAI(i);						//몬스터의 패턴, 스킬
		MonsterStatus(i); 					//몬스터 상태, 애니메이션
	}
}


void cBoneSpider::Render(){
	D3DXMATRIXA16 matWorld;

	D3DXMatrixIdentity(&matWorld);
	for (size_t i = 0; i < m_vecSkinnedMesh.size(); i++){
		D3DXMATRIXA16 matR, matS, matT;
		D3DXMatrixScaling(&matS, 0.05f, 0.05f, 0.05f);

		D3DXMatrixRotationY(&matR, D3DX_PI * 1.5);
		D3DXVec3TransformNormal(&m_vecSkinnedMesh[i].m_vDir, &m_vecSkinnedMesh[i].m_vDir, &matR);

		D3DXVECTOR3 vUp(0, 1, 0);
		D3DXVECTOR3 vRight;
		D3DXVec3Cross(&vRight, &vUp, &m_vecSkinnedMesh[i].m_vDir);
		D3DXVec3Normalize(&vRight, &vRight);
		D3DXVec3Cross(&vUp, &m_vecSkinnedMesh[i].m_vDir, &vRight);
		D3DXMatrixLookAtLH(&matR, &D3DXVECTOR3(0, 0, 0), &m_vecSkinnedMesh[i].m_vDir, &vUp);
		D3DXMatrixTranspose(&matR, &matR);

		D3DXMatrixIdentity(&matT);
		D3DXMatrixTranslation(&matT, m_vecSkinnedMesh[i].m_vPos.x, m_vecSkinnedMesh[i].m_vPos.y, m_vecSkinnedMesh[i].m_vPos.z);

		matWorld = matS * matR * matT;

		m_vecSkinnedMesh[i].m->Render(NULL, &matWorld);
		SphereRender(i);
		if (m_vecSkinnedMesh[i].death){
			for (size_t j = 0; j < m_vecSkinnedMesh[i].m_ItemSprite.size(); j++){
				RenderUI(i, j, 10, 10, 79, 80);
			}
		}
	}
}

//
void cBoneSpider::MonsterInsic(D3DXVECTOR3 d){
	m_vPlayerPos = d;
}

//
void cBoneSpider::HarmDamage(int Damage, size_t i){
	//인자1 : 들어올 데미지, i 타겟이 된 몬스터
	if (m_vecSkinnedMesh[i].t.HP > (Damage - m_vecSkinnedMesh[i].t.DEF))
		m_vecSkinnedMesh[i].t.HP -= (Damage - m_vecSkinnedMesh[i].t.DEF);
	else m_vecSkinnedMesh[i].t.HP = 0;
}

//거미 상태
void cBoneSpider::MonsterStatus(size_t i){
	//Z키를 누르면 체력 100 달게 함
	if (g_pKeyManager->isOnceKeyDown('Z')) {
		HarmDamage(205, 0);
	}

	switch (m_vecSkinnedMesh[i].ENUM_MONSTER)
	{
	case MONSTER_STAND:
		m_vecSkinnedMesh[i].m->SetAnimationIndexBlend(0);
		break;

	case MONSTER_RUN:
		m_vecSkinnedMesh[i].m->SetAnimationIndexBlend(2);
		break;

	case MONSTER_ATTACK:
		m_vecSkinnedMesh[i].m->SetAnimationIndex(1);
		break;

	case MONSTER_HARM:

		break;

	case MONSTER_DEATH:
		m_vecSkinnedMesh[i].m->SetAnimationIndex(3);
		MonsterDeath(i);
		break;
	}
	
}

//
void cBoneSpider::SetupUI(size_t i, size_t a){
	ZeroMemory(&m_vecSkinnedMesh[i].m_StInvectory.m_stImageInfo, sizeof(D3DXIMAGE_INFO));

	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		"UI/UI_Enemy_Invectory.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_vecSkinnedMesh[i].m_StInvectory.m_stImageInfo,
		NULL,
		&m_vecSkinnedMesh[i].m_StInvectory.m_pTexture);

	for (size_t j = 0; j < a; j++){
		ZeroMemory(&m_vecSkinnedMesh[i].m_StItemSprite.m_stImageInfo, sizeof(D3DXIMAGE_INFO));

		D3DXCreateTextureFromFileEx(
			g_pD3DDevice,
			"UI/sword.png",
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			0,
			&m_vecSkinnedMesh[i].m_StItemSprite.m_stImageInfo,
			NULL,
			&m_vecSkinnedMesh[i].m_StItemSprite.m_pTexture);

		m_vecSkinnedMesh[i].m_ItemSprite.push_back(m_vecSkinnedMesh[i].m_StItemSprite);
	}
}

//
void cBoneSpider::RenderUI(size_t i, size_t j, int x, int y, int sizeX, int sizeY){
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pSprite->Draw(
		m_vecSkinnedMesh[i].m_StInvectory.m_pTexture,
		NULL,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(x, y, 0.5f),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pSprite->End();

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pSprite->Draw(
		m_vecSkinnedMesh[i].m_ItemSprite[j].m_pTexture,
		NULL,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(x + 41, y + (sizeY * j) + 181 + (j * 14), 0.5f),
		D3DCOLOR_ARGB(255, 255, 255, 255));
	m_pSprite->End();

	m_vecSkinnedMesh[i].m_ItemSprite[j].rc.left = x;
	m_vecSkinnedMesh[i].m_ItemSprite[j].rc.top = y;
	m_vecSkinnedMesh[i].m_ItemSprite[j].rc.right = sizeX + x;
	m_vecSkinnedMesh[i].m_ItemSprite[j].rc.bottom = sizeY + y;
}

//몬스터 죽었을 때
void cBoneSpider::MonsterDeath(size_t i){
		//HP가 0이 되면 죽는 모션이 나온다.
	m_vecSkinnedMesh[i].deathTime++;
	

	if (!m_vecSkinnedMesh[i].death){
		size_t a = rand() % 4 + 1;
		SetupUI(i, a);
		m_vecSkinnedMesh[i].death = true;
		}

	else {
		//죽는 모션 후 일정시간이 지나면 해당 애니메이션은 정지시킨다.
		if (m_vecSkinnedMesh[i].deathTime > 45){
			m_vecSkinnedMesh[i].m->GetAnimationController()->SetTrackEnable(0, false);

			//SAFE_RELEASE(m_vecSkinnedMesh[i].m_pMeshSphere);
			//SAFE_DELETE(m_vecSkinnedMesh[i].m);
			//m_vecSkinnedMesh.erase(m_vecSkinnedMesh.begin() + i);
		}
	}
}

//거미 AI
void cBoneSpider::MonsterAI(size_t i){
	m_vecSkinnedMesh[i].m_vPos = m_vecSkinnedMesh[i].m->GetPosition();
	m_vecSkinnedMesh[i].m_vDir = m_vecSkinnedMesh[i].m->GetDirection();

	if (m_vPlayerPos < m_vecSkinnedMesh[i].m_vPos) m_vecSkinnedMesh[i].sum = m_vecSkinnedMesh[i].m_vPos - m_vPlayerPos;
	else m_vecSkinnedMesh[i].sum = m_vPlayerPos - m_vecSkinnedMesh[i].m_vPos;

	m_vecSkinnedMesh[i].distance = D3DXVec3Length(&m_vecSkinnedMesh[i].sum);	

	if (m_vecSkinnedMesh[i].distance < m_vecSkinnedMesh[i].MaxRange &&
		m_vecSkinnedMesh[i].distance > m_vecSkinnedMesh[i].range &&
		m_vecSkinnedMesh[i].ENUM_MONSTER != MONSTER_DEATH) {
		m_vecSkinnedMesh[i].time++;
		if (m_vecSkinnedMesh[i].time > 50){
			m_vecSkinnedMesh[i].bi = true;
			m_vecSkinnedMesh[i].ENUM_MONSTER = MONSTER_RUN;
		}
		else m_vecSkinnedMesh[i].bi = false;
	}
	else if(m_vecSkinnedMesh[i].distance >= 10.f){
		m_vecSkinnedMesh[i].ENUM_MONSTER = MONSTER_STAND;
		m_vecSkinnedMesh[i].bi = false;
	}

	if (m_vecSkinnedMesh[i].ENUM_MONSTER != MONSTER_DEATH){

		D3DXMATRIXA16 matT, matR;
		D3DXMatrixIdentity(&matT);
		D3DXMatrixIdentity(&matR);

		D3DXVECTOR3 vDir = m_vPlayerPos - m_vecSkinnedMesh[i].m_vPos;

		vDir.y = m_vecSkinnedMesh[i].m_vDir.y = 0.F;

		D3DXVec3Normalize(&vDir, &vDir);
		D3DXVec3Normalize(&m_vecSkinnedMesh[i].m_vDir, &m_vecSkinnedMesh[i].m_vDir);

		if (m_vecSkinnedMesh[i].distance <= m_vecSkinnedMesh[i].range)
		{
			m_vecSkinnedMesh[i].time = 0;
			m_vecSkinnedMesh[i].ENUM_MONSTER = MONSTER_ATTACK;
			m_vecSkinnedMesh[i].bi = false;
		}

		float fDot = D3DXVec3Dot(&vDir, &m_vecSkinnedMesh[i].m_vDir);


		if (fDot <= 0.95f)
		{
			D3DXVECTOR3 vCross;
			D3DXVec3Cross(&vCross, &m_vecSkinnedMesh[i].m_vDir, &vDir);
			D3DXVec3Normalize(&vCross, &vCross);

			if (vCross.y > 0.F)
			{
				D3DXMATRIXA16 matR;
				D3DXMatrixIdentity(&matR);
				D3DXMatrixRotationY(&matR, 0.5F);
				D3DXVec3TransformNormal(&m_vecSkinnedMesh[i].m_vDir, &m_vecSkinnedMesh[i].m_vDir, &matR);
			}
			else
			{
				D3DXMATRIXA16 matR;
				D3DXMatrixIdentity(&matR);
				D3DXMatrixRotationY(&matR, -0.5F);
				D3DXVec3TransformNormal(&m_vecSkinnedMesh[i].m_vDir, &m_vecSkinnedMesh[i].m_vDir, &matR);
			}
		}
		else
		{
			m_vecSkinnedMesh[i].m_vDir = vDir;
		}

		if (m_vecSkinnedMesh[i].bi) {
			m_vecSkinnedMesh[i].m_vPos += m_vecSkinnedMesh[i].m_vDir * m_vecSkinnedMesh[i].t.Speed;


			m_vecSkinnedMesh[i].m->SetDirection(m_vecSkinnedMesh[i].m_vDir);
			m_vecSkinnedMesh[i].m->SetPosition(m_vecSkinnedMesh[i].m_vPos);
		}
	}
}

//스피어 렌더(골드, 몬스터)
void cBoneSpider::SphereRender(size_t i){
	//스피어부분 렌더
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	D3DXMATRIXA16 matR, matT;
	D3DXMatrixIdentity(&m_matWorld);

	D3DXMatrixRotationY(&matR, m_vecSkinnedMesh[i].m->GetfRotY());
	D3DXVec3TransformNormal(&m_vecSkinnedMesh[i].m->GetDirection(), &m_vecSkinnedMesh[i].m->GetDirection(), &matR);

	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT,
		m_vecSkinnedMesh[i].m->GetPosition().x,
		m_vecSkinnedMesh[i].m->GetPosition().y,
		m_vecSkinnedMesh[i].m->GetPosition().z);

	m_matWorld = matR * matT * m_vecSkinnedMesh[i].m->Getwrold();
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetMaterial(m_vecSkinnedMesh[i].m_Sphere.bIsPicked ?
		&m_vecSkinnedMesh[i].m_stMtlPicked : &m_vecSkinnedMesh[i].m_stMtlNone);
	//m_vecSkinnedMesh[i].m_pMeshSphere->DrawSubset(0);
}
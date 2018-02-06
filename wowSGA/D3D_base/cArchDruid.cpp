#include "stdafx.h"
#include "cArchDruid.h"
#include "cSkinnedMesh.h"
#include <time.h>

cArchDruid::cArchDruid()
: m_vecSkinnedMesh(NULL)
, m_pFont(NULL)
, m_pSprite(NULL)
{
	m_pSkillOn = false;
	nCount = 0;
	D3DXMatrixIdentity(&m_matWorld);
}

cArchDruid::~cArchDruid()
{
	SAFE_RELEASE(m_pFont);
	SAFE_RELEASE(m_pSprite);
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


void cArchDruid::addMonster(float x, float y, float z){
	//몬스터를 생성해줌
	Monster.m = new cSkinnedMesh;
	Monster.m->Setup("Monster/archdruid", "1.x");
	Monster.m->addMonsterPos(&Monster.m->Getwrold(), x, y + 1, z, 0.01f);
	Monster.ENUM_MONSTER = MONSTER_STATUS::MONSTER_STAND;
	Monster.ENUM_MONSTER_KIND = MONSTER_KIND::DRUID;
	Monster.t.HP = 50;
	Monster.MaxHP = 50;
	Monster.t.ATK = 51;
	Monster.t.DEF = 5;
	Monster.t.Speed = 0.03f;
	Monster.t.Gold = rand() % 100 + 1500;
	Monster.m_Sphere.vCenter = D3DXVECTOR3(x, y + 1, z);
	Monster.m_Sphere.fRadius = 0.5f;
	Monster.m_Sphere.bIsPicked = false;
	Monster.fx = x;
	Monster.fy = y;
	Monster.fz = z;
	Monster.MaxRange = 16.f;
	Monster.range = 2.f;
	Monster.time = 0;
	Monster.death = false;
	Monster.deathTime = 0;
	Monster.attackTime = 0;
	Monster.termCount = 0;
	Monster.RunCount = rand() % 250 + 10;
	Monster.m_rangeCheck = false;
	Monster.m_rangeSphere.vCenter = D3DXVECTOR3(x, y + 1, z);
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


void cArchDruid::SetUp(){
	//m_pParticle = new cParticle;

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


void cArchDruid::Update(){
	//거미 업데이트
	for (size_t i = 0; i < m_vecSkinnedMesh.size(); i++){
		//몬스터 죽음
		if (m_vecSkinnedMesh[i].t.HP <= 0) m_vecSkinnedMesh[i].ENUM_MONSTER = MONSTER_STATUS::MONSTER_DEATH;
		//if (g_pKeyManager->isStayKeyDown(VK_LEFT)) m_vecSkinnedMesh[i].m->SetfRotY(m_vecSkinnedMesh[i].m->GetfRotY() - 0.1f);

		m_vecSkinnedMesh[i].m->Update();
		MonsterAI(i);						//몬스터의 패턴, 스킬
		MonsterStatus(i); 					//몬스터 상태, 애니메이션
	}
}


void cArchDruid::Render(){
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
		if (m_vecSkinnedMesh[i].m_rangeSphere.bIsPicked) RangeSphere(i);
		SphereRender(i);
		if (m_vecSkinnedMesh[i].death){
			for (size_t j = 0; j < m_vecSkinnedMesh[i].m_ItemSprite.size(); j++){
				RenderUI(i, j, 10, 10, 79, 80);
			}
		}
	}
	if (m_pFont)
	{
		char str[128];
		sprintf(str, "runCount : %d", m_vecSkinnedMesh[0].termCount);
		std::string sText(str);
		RECT rc;
		SetRect(&rc, 100, 650, 300, 200);

		m_pFont->DrawText(NULL,
			sText.c_str(),
			sText.length(),
			&rc,
			DT_LEFT | DT_TOP | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 255));
	}
}

void cArchDruid::MonsterInsic(D3DXVECTOR3 d){
	m_vPlayerPos = d;
}

void cArchDruid::HarmDamage(int Damage, size_t i){
	//인자1 : 들어올 데미지, i 타겟이 된 몬스터
	if (m_vecSkinnedMesh[i].t.HP > (Damage - m_vecSkinnedMesh[i].t.DEF))
		m_vecSkinnedMesh[i].t.HP -= (Damage - m_vecSkinnedMesh[i].t.DEF);
	else m_vecSkinnedMesh[i].t.HP = 0;
}

//거미 상태
void cArchDruid::MonsterStatus(size_t i){
	//Z키를 누르면 체력 달게 함
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

void cArchDruid::SetupUI(size_t i, size_t a){
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

void cArchDruid::RenderUI(size_t i, size_t j, int x, int y, int sizeX, int sizeY){
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

void cArchDruid::MonsterDeath(size_t i){
	//HP가 0이 되면 죽는 모션이 나온다.
	m_vecSkinnedMesh[i].deathTime++;


	if (!m_vecSkinnedMesh[i].death){
		size_t a = rand() % 4 + 1;
		SetupUI(i, a);
		m_vecSkinnedMesh[i].death = true;
	}
}

//거미 AI1
void cArchDruid::MonsterAI(size_t i){
	m_vecSkinnedMesh[i].m_vPos = m_vecSkinnedMesh[i].m->GetPosition();
	m_vecSkinnedMesh[i].m_vDir = m_vecSkinnedMesh[i].m->GetDirection();

	if (m_vPlayerPos < m_vecSkinnedMesh[i].m_vPos) m_vecSkinnedMesh[i].sum = m_vecSkinnedMesh[i].m_vPos - m_vPlayerPos;
	else m_vecSkinnedMesh[i].sum = m_vPlayerPos - m_vecSkinnedMesh[i].m_vPos;

	m_vecSkinnedMesh[i].distance = D3DXVec3Length(&m_vecSkinnedMesh[i].sum);

	//적이 인식범위 안에 들어왔는지 확인, 물론 죽은 상태는 아니어야 함
	if (m_vecSkinnedMesh[i].distance < m_vecSkinnedMesh[i].MaxRange &&
		m_vecSkinnedMesh[i].distance > m_vecSkinnedMesh[i].range &&
		m_vecSkinnedMesh[i].ENUM_MONSTER != MONSTER_DEATH) {

		//적의 방향을 보기 위한 코드
		D3DXMATRIXA16 matR;
		D3DXMatrixIdentity(&matR);

		D3DXVECTOR3 vDir = m_vPlayerPos - m_vecSkinnedMesh[i].m_vPos;

		vDir.y = m_vecSkinnedMesh[i].m_vDir.y = 0.F;

		D3DXVec3Normalize(&vDir, &vDir);
		D3DXVec3Normalize(&m_vecSkinnedMesh[i].m_vDir, &m_vecSkinnedMesh[i].m_vDir);

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

		//적이 인식범위 안에 들어왔다면 카운트 발동
		m_vecSkinnedMesh[i].time++;

		//공격상태가 아니라면 일정시간이 지난 후 따라감
		if (m_vecSkinnedMesh[i].time > 50 &&
			m_vecSkinnedMesh[i].ENUM_MONSTER != MONSTER_ATTACK){
			m_vecSkinnedMesh[i].ENUM_MONSTER = MONSTER_RUN;
			m_vecSkinnedMesh[i].attackTime = 140;
			m_vecSkinnedMesh[i].m_vPos += m_vecSkinnedMesh[i].m_vDir * m_vecSkinnedMesh[i].t.Speed;
			m_vecSkinnedMesh[i].m->SetPosition(m_vecSkinnedMesh[i].m_vPos);
			m_vecSkinnedMesh[i].m->SetDirection(m_vecSkinnedMesh[i].m_vDir);
		}

		//일정시간이 지나지 않았다면 스탠드 상태
		else if (m_vecSkinnedMesh[i].time <= 50 &&
			m_vecSkinnedMesh[i].ENUM_MONSTER != MONSTER_ATTACK){
			m_vecSkinnedMesh[i].ENUM_MONSTER = MONSTER_STAND;
			m_vecSkinnedMesh[i].m->SetDirection(m_vecSkinnedMesh[i].m_vDir);
		}
	}

	//적이 인식범위 밖으로 빠져나갔다면 행동을 멈춘다.
	if (m_vecSkinnedMesh[i].distance > m_vecSkinnedMesh[i].MaxRange){
		m_vecSkinnedMesh[i].time = 0;
		//if (m_vecSkinnedMesh[i].ENUM_MONSTER != MONSTER_RUN) m_vecSkinnedMesh[i].ENUM_MONSTER = MONSTER_STAND;
		srand(time(NULL));

		D3DXVECTOR3 vDir, m_vDir, vCenter;
		m_vDir = m_vecSkinnedMesh[i].m->GetDirection();
		vCenter = m_vecSkinnedMesh[i].m->GetPosition();
		if (m_vecSkinnedMesh[i].RunCount < 0){
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
		
			if (m_vecSkinnedMesh[i].termCount > rand() % 300 + 50){
				m_vecSkinnedMesh[i].termCount = 0;
				m_vecSkinnedMesh[i].RunCount = rand() % 250 + 10;
			}
		}
		D3DXVec3Normalize(&vDir, &vDir);
		D3DXVec3Normalize(&m_vDir, &m_vDir);

		m_vecSkinnedMesh[i].RunCount--;
		if (m_vecSkinnedMesh[i].RunCount > 0){
			m_vecSkinnedMesh[i].termCount = 0;
			vCenter += m_vDir * m_vecSkinnedMesh[i].t.Speed;
			m_vecSkinnedMesh[i].m->SetPosition(vCenter);
			m_vecSkinnedMesh[i].m->SetDirection(m_vDir);
			m_vecSkinnedMesh[i].ENUM_MONSTER = MONSTER_RUN;
		}
	}



	//원거리 공격의 인식거리
	if (m_vecSkinnedMesh[i].distance <= m_vecSkinnedMesh[i].range + 8)
	{
		//원거리 공격 범위안에 들어온다면, 이동을 멈추고 공격을 준비한다.
		m_vecSkinnedMesh[i].time = 0;
		m_vecSkinnedMesh[i].attackTime++;
		//m_rangeCheck가 false여야 공격을 함
		//어택타임이 차면 공격하도록 함
		if (m_vecSkinnedMesh[i].attackTime < 85){
			m_vecSkinnedMesh[i].ENUM_MONSTER = MONSTER_ATTACK;
			m_vecSkinnedMesh[i].m->SetDirection(m_vecSkinnedMesh[i].m_vDir);
			if (!m_vecSkinnedMesh[i].m_rangeCheck &&
				m_vecSkinnedMesh[i].attackTime > 45 &&
				m_vecSkinnedMesh[i].attackTime < 50){
				m_vecSkinnedMesh[i].m_rangeSphere.vCenter = m_vecSkinnedMesh[i].m->GetPosition();
				m_vecSkinnedMesh[i].m_rangeDir = m_vecSkinnedMesh[i].m->GetDirection();
				m_vecSkinnedMesh[i].m_rangeCheck = true;
				m_vecSkinnedMesh[i].m_rangeSphere.bIsPicked = true;
			}
		}
		else if (m_vecSkinnedMesh[i].attackTime > 85 &&
			m_vecSkinnedMesh[i].time <= 50){
			m_vecSkinnedMesh[i].ENUM_MONSTER = MONSTER_STAND;
		}
	}

	//아직도 때리고 있는 상태라면 어택타임을 계속해서 올림
	else if (m_vecSkinnedMesh[i].ENUM_MONSTER == MONSTER_ATTACK)
		m_vecSkinnedMesh[i].attackTime++;

	//어택타임이 200이 넘어가면 어택타임을 0으로 초기화하고, 원거리 공격모드를 취소함
	if (m_vecSkinnedMesh[i].attackTime > 150) {
		m_vecSkinnedMesh[i].attackTime = 0;
		m_vecSkinnedMesh[i].m_rangeCheck = false;
	}


	// 여긴 원거리공격, 몬스터가 플레이어의 방향과 위치를 받아서 이동하는 것을 스피어에게도 적용시켜준거임
	if (m_vecSkinnedMesh[i].m_rangeSphere.bIsPicked){
		D3DXVECTOR3	vCenter;
		D3DXVECTOR3 m_vDir;
		vCenter = m_vecSkinnedMesh[i].m_rangeSphere.vCenter;
		m_vDir = m_vecSkinnedMesh[i].m_rangeDir;

		if (m_vPlayerPos < vCenter) m_vecSkinnedMesh[i].m_rangeSum = vCenter - m_vPlayerPos;
		else m_vecSkinnedMesh[i].m_rangeSum = m_vPlayerPos - vCenter;

		m_vecSkinnedMesh[i].m_rangeDistance = D3DXVec3Length(&m_vecSkinnedMesh[i].m_rangeSum);

		D3DXVec3Normalize(&m_vDir, &m_vDir);

		vCenter += m_vDir * m_vecSkinnedMesh[i].t.Speed * 6;

		m_vecSkinnedMesh[i].m_rangeSphere.vCenter = vCenter;
		m_vecSkinnedMesh[i].m_rangeSphere.vCenter.y = vCenter.y;
		m_vecSkinnedMesh[i].m_rangeDir = m_vDir;
	}

	//몬스터와 몬스터의 공격(스피어)의 거리를 잰다.
	D3DXVECTOR3 EnemyRange = m_vecSkinnedMesh[i].m_rangeSphere.vCenter - m_vecSkinnedMesh[i].m->GetPosition();
	float		fEnemyRange;
	fEnemyRange = D3DXVec3Length(&EnemyRange);

	//몬스터와 몬스터의 공격(스피어)의 거리가 멀어지거나, 플레이어와 몬스터의 공격이 충돌하면 스피어 삭제
	if (m_vecSkinnedMesh[i].m_rangeDistance <= 1.1f ||
		fEnemyRange > 20) {
		m_vecSkinnedMesh[i].m_rangeSphere.bIsPicked = false;
		m_vecSkinnedMesh[i].m_rangeCheck = false;
	}
}

void cArchDruid::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:

		break;

	case WM_LBUTTONUP:
		break;

	case WM_MOUSEMOVE:

		break;
	}
}

//스피어 렌더(골드, 몬스터)
void cArchDruid::SphereRender(size_t i){
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

void cArchDruid::RangeSphere(size_t i){

	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	D3DXMATRIXA16 matWorld;

	D3DXMatrixIdentity(&matWorld);

	D3DXMATRIXA16 matT;

	D3DXMatrixIdentity(&m_vecSkinnedMesh[i].m_matR);

	D3DXVec3TransformNormal(&m_vecSkinnedMesh[i].m_rangeDir, &m_vecSkinnedMesh[i].m_rangeDir, &m_vecSkinnedMesh[i].m_matR);

	D3DXVECTOR3 vUp(0, 1, 0);
	D3DXVECTOR3 vRight;
	D3DXVec3Cross(&vRight, &vUp, &m_vecSkinnedMesh[i].m_rangeDir);
	D3DXVec3Normalize(&vRight, &vRight);
	D3DXVec3Cross(&vUp, &m_vecSkinnedMesh[i].m_rangeDir, &vRight);
	D3DXMatrixLookAtLH(&m_vecSkinnedMesh[i].m_matR, &D3DXVECTOR3(0, 0, 0), &m_vecSkinnedMesh[i].m_rangeDir, &vUp);
	D3DXMatrixTranspose(&m_vecSkinnedMesh[i].m_matR, &m_vecSkinnedMesh[i].m_matR);

	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT,
		m_vecSkinnedMesh[i].m_rangeSphere.vCenter.x,
		m_vecSkinnedMesh[i].m_rangeSphere.vCenter.y,
		m_vecSkinnedMesh[i].m_rangeSphere.vCenter.z);

	matWorld = m_vecSkinnedMesh[i].m_matR * matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetMaterial(&m_vecSkinnedMesh[i].m_stMtlNone);
	m_vecSkinnedMesh[i].m_rangeMesh->DrawSubset(0);
}
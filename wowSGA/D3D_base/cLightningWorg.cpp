#include "stdafx.h"
#include "cLightningWorg.h"
#include "cSkinnedMesh.h"
#include "cOBB.h"
#include "iMap.h"
#include <time.h>

cLightningWorg::cLightningWorg()
: m_vecSkinnedMesh(NULL)
, m_pFont(NULL)
, m_pSprite(NULL)
{
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
		for (size_t j = 0; j < m_vecSkinnedMesh[i].m_ItemSprite.size(); j++){
			SAFE_RELEASE(m_vecSkinnedMesh[i].m_ItemSprite[j].m_pTexture);
		}
		SAFE_RELEASE(m_vecSkinnedMesh[i].m_pMeshSphere);
		SAFE_DELETE(m_vecSkinnedMesh[i].Particle);
		SAFE_DELETE(m_vecSkinnedMesh[i].MonsterOBB);
		SAFE_DELETE(m_vecSkinnedMesh[i].m);
	}
}


void cLightningWorg::addMonster(float x, float y, float z){
	//몬스터를 생성해줌

	EnemySkinnedMesh Monster;
	Monster.m = new cSkinnedMesh;
	Monster.m->Setup("Monster/lightningworg", "1.x");
	Monster.ENUM_MONSTER = MONSTER_STATUS::MONSTER_STAND;
	Monster.ENUM_MONSTER_KIND = MONSTER_KIND::DRUID;
	Monster.m_vPos = D3DXVECTOR3(x, y + 0.45, z);
	Monster.m_vDir = D3DXVECTOR3(0, 0, 1);
	Monster.t.HP = 50;
	Monster.MaxHP = 50;
	Monster.t.ATK = 3;
	Monster.t.DEF = 5;
	Monster.t.Speed = 0.08f;
	Monster.t.Gold = rand() % 100 + 1500;
	Monster.attackSpeed = 130;
	Monster.m_Sphere.vCenter = D3DXVECTOR3(x, y + 0.45, z);
	Monster.m_Sphere.fRadius = 10.f;
	Monster.m_Sphere.bIsPicked = false;
	Monster.MaxRange = 18.f;
	Monster.range = 1.f;
	Monster.time = 0;
	Monster.death = false;
	Monster.deathTime = 0;
	Monster.attackTime = 100;
	Monster.termCount = 0;
	Monster.RunCount = rand() % 250 + 10;

	Monster.Particle = new cMonsterParticle(512);
	Monster.Particle->init("Particle/alpha_tex.tga");

	D3DXMATRIXA16	World, matS, matR, matT;
	D3DXMatrixRotationX(&matR, D3DX_PI/2.0f);
	D3DXMatrixScaling(&matS, 0.011f, 0.011f, 0.011f);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, 0,0.35f,0.3);
	World = matS * matR * matT ;

	Monster.MonsterOBB = new cOBB;
	Monster.MonsterOBB->Setup(Monster.m, &World);

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

	m_vecSkinnedMesh.push_back(Monster);
}


void cLightningWorg::SetUp(){
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


void cLightningWorg::Update(iMap* map){

	//거미 업데이트
	for (size_t i = 0; i < m_vecSkinnedMesh.size(); i++){
		//몬스터 죽음
		if (m_vecSkinnedMesh[i].t.HP <= 0) m_vecSkinnedMesh[i].ENUM_MONSTER = MONSTER_STATUS::MONSTER_DEATH;

		
		matUpdate(i, map);
		m_vecSkinnedMesh[i].m->Update();
		m_vecSkinnedMesh[i].Particle->update(0.8);
		m_vecSkinnedMesh[i].MonsterOBB->Update(&m_vecSkinnedMesh[i].matRT);
		MonsterAI(i);						//몬스터의 패턴, 스킬
		MonsterStatus(i); 					//몬스터 상태, 애니메이션
	}
}


void cLightningWorg::Render(){
	for (size_t i = 0; i < m_vecSkinnedMesh.size(); i++){
		m_vecSkinnedMesh[i].m->Render(NULL, &m_vecSkinnedMesh[i].matWorld);
		m_vecSkinnedMesh[i].Particle->render();
		D3DCOLOR c = D3DCOLOR_XRGB(255, 255, 255);
		m_vecSkinnedMesh[i].MonsterOBB->Render_Debug(c, &m_vecSkinnedMesh[i].matWorld, &matWorld);

		SphereRender(i, m_vecSkinnedMesh[i].matWorld);
		if (m_vecSkinnedMesh[i].death){
			for (size_t j = 0; j < m_vecSkinnedMesh[i].m_ItemSprite.size(); j++){
				RenderUI(i, j, 10, 10, 79, 80);
			}
		}
	}
	if (m_pFont)
	{
		char str[128];
		sprintf(str, "bossHP : %d ", m_vecSkinnedMesh[0].attackTime);
		std::string sText(str);
		RECT rc;
		SetRect(&rc, 100, 630, 300, 200);

		m_pFont->DrawText(NULL,
			sText.c_str(),
			sText.length(),
			&rc,
			DT_LEFT | DT_TOP | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 255));
	}
}

void cLightningWorg::MonsterInsic(D3DXVECTOR3 d){
	m_vPlayerPos = d;
}

void cLightningWorg::HarmDamage(int Damage, size_t i){
	//인자1 : 들어올 데미지, i 타겟이 된 몬스터
	if (m_vecSkinnedMesh[i].t.HP > (Damage - m_vecSkinnedMesh[i].t.DEF))
		m_vecSkinnedMesh[i].t.HP -= (Damage - m_vecSkinnedMesh[i].t.DEF);
	else m_vecSkinnedMesh[i].t.HP = 0;
}

//거미 상태
void cLightningWorg::MonsterStatus(size_t i){
	//Z키를 누르면 체력 100 달게 함
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

void cLightningWorg::SetupUI(size_t i, size_t a){
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

void cLightningWorg::RenderUI(size_t i, size_t j, int x, int y, int sizeX, int sizeY){
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

void cLightningWorg::MonsterDeath(size_t i){
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

//거미 AI1
void cLightningWorg::MonsterAI(size_t i){
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
		if (m_vecSkinnedMesh[i].time > 90 &&
			m_vecSkinnedMesh[i].ENUM_MONSTER != MONSTER_ATTACK){
			m_vecSkinnedMesh[i].ENUM_MONSTER = MONSTER_RUN;
			if (m_vecSkinnedMesh[i].attackTime < m_vecSkinnedMesh[i].attackSpeed - 1) m_vecSkinnedMesh[i].attackTime++;
			pos[i] += dir[i] * m_vecSkinnedMesh[i].t.Speed;
			m_vecSkinnedMesh[i].m_vPos = pos[i];
			m_vecSkinnedMesh[i].m_vDir = dir[i];
		}

		//일정시간이 지나지 않았다면 스탠드 상태
		else if (m_vecSkinnedMesh[i].time <= 90 &&
			m_vecSkinnedMesh[i].ENUM_MONSTER != MONSTER_ATTACK){
			if (m_vecSkinnedMesh[i].attackTime < m_vecSkinnedMesh[i].attackSpeed - 1) m_vecSkinnedMesh[i].attackTime++;
			m_vecSkinnedMesh[i].ENUM_MONSTER = MONSTER_STAND;
		}
	}

	//적이 인식범위 밖으로 빠져나갔다면 행동을 멈춘다.
	if (m_vecSkinnedMesh[i].distance > m_vecSkinnedMesh[i].MaxRange){
		m_vecSkinnedMesh[i].time = 0;
		//if (m_vecSkinnedMesh[i].ENUM_MONSTER != MONSTER_RUN) m_vecSkinnedMesh[i].ENUM_MONSTER = MONSTER_STAND;
		srand(time(NULL));

		D3DXVECTOR3 vDir, m_vDir, vCenter;
		m_vDir = m_vecSkinnedMesh[i].m_vDir;
		vCenter = m_vecSkinnedMesh[i].m_vPos;
		if (m_vecSkinnedMesh[i].RunCount < 0){

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
		if (m_vecSkinnedMesh[i].attackTime < 90){
			m_vecSkinnedMesh[i].ENUM_MONSTER = MONSTER_ATTACK;
		}
		//하거나 쉬도록 함
		else if (m_vecSkinnedMesh[i].attackTime > 90){
			m_vecSkinnedMesh[i].ENUM_MONSTER = MONSTER_STAND;
		}
	}

	
}

void cLightningWorg::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
void cLightningWorg::SphereRender(size_t i, D3DXMATRIXA16& m_matWorld){
	//스피어부분 렌더
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetMaterial(m_vecSkinnedMesh[i].m_Sphere.bIsPicked ?
		&m_vecSkinnedMesh[i].m_stMtlPicked : &m_vecSkinnedMesh[i].m_stMtlNone);
	//m_vecSkinnedMesh[i].m_pMeshSphere->DrawSubset(0);
}

void cLightningWorg::matUpdate(size_t i, iMap* pMap){
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
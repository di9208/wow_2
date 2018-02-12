#include "stdafx.h"
#include "cMainLoading.h"
#include "cUIObject.h"
#include "cUIImage.h"
#include "loading.h"


cMainLoading::cMainLoading()
	:m_time(0)
{
}

cMainLoading::~cMainLoading()
{
	Destroy();
}

void cMainLoading::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	m_loading = new loading;

	cUIImage * main = new cUIImage;
	main->SetTexture("UI/LOADSCREENNORTHREND.png");
	main->SetPos(D3DXVECTOR3(0, 0, 1));
	Root = main;

	cUIImage * loadingbar = new cUIImage;
	loadingbar->SetTexture("UI/Loading-BarFill.png");
	loadingbar->SetPos(D3DXVECTOR3(352, 735, 0));
	Root->AddChild(loadingbar);

	cUIImage * loading = new cUIImage;
	loading->SetTexture("UI/Loading-BarBorder.png");
	loading->SetPos(D3DXVECTOR3(300, 720, 0));
	Root->AddChild(loading);

	
	this->Loading();
}

void cMainLoading::Destroy()
{
	SAFE_DELETE(m_loading);
	SAFE_RELEASE(m_pSprite);
	Root->Destroy();
}

void cMainLoading::Update()
{
	g_pTimeManager->Update();
	//14.3457
	m_time = (m_loading->getloaditemSize() / (float)m_loading->getloaditem().size())*14.4f;
	Root->GetChild()[0]->SetScal(D3DXVECTOR3(m_time,1,0));
	Root->Update();
	  
	m_loading->update();
	if (m_loading->loadingdone())
	{
		g_pSceneManager->changescene("Scene1");
	}
}

void cMainLoading::Render()
{
	Root->Render(m_pSprite);
}

void cMainLoading::Loading()
{
	m_loading->loadingSkinnedMesh("player", "player", "player.x");
	//g_pSkinnedMeshManager->Setup("player", "player", "player.x");
	m_loading->loadingSkinnedMesh("NPC", "tawo", "testtawoo.X");
	//
	m_loading->loadingSkinnedMesh("리치왕", "Monster/boss/Arthaslichking", "arthas2.x");
	m_loading->loadingSkinnedMesh("스킬", "Monster/boss/Arthaslichking", "skill.x");
	m_loading->loadingSkinnedMesh("아이스노바", "Monster/boss/Arthaslichking", "icenova.x");
	m_loading->loadingSkinnedMesh("라그나로스", "Monster/boss/ragnaros", "ragnarosF.X");
	m_loading->loadingSkinnedMesh("스킬1", "Monster/boss/ragnaros", "ragSkill1.x");
	m_loading->loadingSkinnedMesh("스킬2", "Monster/boss/ragnaros", "ragSkill2.x");
	//
	m_loading->loadingSkinnedMesh("druid1", "Monster/archdruid", "1.x");
	m_loading->loadingSkinnedMesh("druid2", "Monster/archdruid", "1.x");
	m_loading->loadingSkinnedMesh("druid3", "Monster/archdruid", "1.x");
	m_loading->loadingSkinnedMesh("druid4", "Monster/archdruid", "1.x");
	m_loading->loadingSkinnedMesh("druid5", "Monster/archdruid", "1.x");
	m_loading->loadingSkinnedMesh("druid6", "Monster/archdruid", "1.x");
	m_loading->loadingSkinnedMesh("druid7", "Monster/archdruid", "1.x");
	m_loading->loadingSkinnedMesh("druid8", "Monster/archdruid", "1.x");
	
	m_loading->loadingSkinnedMesh("bonespider1", "Monster/bonespider", "1.x");
	m_loading->loadingSkinnedMesh("bonespider2", "Monster/bonespider", "1.x");
	m_loading->loadingSkinnedMesh("bonespider3", "Monster/bonespider", "1.x");
	m_loading->loadingSkinnedMesh("bonespider4", "Monster/bonespider", "1.x");
	m_loading->loadingSkinnedMesh("bonespider5", "Monster/bonespider", "1.x");
	m_loading->loadingSkinnedMesh("bonespider6", "Monster/bonespider", "1.x");
	m_loading->loadingSkinnedMesh("bonespider7", "Monster/bonespider", "1.x");
	m_loading->loadingSkinnedMesh("bonespider8", "Monster/bonespider", "1.x");
	m_loading->loadingSkinnedMesh("bonespider9", "Monster/bonespider", "1.x");
	m_loading->loadingSkinnedMesh("bonespider10", "Monster/bonespider", "1.x");

	m_loading->loadingSkinnedMesh("worg1", "Monster/lightningworg", "1.x");
	m_loading->loadingSkinnedMesh("worg2", "Monster/lightningworg", "1.x");
	m_loading->loadingSkinnedMesh("worg3", "Monster/lightningworg", "1.x");
	m_loading->loadingSkinnedMesh("worg4", "Monster/lightningworg", "1.x");
	m_loading->loadingSkinnedMesh("worg5", "Monster/lightningworg", "1.x");
	m_loading->loadingSkinnedMesh("worg6", "Monster/lightningworg", "1.x");
	m_loading->loadingSkinnedMesh("worg7", "Monster/lightningworg", "1.x");
	m_loading->loadingSkinnedMesh("worg8", "Monster/lightningworg", "1.x");
	///
}

void cMainLoading::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}




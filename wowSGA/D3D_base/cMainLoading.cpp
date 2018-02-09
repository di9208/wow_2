#include "stdafx.h"
#include "cMainLoading.h"
#include "cUIObject.h"
#include "cUIImage.h"
#include "loading.h"


cMainLoading::cMainLoading()
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
	Root->Update();
	static float j = 0.0f;
	 j += g_pTimeManager->GetEllapsedTime()*4.5f;
	Root->GetChild()[0]->SetScal(D3DXVECTOR3(j,1,0));
	
	m_loading->update();
	if (m_loading->loadingdone())
	{
		if(j>=1)
		g_pSceneManager->changescene("Scene1");
	}
}

void cMainLoading::Render()
{
	Root->Render(m_pSprite);
}

void cMainLoading::Loading()
{
	g_pSkinnedMeshManager->Setup("player", "player", "player.x");
	g_pSkinnedMeshManager->Setup("NPC", "tawo", "testtawoo.x");

	////
	g_pSkinnedMeshManager->Setup("리치왕", "Monster/boss/Arthaslichking", "arthas2.x");
	g_pSkinnedMeshManager->Setup("스킬", "Monster/boss/Arthaslichking", "skill.x");
	g_pSkinnedMeshManager->Setup("아이스노바", "Monster/boss/Arthaslichking", "icenova.x");
	g_pSkinnedMeshManager->Setup("라그나로스", "Monster/boss/ragnaros", "ragnaros2.X");
	g_pSkinnedMeshManager->Setup("스킬1", "Monster/boss/ragnaros", "ragSkill1.x");
	g_pSkinnedMeshManager->Setup("스킬2", "Monster/boss/ragnaros", "ragSkill2.x");
	////
	g_pSkinnedMeshManager->Setup("druid1", "Monster/archdruid", "1.x");
	g_pSkinnedMeshManager->Setup("druid2", "Monster/archdruid", "1.x");
	g_pSkinnedMeshManager->Setup("druid3", "Monster/archdruid", "1.x");
	g_pSkinnedMeshManager->Setup("druid4", "Monster/archdruid", "1.x");
	g_pSkinnedMeshManager->Setup("druid5", "Monster/archdruid", "1.x");
	g_pSkinnedMeshManager->Setup("druid6", "Monster/archdruid", "1.x");
	g_pSkinnedMeshManager->Setup("druid7", "Monster/archdruid", "1.x");
	g_pSkinnedMeshManager->Setup("druid8", "Monster/archdruid", "1.x");
	//g_pSkinnedMeshManager->Setup("druid1", "Monster/archdruid", "1.x");
	////
	g_pSkinnedMeshManager->Setup("bonespider1", "Monster/bonespider", "1.x");
	g_pSkinnedMeshManager->Setup("bonespider2", "Monster/bonespider", "1.x");
	g_pSkinnedMeshManager->Setup("bonespider3", "Monster/bonespider", "1.x");
	g_pSkinnedMeshManager->Setup("bonespider4", "Monster/bonespider", "1.x");
	g_pSkinnedMeshManager->Setup("bonespider5", "Monster/bonespider", "1.x");
	g_pSkinnedMeshManager->Setup("bonespider6", "Monster/bonespider", "1.x");
	g_pSkinnedMeshManager->Setup("bonespider7", "Monster/bonespider", "1.x");
	g_pSkinnedMeshManager->Setup("bonespider8", "Monster/bonespider", "1.x");
	g_pSkinnedMeshManager->Setup("bonespider9", "Monster/bonespider", "1.x");
	g_pSkinnedMeshManager->Setup("bonespider10", "Monster/bonespider", "1.x");
	//g_pSkinnedMeshManager->Setup("bonespider1", "Monster/bonespider", "1.x");
	g_pSkinnedMeshManager->Setup("worg1", "Monster/lightningworg", "1.x");
	g_pSkinnedMeshManager->Setup("worg2", "Monster/lightningworg", "1.x");
	g_pSkinnedMeshManager->Setup("worg3", "Monster/lightningworg", "1.x");
	g_pSkinnedMeshManager->Setup("worg4", "Monster/lightningworg", "1.x");
	g_pSkinnedMeshManager->Setup("worg5", "Monster/lightningworg", "1.x");
	g_pSkinnedMeshManager->Setup("worg6", "Monster/lightningworg", "1.x");
	g_pSkinnedMeshManager->Setup("worg7", "Monster/lightningworg", "1.x");
	g_pSkinnedMeshManager->Setup("worg8", "Monster/lightningworg", "1.x");
	///
}

void cMainLoading::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}




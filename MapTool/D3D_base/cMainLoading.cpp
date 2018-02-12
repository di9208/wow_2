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
	Root->GetChild()[0]->SetScale(D3DXVECTOR3(j,1,0));
	
	m_loading->update();
	if (m_loading->loadingdone())
	{
		if(j>=1)
		g_pSceneManager->changescene("Testing");
	}
}

void cMainLoading::Render()
{
	Root->Render(m_pSprite);
}

void cMainLoading::Loading()
{
	g_pSkinnedMeshManager->Setup("Tree1", "MapTool_Unit", "Tree11.X");
	g_pSkinnedMeshManager->Setup("Tree2", "MapTool_Unit", "Tree11.X");
	g_pSkinnedMeshManager->Setup("Tree3", "MapTool_Unit", "Tree11.X");
	g_pSkinnedMeshManager->Setup("Tree4", "MapTool_Unit", "Tree11.X");
	g_pSkinnedMeshManager->Setup("Tree5", "MapTool_Unit", "Tree11.X");
	g_pSkinnedMeshManager->Setup("Tree6", "MapTool_Unit", "Tree11.X");
	g_pSkinnedMeshManager->Setup("Tree7", "MapTool_Unit", "Tree11.X");
	g_pSkinnedMeshManager->Setup("Tree8", "MapTool_Unit", "Tree11.X");
	g_pSkinnedMeshManager->Setup("Tree9", "MapTool_Unit", "Tree11.X");
	g_pSkinnedMeshManager->Setup("Tree10", "MapTool_Unit", "Tree11.X");
	g_pSkinnedMeshManager->Setup("Tree11", "MapTool_Unit", "Tree11.X");
	g_pSkinnedMeshManager->Setup("Tree12", "MapTool_Unit", "Tree11.X");
	g_pSkinnedMeshManager->Setup("Tree13", "MapTool_Unit", "Tree11.X");
	g_pSkinnedMeshManager->Setup("Tree14", "MapTool_Unit", "Tree11.X");
	g_pSkinnedMeshManager->Setup("Tree15", "MapTool_Unit", "Tree11.X");
	g_pSkinnedMeshManager->Setup("Tree16", "MapTool_Unit", "Tree11.X");
	g_pSkinnedMeshManager->Setup("Tree17", "MapTool_Unit", "Tree11.X");
	g_pSkinnedMeshManager->Setup("Tree18", "MapTool_Unit", "Tree11.X");
	g_pSkinnedMeshManager->Setup("Tree19", "MapTool_Unit", "Tree11.X");
	g_pSkinnedMeshManager->Setup("Tree20", "MapTool_Unit", "Tree11.X");
	g_pSkinnedMeshManager->Setup("Tree21", "MapTool_Unit", "Tree11.X");
	g_pSkinnedMeshManager->Setup("Tree22", "MapTool_Unit", "Tree11.X");

	g_pSkinnedMeshManager->Setup("Tree16", "MapTool_Unit", "Tree11.X");


	g_pSkinnedMeshManager->Setup("NPC", "MapTool_Unit", "testtawoo.X");
	g_pSkinnedMeshManager->Setup("player", "MapTool_Unit", "player.X");
	g_pSkinnedMeshManager->Setup("lichking", "MapTool_Unit", "arthas.X");
	g_pSkinnedMeshManager->Setup("bonespider1", "MapTool_Unit", "bonespider.X");
	g_pSkinnedMeshManager->Setup("bonespider2", "MapTool_Unit", "bonespider.X");
	g_pSkinnedMeshManager->Setup("bonespider3", "MapTool_Unit", "bonespider.X");
	g_pSkinnedMeshManager->Setup("bonespider4", "MapTool_Unit", "bonespider.X");
	g_pSkinnedMeshManager->Setup("bonespider5", "MapTool_Unit", "bonespider.X");
	g_pSkinnedMeshManager->Setup("bonespider6", "MapTool_Unit", "bonespider.X");
	g_pSkinnedMeshManager->Setup("bonespider7", "MapTool_Unit", "bonespider.X");
	g_pSkinnedMeshManager->Setup("bonespider8", "MapTool_Unit", "bonespider.X");
	g_pSkinnedMeshManager->Setup("bonespider9", "MapTool_Unit", "bonespider.X");
	g_pSkinnedMeshManager->Setup("bonespider10", "MapTool_Unit", "bonespider.X");
	g_pSkinnedMeshManager->Setup("druid1", "MapTool_Unit", "druid.X");
	g_pSkinnedMeshManager->Setup("druid2", "MapTool_Unit", "druid.X");
	g_pSkinnedMeshManager->Setup("druid3", "MapTool_Unit", "druid.X");
	g_pSkinnedMeshManager->Setup("druid4", "MapTool_Unit", "druid.X");
	g_pSkinnedMeshManager->Setup("druid5", "MapTool_Unit", "druid.X");
	g_pSkinnedMeshManager->Setup("druid6", "MapTool_Unit", "druid.X");
	g_pSkinnedMeshManager->Setup("worg1", "MapTool_Unit", "worg.X");
	g_pSkinnedMeshManager->Setup("worg2", "MapTool_Unit", "worg.X");
	g_pSkinnedMeshManager->Setup("worg3", "MapTool_Unit", "worg.X");
	g_pSkinnedMeshManager->Setup("worg4", "MapTool_Unit", "worg.X");
	g_pSkinnedMeshManager->Setup("worg5", "MapTool_Unit", "worg.X");
	g_pSkinnedMeshManager->Setup("worg6", "MapTool_Unit", "worg.X");
	g_pSkinnedMeshManager->Setup("worg7", "MapTool_Unit", "worg.X");
	g_pSkinnedMeshManager->Setup("worg8", "MapTool_Unit", "worg.X");
	g_pSkinnedMeshManager->Setup("rag", "MapTool_Unit", "ragnaros.X");

}

void cMainLoading::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}




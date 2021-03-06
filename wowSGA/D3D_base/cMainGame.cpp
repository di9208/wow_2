#include "stdafx.h"
#include "cMainGame.h"


cMainGame::cMainGame() 
{
}


cMainGame::~cMainGame()
{

}
void cMainGame::Destroy()
{
	g_pSceneManager->Destroy();
}

void cMainGame::Setup()
{
	g_pSceneManager->addscene("Loading", new cMainLoading);
	g_pSceneManager->addscene("Scene1", new cScene1);
	g_pSceneManager->addscene("Scene2", new cScene2);
	g_pSceneManager->addscene("Change", new cSceneChange);
	g_pSceneManager->changescene("Loading");

}

void cMainGame::Update()
{
	g_pSceneManager->Update();
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 0),
		1.0f, 0);

	g_pD3DDevice->BeginScene();

	// TODO : �׸���
	g_pSceneManager->Render();



	///////////////////////////////////////////

	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	g_pSceneManager->WndProc(hWnd, message, wParam, lParam);
}
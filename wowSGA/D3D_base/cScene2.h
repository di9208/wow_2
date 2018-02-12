#pragma once
#include "cGameManager.h"

class cCamera;
class cPlayer_Enemy;
class shop_TEST_CLASS;
class cStage2;
class cFrustum;
class cSkyBox;

class cScene2:public cGameManager
{
private:
	
	cCamera * m_pCamera;
	cPlayer_Enemy*	m_Player_Enemy;
	cStage2*		m_Stage2;
	cFrustum*		m_Frustum;
	cSkyBox* m_skybox;
public:
	cScene2();
	~cScene2();

	void SetLight();

	void Setup();
	void Destroy();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};


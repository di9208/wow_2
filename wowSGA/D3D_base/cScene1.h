#pragma once
#include "cGameManager.h"

class cCamera;
class cGrid;
class cPlayer_Enemy;
class shop_TEST_CLASS;
class cStage1;
class cFrustum;
class cSkyBox;

class cScene1:public cGameManager
{
private:
	cCamera * m_pCamera;
	cGrid*		m_pGrid;
	cPlayer_Enemy*	m_Player_Enemy;
	shop_TEST_CLASS* m_shop_TEST_CLASS;
	cStage1*		m_Stage1;
	cFrustum*		m_Frustum;
	cSkyBox* m_skybox;
public:
	cScene1();
	~cScene1();

	void SetLight();

	void Setup();
	void Destroy();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};


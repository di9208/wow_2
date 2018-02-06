#pragma once
#include "cGameManager.h"
#include "cMainLoading.h"

class cCamera;
class cGrid;
class cMaptool;
class cCube;
class cHeightMap;
class cFrustum;
class cSkinnedMesh;
class cTesting;

class cMainGame:public cGameManager
{
private:
	cCamera*	m_pCamera;

	cGrid*		m_pGrid;
	cMaptool*	m_maptool;
	cCube* m_cube;
	// sprite
	LPD3DXSPRITE				m_pSprite;

	cFrustum* frustum;
	cSkinnedMesh* m;
	LPD3DXFRAME f;
	

public:
	cMainGame();
	~cMainGame();

	void SetLight();

	virtual void Setup();
	virtual void Destroy();
	virtual void Update();
	virtual void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};


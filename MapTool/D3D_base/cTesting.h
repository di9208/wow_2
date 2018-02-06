#pragma once
#include "cGameManager.h"

class cCamera;
class cGrid;
class cMaptool;
class cCube;
class cHeightMap;
class cFrustum;
class cSkinnedMesh;
class cSkyBox;

class cTesting:public cGameManager
{
private:
	cCamera * m_pCamera;

	cGrid*		m_pGrid;
	cMaptool*	m_maptool;
	cCube* m_cube;
	cSkyBox * m_sky;

	// sprite
	LPD3DXSPRITE				m_pSprite;

	cFrustum* frustum;
	cSkinnedMesh* m;
	LPD3DXFRAME f;


public:
	cTesting();
	virtual ~cTesting();

	void SetLight();
	virtual void Setup();
	virtual void Destroy();
	virtual void Update();
	virtual void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};


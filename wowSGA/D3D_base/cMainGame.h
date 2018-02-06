#pragma once

class cCamera;
class cGrid;
//class cPlayer;
//class cEnemyControl;
class cPlayer_Enemy;
class shop_TEST_CLASS;

class cMainGame
{
private:
	cCamera*	m_pCamera;
	cGrid*		m_pGrid;
	//cPlayer*	m_pPlayer;
	//cEnemyControl*	m_pMonster;
	cPlayer_Enemy*	m_Player_Enemy;
	shop_TEST_CLASS* m_shop_TEST_CLASS;

	

	// sprite
	LPD3DXSPRITE				m_pSprite;

public:
	cMainGame();
	~cMainGame();

	void SetLight();

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};


#pragma once
class cCamera
{
private:
	SYNTHESIZE(D3DXVECTOR3,	m_vEye, Eye);
	D3DXVECTOR3		m_vLookAt;
	D3DXVECTOR3		m_vUp;

	POINT			m_ptPrevMouse;
	bool			m_isLButtonDown;
	float			m_fCamDist;
	D3DXVECTOR3		m_vCamRotAngle;

	D3DXVECTOR3*	m_pvTarget;

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_dir;
	float RotY;

public:
	cCamera();
	~cCamera();

	void Setup(D3DXVECTOR3* pvTarget);
	void Update();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};


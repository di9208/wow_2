#pragma once
class cCamera
{
private:
	D3DXVECTOR3		m_vEye;
	D3DXVECTOR3		m_vLookAt;
	D3DXVECTOR3		m_vUp;

	POINT			m_ptPrevMouse;
	bool			m_isLButtonDown;
	float			m_fCamDist;
	D3DXVECTOR3		m_vCamRotAngle;

	D3DXVECTOR3*	m_pvTarget;
	float RotY;
public:
	cCamera();
	~cCamera();

	void Setup(D3DXVECTOR3* pvTarget, float roty);
	void Update();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	D3DXVECTOR3 GetEye() { return m_vEye; }
};


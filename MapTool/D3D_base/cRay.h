#pragma once
class cRay
{
private:
	SYNTHESIZE(D3DXVECTOR3, m_vPos,Pos);
	SYNTHESIZE(D3DXVECTOR3 ,m_vDir,Dir);
	SYNTHESIZE(D3DXVECTOR3, m_vNDir, NDir);
	float t;
	float a;
public:
	cRay();
	~cRay();

	static cRay RayAtViewSpace(int nScreenX, int nScreenY);
	static cRay RayAtWorldSpace(int nScreenX, int nScreenY);

	bool IsPicked(ST_SPHERE* pS);

	bool IsPicked(D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3& dis);
};


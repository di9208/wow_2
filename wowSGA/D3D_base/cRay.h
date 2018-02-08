#pragma once
#include "cUnit.h"
class cRay
{
private:
	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_vDir;

public:
	cRay();
	~cRay();

	static cRay RayAtViewSpace(int nScreenX, int nScreenY);
	static cRay RayAtWorldSpace(int nScreenX, int nScreenY);

	bool IsPicked(Enemy_Sphere* pS);
	bool IsPicked(ST_SPHERE* pS);
	bool IntersectTri(IN D3DXVECTOR3& v0, IN D3DXVECTOR3& v1, IN D3DXVECTOR3& v2, OUT D3DXVECTOR3& pickPoision);

};


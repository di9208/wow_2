#include "stdafx.h"
#include "cRay.h"


cRay::cRay()
	: m_vPos(0, 0, 0)
	, m_vDir(0, 0, 0)
	, m_vNDir(0, 0, 0)
	,a(9000.0f)
{
}


cRay::~cRay()
{
}

cRay cRay::RayAtViewSpace(int nScreenX, int nScreenY)
{
	D3DVIEWPORT9 vp;
	g_pD3DDevice->GetViewport(&vp);

	D3DXMATRIXA16 matProj;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);

	cRay r;
	r.m_vDir.x = ((2.0 * nScreenX) / vp.Width - 1.0f) / matProj._11;
	r.m_vDir.y = ((-2.0 * nScreenY) / vp.Height + 1.0f) / matProj._22;
	r.m_vDir.z = 1.0f;

	return r;
}

cRay cRay::RayAtWorldSpace(int nScreenX, int nScreenY)
{
	cRay r = RayAtViewSpace(nScreenX, nScreenY);
	D3DXMATRIXA16 matView, matInvView;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matInvView, 0, &matView);

	D3DXVec3TransformCoord(&r.m_vPos, &r.m_vPos, &matInvView);

	r.m_vNDir = r.m_vDir;
	D3DXVec3TransformCoord(&r.m_vNDir, &r.m_vNDir, &matInvView);
	D3DXVec3TransformNormal(&r.m_vDir, &r.m_vDir, &matInvView);
	//D3DXVec3Normalize(&r.m_vNDir, &r.m_vNDir);
	D3DXVec3Normalize(&r.m_vDir, &r.m_vDir);

	
	

	return r;
}

bool cRay::IsPicked(ST_SPHERE * pS)
{
	cRay r = (*this);

	D3DXMATRIXA16	matInvWorld;
	D3DXMatrixIdentity(&matInvWorld);
	matInvWorld._41 = -pS->vCenter.x;
	matInvWorld._42 = -pS->vCenter.y;
	matInvWorld._43 = -pS->vCenter.z;

	D3DXVec3TransformCoord(&r.m_vPos, &r.m_vPos, &matInvWorld);
	D3DXVec3TransformNormal(&r.m_vDir, &r.m_vDir, &matInvWorld);

	float vv = D3DXVec3Dot(&r.m_vDir, &r.m_vDir);
	float qv = D3DXVec3Dot(&r.m_vPos, &r.m_vDir);
	float qq = D3DXVec3Dot(&r.m_vPos, &r.m_vPos);
	float rr = pS->fRadius * pS->fRadius;

	return qv * qv - vv * (qq - rr) >= 0;
}
bool cRay::IsPicked(D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3& dis)
{

	cRay r = (*this);
	

	if (D3DXIntersectTri(&v0, &v1, &v2, &m_vPos, &m_vDir, 0, 0, &t))
	{
		if (a > t)
			a = t;
		dis = m_vPos + a * m_vDir;
		return true;
	}
	else
		return false;

}
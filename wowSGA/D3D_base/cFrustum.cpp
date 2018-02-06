#include "stdafx.h"
#include "cFrustum.h"


cFrustum::cFrustum()
{
}


cFrustum::~cFrustum()
{
}

void cFrustum::SetupVertex()
{
	D3DXMATRIXA16 projection, view, inviewprojection;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &view);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &projection);

	inviewprojection = view * projection;
	vertex[0] = D3DXVECTOR3(-1.0f, -1.0f, 0);
	vertex[1] = D3DXVECTOR3(-1.0f, 1.0f, 0);
	vertex[2] = D3DXVECTOR3(1.0f, 1.0f, 0);
	vertex[3] = D3DXVECTOR3(1.0f, -1.0f, 0);

	vertex[4] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	vertex[5] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	vertex[6] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	vertex[7] = D3DXVECTOR3(1.0f, -1.0f, 1.0f);

	D3DXMatrixInverse(&inviewprojection, nullptr, &inviewprojection);

	for (int i = 0; i < 8; i++)
	{
		D3DXVec3TransformCoord(&vertex[i], &vertex[i], &inviewprojection);
	}
	//ax +by + cz + d  Plane
	//near , far, top, bottom, left, right


	//near
	D3DXPlaneFromPoints(&plane[0], &vertex[0], &vertex[1], &vertex[2]);
	//far
	D3DXPlaneFromPoints(&plane[1], &vertex[7], &vertex[6], &vertex[5]);
	//top
	D3DXPlaneFromPoints(&plane[2], &vertex[1], &vertex[5], &vertex[6]);
	//bottom
	D3DXPlaneFromPoints(&plane[3], &vertex[4], &vertex[0], &vertex[3]);
	//left
	D3DXPlaneFromPoints(&plane[4], &vertex[4], &vertex[5], &vertex[1]);
	//right
	D3DXPlaneFromPoints(&plane[5], &vertex[3], &vertex[2], &vertex[6]);
}

bool cFrustum::isInside(D3DXVECTOR3 * v)
{
	float dis1 = D3DXPlaneDotCoord(&plane[0], v);
	float dis2 = D3DXPlaneDotCoord(&plane[1], v);
	float dis3 = D3DXPlaneDotCoord(&plane[2], v);
	float dis4 = D3DXPlaneDotCoord(&plane[3], v);
	float dis5 = D3DXPlaneDotCoord(&plane[4], v);
	float dis6 = D3DXPlaneDotCoord(&plane[5], v);
	if (dis1 > 0+ EPSILON || dis2 > 0 + EPSILON || dis3 > 0+ EPSILON || dis4 > 0+ EPSILON || dis5 > 0+ EPSILON || dis6 > 0+ EPSILON)
		return false;

	return true;
}

bool cFrustum::isInside(D3DXVECTOR3 * v, float radius)
{
	float dis1 = D3DXPlaneDotCoord(&plane[0], v);
	float dis2 = D3DXPlaneDotCoord(&plane[1], v);
	float dis3 = D3DXPlaneDotCoord(&plane[2], v);
	float dis4 = D3DXPlaneDotCoord(&plane[3], v);
	float dis5 = D3DXPlaneDotCoord(&plane[4], v);
	float dis6 = D3DXPlaneDotCoord(&plane[5], v);
	if (dis1 > radius+ EPSILON || dis2 > radius+ EPSILON || dis3 > radius+ EPSILON || dis4 > radius+ EPSILON || dis5 > radius+ EPSILON || dis6 > radius+ EPSILON)
		return false;

	return true;
}

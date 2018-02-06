#include "stdafx.h"
#include "cOBB.h"
#include "cSkinnedMesh.h"

#include <sstream>
#include "cOBB.h"

//std::string Convert(float number) {
//	std::ostringstream buff;
//	buff << number;
//	return buff.str();
//}

cOBB::cOBB()
	:m_pMeshSphere(NULL)
{
}

cOBB::~cOBB()
{
	SAFE_RELEASE(m_pMeshSphere);
	SAFE_RELEASE(m_pFont);
}

void cOBB::Setup(cSkinnedMesh* pSkinnedMesh, D3DXMATRIXA16* playerWorld)
{
	SetFont();
	D3DXVECTOR3 vMin = pSkinnedMesh->GetMin();//-11.3,-29.5,-0.07
	D3DXVECTOR3 vMax = pSkinnedMesh->GetMax();//11.3,20.5,102.9

	D3DXVec3TransformCoord(&vMin, &vMin, playerWorld);
	D3DXVec3TransformCoord(&vMax, &vMax, playerWorld);

	m_vOrgCenterPos = (vMin + vMax) / 2.0f;

	m_vOrgCenterPos.z *= -1;
	//m_vOrgCenterPos.y =0.0f; 

	//float dummy;

	//dummy = m_vOrgCenterPos.z;
	//m_vOrgCenterPos.z = m_vOrgCenterPos.y;
	//m_vOrgCenterPos.y = dummy;

	m_vOrgAxisDir[0] = D3DXVECTOR3(1, 0, 0);
	m_vOrgAxisDir[1] = D3DXVECTOR3(0, 1, 0);
	m_vOrgAxisDir[2] = D3DXVECTOR3(0, 0, 1);

	m_fAxisLen[0] = fabs(vMax.x - vMin.x);
	m_fAxisLen[1] = fabs(vMax.y - vMin.y);
	m_fAxisLen[2] = fabs(vMax.z - vMin.z);

	m_fAxisHalfLen[0] = m_fAxisLen[0] / 2.0f;
	m_fAxisHalfLen[1] = m_fAxisLen[1] / 2.0f;
	m_fAxisHalfLen[2] = m_fAxisLen[2] / 2.0f;

	//m_vAxisDir.resize(3);

	D3DXMatrixIdentity(&m_matWorldTM);
}

void cOBB::Update(D3DXMATRIXA16* pMatWorld)
{
	if (pMatWorld)
	{
		m_matWorldTM = (*pMatWorld);
	}

	for (int i = 0; i < 3; i++)
	{
		D3DXVec3TransformNormal(&m_vAxisDir[i],
			&m_vOrgAxisDir[i],
			&m_matWorldTM);
	}

	D3DXVec3TransformCoord(&m_vCenterPos,
		&m_vOrgCenterPos,
		&m_matWorldTM);

}

bool cOBB::IsCollision(cOBB * pObb1, cOBB * pObb2)
{
	/*float cos[3][3];
	float absCos[3][3];
	float dist[3];
	float r0, r1, r2;
	bool isExistParaller = false;
	float cutOff = 0.9999999f;

	D3DXVECTOR3 D = pObb2->m_vCenterPos -m_vCenterPos;

	for (int i = 0; i < 3; i++)
	{
	D3DXVECTOR3 Dummy = pObb2->GetAxisDir()[i];
	cos[0][i] = D3DXVec3Dot(&m_vAxisDir[0], &Dummy);
	absCos[0][i] = abs(cos[0][i]);
	if (absCos[0][i] > cutOff)
	isExistParaller = true;
	}
	dist[0] = D3DXVec3Dot(&D, &m_vAxisDir[0]);
	r0 = abs(dist[0]);
	r1 = m_fAxisLen[0];
	r2 = pObb2->GetAxisLen()[0]*absCos[0][0] + pObb2->GetAxisLen()[1]*absCos[0][1] + pObb2->GetAxisLen()[2]*absCos[0][2];
	if (r0 = r1 + r2)
	return false;


	for (int i = 0; i < 3; i++)
	{
	cos[1][i] = D3DXVec3Dot(&m_vAxisDir[1], &pObb2->GetAxisDir()[i]);
	absCos[1][i] = abs(cos[1][i]);
	if (absCos[1][i] > cutOff)
	isExistParaller = true;
	}
	dist[1] = D3DXVec3Dot(&D, &m_vAxisDir[1]);
	r0 = abs(dist[1]);
	r1 = m_fAxisLen[1];
	r2 = pObb2->GetAxisLen()[0]*absCos[1][0] + pObb2->GetAxisLen()[1]*absCos[1][1] + pObb2->GetAxisLen()[2]*absCos[1][2];
	if (r0 = r1 + r2)
	return false;

	for (int i = 0; i < 3; i++)
	{
	cos[2][i] = D3DXVec3Dot(&m_vAxisDir[2], &pObb2->GetAxisDir()[i]);
	absCos[2][i] = abs(cos[2][i]);
	if (absCos[2][i] > cutOff)
	isExistParaller = true;
	}
	dist[2] = D3DXVec3Dot(&D, &m_vAxisDir[2]);
	r0 = abs(dist[2]);
	r1 = m_fAxisLen[2];
	r2 = pObb2->GetAxisLen()[0]*absCos[2][0] + pObb2->GetAxisLen()[1]*absCos[2][1] + pObb2->GetAxisLen()[2]*absCos[2][2];
	if (r0 = r1 + r2)
	return false;

	r0 = abs(D3DXVec3Dot(&D, &pObb2->GetAxisDir()[0]));
	r1 = m_fAxisLen[0] * absCos[0][0] + m_fAxisLen[1] * absCos[1][0] + m_fAxisLen[2] * absCos[2][0];
	r2 = pObb2->GetAxisLen()[0];
	if (r0 = r1 + r2)
	return false;

	r0 = abs(D3DXVec3Dot(&D, &pObb2->GetAxisDir()[1]));
	r1 = m_fAxisLen[0] * absCos[0][1] + m_fAxisLen[1] * absCos[1][1] + m_fAxisLen[2] * absCos[2][1];
	r2 = pObb2->GetAxisLen()[1];
	if (r0 = r1 + r2)
	return false;

	r0 = abs(D3DXVec3Dot(&D, &pObb2->GetAxisDir()[2]));
	r1 = m_fAxisLen[0] * absCos[0][2] + m_fAxisLen[1] * absCos[1][2] + m_fAxisLen[2] * absCos[2][2];
	r2 = pObb2->GetAxisLen()[2];
	if (r0 =r1 + r2)
	return false;

	if (isExistParaller)
	return true;

	r0 = abs(dist[2] * cos[1][0] - dist[1] * cos[2][0]);
	r1 = m_fAxisLen[1] * absCos[2][0] + m_fAxisLen[2] * absCos[1][0];
	r2 = pObb2->GetAxisLen()[1]*absCos[0][2] + pObb2->GetAxisLen()[2] * absCos[0][1];
	if (r0 = r1 + r2)
	return false;

	r0 = abs(dist[2] * cos[1][1] - dist[1] * cos[2][1]);
	r1 = m_fAxisLen[1] * absCos[2][1] + m_fAxisLen[2] * absCos[1][1];
	r2 = pObb2->GetAxisLen()[0]*absCos[0][2] + pObb2->GetAxisLen()[2] * absCos[0][0];
	if (r0 = r1 + r2)
	return false;

	r0 = abs(dist[2] * cos[1][2] - dist[1] * cos[2][2]);
	r1 = m_fAxisLen[1] * absCos[2][2] + m_fAxisLen[2] * absCos[1][2];
	r2 = pObb2->GetAxisLen()[0]*absCos[0][1] + pObb2->GetAxisLen()[1] * absCos[0][0];
	if (r0 = r1 + r2)
	return false;

	r0 = abs(dist[0] * cos[2][0] - dist[2] * cos[0][0]);
	r1 = m_fAxisLen[0] * absCos[2][0] + m_fAxisLen[2] * absCos[0][0];
	r2 = pObb2->GetAxisLen()[1]*absCos[1][2] + pObb2->GetAxisLen()[2] * absCos[1][1];
	if (r0 = r1 + r2)
	return false;

	r0 = abs(dist[0] * cos[2][1] - dist[2] * cos[0][1]);
	r1 = m_fAxisLen[0] * absCos[2][1] + m_fAxisLen[2] * absCos[0][1];
	r2 = pObb2->GetAxisLen()[0]*absCos[1][2] + pObb2->GetAxisLen()[2] * absCos[1][0];
	if (r0 = r1 + r2)
	return false;

	r0 = abs(dist[0] * cos[2][2] - dist[2] * cos[0][2]);
	r1 = m_fAxisLen[0] * absCos[2][2] + m_fAxisLen[2] * absCos[0][2];
	r2 = pObb2->GetAxisLen()[0]*absCos[1][1] + pObb2->GetAxisLen()[1] * absCos[1][0];
	if (r0 = r1 + r2)
	return false;

	r0 = abs(dist[1] * cos[0][0] - dist[0] * cos[1][0]);
	r1 = m_fAxisLen[0] * absCos[1][0] + m_fAxisLen[1] * absCos[0][0];
	r2 = pObb2->GetAxisLen()[1]*absCos[2][2] + pObb2->GetAxisLen()[2] * absCos[2][1];
	if (r0 = r1 + r2)
	return false;

	r0 = abs(dist[1] * cos[0][1] - dist[0] * cos[1][1]);
	r1 = m_fAxisLen[0] * absCos[1][1] + m_fAxisLen[1] * absCos[0][1];
	r2 = pObb2->GetAxisLen()[0]*absCos[2][2] + pObb2->GetAxisLen()[2] * absCos[2][0];
	if (r0 = r1 + r2)
	return false;

	r0 = abs(dist[1] * cos[0][2] - dist[0] * cos[1][2]);
	r1 = m_fAxisLen[0] * absCos[1][2] + m_fAxisLen[1] * absCos[0][2];
	r2 = pObb2->GetAxisLen()[0]*absCos[2][1] + pObb2->GetAxisLen()[1]* absCos[2][0];
	if (r0 = r1 + r2)
	return false;*/

	// 출처 : http://www.gingaminga.com/Data/Note/oriented_bounding_boxes/

	float cos[3][3];
	float absCos[3][3];
	float dist[3];
	float r0, r1, r2;

	bool isExistParaller = false;
	float cutOff = 0.9999999f;

	D3DXVECTOR3 D;
	D.x = pObb2->m_vCenterPos.x - pObb1->m_vCenterPos.x;
	D.y = pObb2->m_vCenterPos.y - pObb1->m_vCenterPos.y;
	D.z = pObb2->m_vCenterPos.z - pObb1->m_vCenterPos.z;
	// obb 1의 평면 3개를 기준으로 obb2 의 축 3개를 검사
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cos[i][j] = D3DXVec3Dot(&pObb1->m_vAxisDir[i], &pObb2->m_vAxisDir[j]);
			absCos[i][j] = abs(cos[i][j]);
			if (absCos[i][j] > cutOff)
				isExistParaller = true;
		}

		dist[i] = D3DXVec3Dot(&pObb2->m_vAxisDir[i], &D);
		r0 = abs(dist[i]);

		r1 = pObb1->m_fAxisHalfLen[i];
		r2 = pObb2->m_fAxisHalfLen[0] * absCos[i][0] +
			pObb2->m_fAxisHalfLen[1] * absCos[i][1] +
			pObb2->m_fAxisHalfLen[2] * absCos[i][2];

		if (r0 > r1 + r2)
			return false;

		dist[i] = D3DXVec3Dot(&pObb1->m_vAxisDir[i], &D);
		r0 = abs(dist[i]);

		r1 = pObb1->m_fAxisHalfLen[0] * absCos[i][0] +
			pObb1->m_fAxisHalfLen[1] * absCos[i][1] +
			pObb1->m_fAxisHalfLen[2] * absCos[i][2];
		r2 = pObb2->m_fAxisHalfLen[i];

		if (r0 > r1 + r2)
			return false;
	}
	//if (isExistParaller)
	//	return true;
	// obb 2의 평면 3개를 기준으로 obb1 의 축 3개를 검사


	// obb1 의 축 3개와 obb2 의 축 3개를 가지고 만든 평면의 분리축 검사
	{
		r0 = abs(dist[0] * cos[2][0] - dist[2] * cos[0][0]);
		r1 = pObb1->m_fAxisHalfLen[0] * absCos[2][0] + pObb1->m_fAxisHalfLen[2] * absCos[0][0];
		r2 = pObb2->m_fAxisHalfLen[1] * absCos[1][2] + pObb2->m_fAxisHalfLen[2] * absCos[1][1];

		if (r0 > r1 + r2)
			return false;

		r0 = abs(dist[0] * cos[2][1] - dist[2] * cos[0][1]);
		r1 = pObb1->m_fAxisHalfLen[0] * absCos[2][1] + pObb1->m_fAxisHalfLen[2] * absCos[0][1];
		r2 = pObb2->m_fAxisHalfLen[0] * absCos[1][2] + pObb2->m_fAxisHalfLen[2] * absCos[1][0];

		if (r0 > r1 + r2)
			return false;

		r0 = abs(dist[0] * cos[2][2] - dist[2] * cos[0][2]);
		r1 = pObb1->m_fAxisHalfLen[0] * absCos[2][2] + pObb1->m_fAxisHalfLen[2] * absCos[0][2];
		r2 = pObb2->m_fAxisHalfLen[0] * absCos[1][1] + pObb2->m_fAxisHalfLen[1] * absCos[1][0];

		if (r0 > r1 + r2)
			return false;
		//---------------------------------------------------------------------------------------
		r0 = abs(dist[1] * cos[0][0] - dist[0] * cos[1][0]);
		r1 = pObb1->m_fAxisHalfLen[0] * absCos[1][0] + pObb1->m_fAxisHalfLen[1] * absCos[0][0];
		r2 = pObb2->m_fAxisHalfLen[1] * absCos[2][2] + pObb2->m_fAxisHalfLen[2] * absCos[2][1];

		if (r0 > r1 + r2)
			return false;

		r0 = abs(dist[1] * cos[0][1] - dist[0] * cos[1][1]);
		r1 = pObb1->m_fAxisHalfLen[0] * absCos[1][1] + pObb1->m_fAxisHalfLen[1] * absCos[0][1];
		r2 = pObb2->m_fAxisHalfLen[0] * absCos[2][2] + pObb2->m_fAxisHalfLen[2] * absCos[2][0];

		if (r0 > r1 + r2)
			return false;

		r0 = abs(dist[1] * cos[0][2] - dist[0] * cos[1][2]);
		r1 = pObb1->m_fAxisHalfLen[0] * absCos[1][2] + pObb1->m_fAxisHalfLen[1] * absCos[0][2];
		r2 = pObb2->m_fAxisHalfLen[0] * absCos[2][1] + pObb2->m_fAxisHalfLen[1] * absCos[2][0];

		if (r0 > r1 + r2)
			return false;
		//-----------------------------------------------------
		r0 = abs(dist[2] * cos[1][0] - dist[1] * cos[2][0]);
		r1 = pObb1->m_fAxisHalfLen[1] * absCos[2][0] + pObb1->m_fAxisHalfLen[2] * absCos[1][0];
		r2 = pObb2->m_fAxisHalfLen[1] * absCos[0][2] + pObb2->m_fAxisHalfLen[2] * absCos[0][1];

		if (r0 > r1 + r2)
			return false;

		r0 = abs(dist[2] * cos[1][1] - dist[1] * cos[2][1]);
		r1 = pObb1->m_fAxisHalfLen[1] * absCos[2][1] + pObb1->m_fAxisHalfLen[2] * absCos[1][1];
		r2 = pObb2->m_fAxisHalfLen[0] * absCos[0][2] + pObb2->m_fAxisHalfLen[2] * absCos[0][0];

		if (r0 > r1 + r2)
			return false;

		r0 = abs(dist[2] * cos[1][2] - dist[1] * cos[2][2]);
		r1 = pObb1->m_fAxisHalfLen[1] * absCos[2][2] + pObb1->m_fAxisHalfLen[2] * absCos[1][2];
		r2 = pObb2->m_fAxisHalfLen[0] * absCos[0][1] + pObb2->m_fAxisHalfLen[1] * absCos[0][0];

		if (r0 > r1 + r2)
			return false;
	}

	return true;
}

void cOBB::Render_Debug(D3DCOLOR c, D3DXMATRIXA16* playerWorld, D3DXMATRIXA16* World)
{
	std::vector<ST_PC_VERTEX>	vecVertex;
	vecVertex.reserve(8);

	// 버텍스 설정
	ST_PC_VERTEX v;
	v.c = c;
	{
		v.p = D3DXVECTOR3(
			m_vOrgCenterPos.x - m_fAxisHalfLen[0],
			m_vOrgCenterPos.y - m_fAxisHalfLen[1],
			m_vOrgCenterPos.z - m_fAxisHalfLen[2]);
		vecVertex.push_back(v);

		v.p = D3DXVECTOR3(
			m_vOrgCenterPos.x - m_fAxisHalfLen[0],
			m_vOrgCenterPos.y + m_fAxisHalfLen[1],
			m_vOrgCenterPos.z - m_fAxisHalfLen[2]);
		vecVertex.push_back(v);

		v.p = D3DXVECTOR3(
			m_vOrgCenterPos.x + m_fAxisHalfLen[0],
			m_vOrgCenterPos.y + m_fAxisHalfLen[1],
			m_vOrgCenterPos.z - m_fAxisHalfLen[2]);
		vecVertex.push_back(v);

		v.p = D3DXVECTOR3(
			m_vOrgCenterPos.x + m_fAxisHalfLen[0],
			m_vOrgCenterPos.y - m_fAxisHalfLen[1],
			m_vOrgCenterPos.z - m_fAxisHalfLen[2]);
		vecVertex.push_back(v);

		v.p = D3DXVECTOR3(
			m_vOrgCenterPos.x - m_fAxisHalfLen[0],
			m_vOrgCenterPos.y - m_fAxisHalfLen[1],
			m_vOrgCenterPos.z + m_fAxisHalfLen[2]);
		vecVertex.push_back(v);

		v.p = D3DXVECTOR3(
			m_vOrgCenterPos.x - m_fAxisHalfLen[0],
			m_vOrgCenterPos.y + m_fAxisHalfLen[1],
			m_vOrgCenterPos.z + m_fAxisHalfLen[2]);
		vecVertex.push_back(v);

		v.p = D3DXVECTOR3(
			m_vOrgCenterPos.x + m_fAxisHalfLen[0],
			m_vOrgCenterPos.y + m_fAxisHalfLen[1],
			m_vOrgCenterPos.z + m_fAxisHalfLen[2]);
		vecVertex.push_back(v);

		v.p = D3DXVECTOR3(
			m_vOrgCenterPos.x + m_fAxisHalfLen[0],
			m_vOrgCenterPos.y - m_fAxisHalfLen[1],
			m_vOrgCenterPos.z + m_fAxisHalfLen[2]);
		vecVertex.push_back(v);

		//===========================================
		{
			/*int nunV = 10;
			v.p = D3DXVECTOR3(
			m_vOrgCenterPos.x - nunV,
			m_vOrgCenterPos.y - nunV,
			m_vOrgCenterPos.z - nunV);
			vecVertex.push_back(v);

			v.p = D3DXVECTOR3(
			m_vOrgCenterPos.x - nunV,
			m_vOrgCenterPos.y + nunV,
			m_vOrgCenterPos.z - nunV);
			vecVertex.push_back(v);

			v.p = D3DXVECTOR3(
			m_vOrgCenterPos.x + nunV,
			m_vOrgCenterPos.y + nunV,
			m_vOrgCenterPos.z - nunV);
			vecVertex.push_back(v);

			v.p = D3DXVECTOR3(
			m_vOrgCenterPos.x + nunV,
			m_vOrgCenterPos.y - nunV,
			m_vOrgCenterPos.z - nunV);
			vecVertex.push_back(v);

			v.p = D3DXVECTOR3(
			m_vOrgCenterPos.x -nunV,
			m_vOrgCenterPos.y -nunV,
			m_vOrgCenterPos.z +nunV);
			vecVertex.push_back(v);

			v.p = D3DXVECTOR3(
			m_vOrgCenterPos.x - nunV,
			m_vOrgCenterPos.y + nunV,
			m_vOrgCenterPos.z + nunV);
			vecVertex.push_back(v);

			v.p = D3DXVECTOR3(
			m_vOrgCenterPos.x + nunV,
			m_vOrgCenterPos.y + nunV,
			m_vOrgCenterPos.z + nunV);
			vecVertex.push_back(v);

			v.p = D3DXVECTOR3(
			m_vOrgCenterPos.x + nunV,
			m_vOrgCenterPos.y - nunV,
			m_vOrgCenterPos.z + nunV);
			vecVertex.push_back(v);*/
		}
	}
	//D3DXMATRIXA16   matS;
	//D3DXMatrixScaling(&matS, 0.15f, 0.15f, 0.15f);
	//D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);
	//for (int i = 0; i < vecVertex.size(); i++)
	//{
	//	D3DXVec3TransformCoord(&vecVertex[i].p, &vecVertex[i].p, &matS);
	//}
	//D3DXVec3TransformCoord(&m_vCenterPos, &m_vCenterPos, &matS);
	// 인덱스 설정
	std::vector<ST_PC_VERTEX>	m_vecVertex;

	std::vector<WORD>	vecIndex;
	vecIndex.reserve(36);
	{
		vecIndex.push_back(0);
		vecIndex.push_back(1);
		vecIndex.push_back(2);

		vecIndex.push_back(0);
		vecIndex.push_back(2);
		vecIndex.push_back(3);

		vecIndex.push_back(4);
		vecIndex.push_back(6);
		vecIndex.push_back(5);

		vecIndex.push_back(4);
		vecIndex.push_back(7);
		vecIndex.push_back(6);

		vecIndex.push_back(4);
		vecIndex.push_back(5);
		vecIndex.push_back(1);

		vecIndex.push_back(4);
		vecIndex.push_back(1);
		vecIndex.push_back(0);

		vecIndex.push_back(3);
		vecIndex.push_back(2);
		vecIndex.push_back(6);

		vecIndex.push_back(3);
		vecIndex.push_back(6);
		vecIndex.push_back(7);

		vecIndex.push_back(1);
		vecIndex.push_back(5);
		vecIndex.push_back(6);

		vecIndex.push_back(1);
		vecIndex.push_back(6);
		vecIndex.push_back(2);

		vecIndex.push_back(4);
		vecIndex.push_back(0);
		vecIndex.push_back(3);

		vecIndex.push_back(4);
		vecIndex.push_back(3);
		vecIndex.push_back(7);

	}

	ST_PC_VERTEX vv;
	vv.c = c;
	for (int i = 0; i < vecIndex.size(); i++)
	{
		vv.p = vecVertex[vecIndex[i]].p;
		m_vecVertex.push_back(vv);
	}

	if (*World)
	{
		m_matWorldTM = (*playerWorld)*(*World);
	}
	else
	{
		m_matWorldTM = (*playerWorld);
	}



	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTM);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3,
		&m_vecVertex[0],
		sizeof(ST_PC_VERTEX));
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	RenderFont(vecVertex);
}

void cOBB::SetFont()
{
	D3DXFONT_DESC stFD;
	ZeroMemory(&stFD, sizeof(D3DXFONT_DESC));
	stFD.Height = 35;
	stFD.Width = 20;
	stFD.Weight = FW_MEDIUM;
	stFD.Italic = false;
	stFD.CharSet = DEFAULT_CHARSET;
	stFD.OutputPrecision = OUT_DEFAULT_PRECIS;
	stFD.PitchAndFamily = FF_DONTCARE;

	//AddFontResource("font/umberto.ttf");
	//strcpy_s(stFD.FaceName, "umberto");
	strcpy_s(stFD.FaceName, "굴림체");
	D3DXCreateFontIndirect(g_pD3DDevice, &stFD, &m_pFont);
}

void cOBB::RenderFont(std::vector<ST_PC_VERTEX> pc)
{
	if (m_pFont)
	{
		std::string sText;// =
						  //	"중심" + Convert((int)m_vCenterPos.x)+"/" + Convert((int)m_vCenterPos.y) + "/" + Convert((int)m_vCenterPos.z) + "\n"+
						  //	"0번:" + Convert((int)pc[0].p.x) + "/" + Convert((int)pc[0].p.y) + "/" + Convert((int)pc[0].p.z) + "\n" +
						  //	"1번:" + Convert((int)pc[1].p.x) + "/" + Convert((int)pc[1].p.y) + "/" + Convert((int)pc[1].p.z) + "\n" +
						  //	"2번:" + Convert((int)pc[2].p.x) + "/" + Convert((int)pc[2].p.y) + "/" + Convert((int)pc[2].p.z) + "\n" +
						  //	"3번:" + Convert((int)pc[3].p.x) + "/" + Convert((int)pc[3].p.y) + "/" + Convert((int)pc[3].p.z) + "\n" +

						  //	"4번:" + Convert((int)pc[4].p.x) + "/" + Convert((int)pc[4].p.y) + "/" + Convert((int)pc[4].p.z) + "\n" +
						  //	"5번:" + Convert((int)pc[5].p.x) + "/" + Convert((int)pc[5].p.y) + "/" + Convert((int)pc[5].p.z) + "\n" +
						  //	"6번:" + Convert((int)pc[6].p.x) + "/" + Convert((int)pc[6].p.y) + "/" + Convert((int)pc[6].p.z) + "\n" +
						  //	"7번:" + Convert((int)pc[7].p.x) + "/" + Convert((int)pc[7].p.y) + "/" + Convert((int)pc[7].p.z) + "\n";
						  ////sprintf(sText, "%f", (PlayerInFo.HP));

		RECT rc;
		SetRect(&rc, 100, 100, 300, 200);

		m_pFont->DrawText(NULL,
			sText.c_str(),
			sText.length(),
			&rc,
			DT_LEFT | DT_TOP | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 0));
	}
}

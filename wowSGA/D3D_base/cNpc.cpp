#include "stdafx.h"
#include "cNpc.h"

#include "cNpc_AniController.h"
#include "cNpcInfo.h"
#include "cRay.h"

cNpc::cNpc()
	:m_npcAnicontroller(NULL)
	, m_npc_info(NULL)
	, m_playerPos(0, 0, 0)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cNpc::~cNpc()
{
	SAFE_DELETE(m_npcAnicontroller);
	SAFE_DELETE(m_npc_info);
	m_mesh->Release();
}

void cNpc::Setup(D3DXVECTOR3 pos)
{
	
	m_npcAnicontroller = new cNpc_AniController;
	m_npcAnicontroller->Setup();

	m_npc_info = new cNpcInfo;
	m_npc_info->setup();

	D3DXCreateSphere(g_pD3DDevice, 0.8f, 20, 20, &m_mesh, NULL);
	PmeshInfo.fRadius = 0.8f;

	m_pos = pos;

	ispickinged = false;
}

void cNpc::update()
{
	if (m_npcAnicontroller)
		m_npcAnicontroller->Update(&Npc_State);

	if (GetKeyState(VK_LBUTTON) & 0x8000)
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);
		cRay r = cRay::RayAtWorldSpace(pt.x, pt.y);
		PmeshInfo.bIsPicked = r.IsPicked(&PmeshInfo);
		if (PmeshInfo.bIsPicked) ispickinged = true;
	}
}

void cNpc::render()
{
	D3DXMATRIXA16 matworld, matT, matR, matS;

	D3DXMatrixIsIdentity(&matworld);
	D3DXMatrixIsIdentity(&matT);

	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y+0.85f, m_pos.z);
	D3DXMatrixRotationY(&matR, D3DX_PI / 2.0f);
	D3DXMatrixScaling(&matS, 0.1f, 0.1f, 0.1f);

	

	matworld = m_matWorld * matR;

	matworld._41 += matT._41;
	matworld._42 += matT._42;
	matworld._43 += matT._43;


	PmeshInfo.vCenter = D3DXVECTOR3(matworld._41, matworld._42, matworld._43);

	if (m_npcAnicontroller)
		m_npcAnicontroller->Render(&matworld);

	if (m_npc_info)
		m_npc_info->render();

	//g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &matworld);
	//m_mesh->DrawSubset(0);
	//g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}
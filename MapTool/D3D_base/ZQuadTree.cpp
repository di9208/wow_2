#include "stdafx.h"
#include "ZQuadTree.h"


//최초 루트 노드 생성자
ZQuadTree::ZQuadTree(int cx, int cy)
{
	int i;
	m_nCenter = 0;
	for(i=0; i<4; i++)
	{
		m_pChild[i] = NULL;
	}

	//루트 노드의 4개 코너값 설정
	m_nCorner[CORNER_TL] = 0;
	m_nCorner[CORNER_TR] = cx - 1;
	m_nCorner[CORNER_BL] = cx * (cy - 1);
	m_nCorner[CORNER_BR] = cx * cy - 1;
	m_nCenter                 = (m_nCorner[CORNER_TL] +
		                            m_nCorner[CORNER_TR] +
									m_nCorner[CORNER_BL] +
									m_nCorner[CORNER_BR]) / 4;
	m_fRadius = 0.0f;
	m_bCulled = FALSE;
	m_fRadius = 0.0f;
}

//하위 자식 노드 생성자
ZQuadTree::ZQuadTree(ZQuadTree *pParent)
{
	int i;
	m_nCenter = 0;
	for(i=0; i<4; i++)
	{
		m_pChild[i] = NULL;
		m_nCorner[i] = 0;
	}

	m_bCulled = FALSE;
	m_fRadius = 0.0f;
}

//소멸자
ZQuadTree::~ZQuadTree()
{
	_Destroy();
}

//메모리에서 쿼드트리를 삭제한다.
void ZQuadTree::_Destroy()
{
	//자식 노드들을 소멸시킨다.
	for(int i=0; i<4; i++) SAFE_DELETE(m_pChild[i]);
}

//4개의 코너값을 셋팅한다.
BOOL ZQuadTree::_SetCorners(int nCornerTL, int nCornerTR, int nCornerBL, int nCornerBR)
{
	m_nCorner[CORNER_TL] = nCornerTL;
	m_nCorner[CORNER_TR] = nCornerTR;
	m_nCorner[CORNER_BL] = nCornerBL;
	m_nCorner[CORNER_BR] = nCornerBR;
	m_nCenter                 = (m_nCorner[CORNER_TL] +
		                            m_nCorner[CORNER_TR] +
									m_nCorner[CORNER_BL] +
									m_nCorner[CORNER_BR]) / 4;

	return TRUE;
}

//자식노드를 추가한다.
ZQuadTree* ZQuadTree::_AddChild(int nCornerTL, int nCornerTR, int nCornerBL, int nCornerBR)
{
	ZQuadTree* pChild;

	pChild = new ZQuadTree(this);
	pChild->_SetCorners(nCornerTL, nCornerTR, nCornerBL, nCornerBR);

	return pChild;
}

//쿼드트리를 4개의 자식 트리로 하위분할 한다.
BOOL ZQuadTree::_SubDivide()
{
	int nTopEdgeCenter;
	int nBottomEdgeCenter;
	int nLeftEdgeCenter;
	int nRightEdgeCenter;
	int nCentralPoint;

	//상단변 가운데
	nTopEdgeCenter = (m_nCorner[CORNER_TL] + m_nCorner[CORNER_TR]) / 2;
	//하단변 가운데
	nBottomEdgeCenter = (m_nCorner[CORNER_BL] + m_nCorner[CORNER_BR]) / 2;
	//좌측변 가운데
	nLeftEdgeCenter = (m_nCorner[CORNER_TL] + m_nCorner[CORNER_BL]) / 2;
	//우측변 가운데
	nRightEdgeCenter = (m_nCorner[CORNER_TR] + m_nCorner[CORNER_BR]) / 2;
	//한가운데
	nCentralPoint = (m_nCorner[CORNER_TL] + 
		                m_nCorner[CORNER_TR] +
						m_nCorner[CORNER_BL] + 
						m_nCorner[CORNER_BR]) / 4;

	//더 이상 분할이 불가능한가? 그렇다면 SubDivide() 종료
	if((m_nCorner[CORNER_TR] - m_nCorner[CORNER_TL]) <= 1)
	{
		return FALSE;
	}

	//4개의 자식 노드 추가
	m_pChild[CORNER_TL] = _AddChild(m_nCorner[CORNER_TL],
		nTopEdgeCenter, nLeftEdgeCenter, nCentralPoint);
	m_pChild[CORNER_TR] = _AddChild(nTopEdgeCenter,
		m_nCorner[CORNER_TR], nCentralPoint, nRightEdgeCenter);
	m_pChild[CORNER_BL] = _AddChild(nLeftEdgeCenter,
		nCentralPoint, m_nCorner[CORNER_BL], nBottomEdgeCenter);
	m_pChild[CORNER_BR] = _AddChild(nCentralPoint,
		nRightEdgeCenter, nBottomEdgeCenter, m_nCorner[CORNER_BR]);

	return TRUE;
}

BOOL ZQuadTree::Build()
{
	if(_SubDivide())
	{
		
		m_pChild[CORNER_TL]->Build();
		m_pChild[CORNER_TR]->Build();
		m_pChild[CORNER_BL]->Build();
		m_pChild[CORNER_BR]->Build();
	}
	return TRUE;
}


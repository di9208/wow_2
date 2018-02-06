#include "stdafx.h"
#include "ZQuadTree.h"


//���� ��Ʈ ��� ������
ZQuadTree::ZQuadTree(int cx, int cy)
{
	int i;
	m_nCenter = 0;
	for(i=0; i<4; i++)
	{
		m_pChild[i] = NULL;
	}

	//��Ʈ ����� 4�� �ڳʰ� ����
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

//���� �ڽ� ��� ������
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

//�Ҹ���
ZQuadTree::~ZQuadTree()
{
	_Destroy();
}

//�޸𸮿��� ����Ʈ���� �����Ѵ�.
void ZQuadTree::_Destroy()
{
	//�ڽ� ������ �Ҹ��Ų��.
	for(int i=0; i<4; i++) SAFE_DELETE(m_pChild[i]);
}

//4���� �ڳʰ��� �����Ѵ�.
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

//�ڽĳ�带 �߰��Ѵ�.
ZQuadTree* ZQuadTree::_AddChild(int nCornerTL, int nCornerTR, int nCornerBL, int nCornerBR)
{
	ZQuadTree* pChild;

	pChild = new ZQuadTree(this);
	pChild->_SetCorners(nCornerTL, nCornerTR, nCornerBL, nCornerBR);

	return pChild;
}

//����Ʈ���� 4���� �ڽ� Ʈ���� �������� �Ѵ�.
BOOL ZQuadTree::_SubDivide()
{
	int nTopEdgeCenter;
	int nBottomEdgeCenter;
	int nLeftEdgeCenter;
	int nRightEdgeCenter;
	int nCentralPoint;

	//��ܺ� ���
	nTopEdgeCenter = (m_nCorner[CORNER_TL] + m_nCorner[CORNER_TR]) / 2;
	//�ϴܺ� ���
	nBottomEdgeCenter = (m_nCorner[CORNER_BL] + m_nCorner[CORNER_BR]) / 2;
	//������ ���
	nLeftEdgeCenter = (m_nCorner[CORNER_TL] + m_nCorner[CORNER_BL]) / 2;
	//������ ���
	nRightEdgeCenter = (m_nCorner[CORNER_TR] + m_nCorner[CORNER_BR]) / 2;
	//�Ѱ��
	nCentralPoint = (m_nCorner[CORNER_TL] + 
		                m_nCorner[CORNER_TR] +
						m_nCorner[CORNER_BL] + 
						m_nCorner[CORNER_BR]) / 4;

	//�� �̻� ������ �Ұ����Ѱ�? �׷��ٸ� SubDivide() ����
	if((m_nCorner[CORNER_TR] - m_nCorner[CORNER_TL]) <= 1)
	{
		return FALSE;
	}

	//4���� �ڽ� ��� �߰�
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


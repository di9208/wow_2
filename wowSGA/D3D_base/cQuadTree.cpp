#include "stdafx.h"
#include "cQuadTree.h"
#include "cFrustum.h"

cQuadTree::cQuadTree(int col, int row)
{
	for (int i = 0; i < 4; i++)
	{
		Child[i] = nullptr;
	}

	_col = col;
	_row = row;
	m_pPoint.p0 = 0;
	m_pPoint.p1 = col * (row - 1);
	m_pPoint.p2 = col * row - 1;
	m_pPoint.p3 = col - 1;
	m_pPoint.C = (m_pPoint.p0 + m_pPoint.p1 + m_pPoint.p2 + m_pPoint.p3) / 4;

	
	m_radius = 0;
	iscull = false;
}
cQuadTree::cQuadTree(cQuadTree* Parent)
{
	ZeroMemory(&m_pPoint, sizeof(tagpoint));
	for (int i = 0; i < 4; i++)
	{
		Child[i] = nullptr;
	}

	m_radius = 0;
	iscull = false;
}

cQuadTree::~cQuadTree()
{
	for (int i = 0; i < 4; i++)
	{
		SAFE_DELETE(Child[i]);
	}
}



void cQuadTree::Add()
{
	if ((m_pPoint.p3 - m_pPoint.p0) < 2)
		return;
	Child[0] = SetChild(0);
	Child[1] = SetChild(1);
	Child[2] = SetChild(2);
	Child[3] = SetChild(3);

	Child[0]->Add();
	Child[1]->Add();
	Child[2]->Add();
	Child[3]->Add();



}

bool cQuadTree::Add(ST_PTN_VERTEX * vp)
{
	if (SubDivide())
	{
		//좌측 상단과 우측 하단의 거리를 구한다.
		D3DXVECTOR3 v = *((D3DXVECTOR3*)(vp + m_pPoint.p1)) -
			*((D3DXVECTOR3*)(vp + m_pPoint.p3));
		//v의 거리값이 이 노드를 감싸는 경계구의 지름이므로, 2로 나누어 반지름을 구한다.
		m_radius = D3DXVec3Length(&v) / 2.0f;
		Child[0]->Add(vp);
		Child[1]->Add(vp);
		Child[2]->Add(vp);
		Child[3]->Add(vp);
	}


	return true;
}

void cQuadTree::Check(std::vector<ST_PTN_VERTEX> vec, D3DXVECTOR3 v, std::vector<ST_PTN_VERTEX> &vec2, std::vector<int> &index)
{
	for (int i = 0; i < 4; i++)
	{
		if (v.x >= vec[m_pPoint.p0].p.x &&
			v.x <= vec[m_pPoint.p2].p.x &&
			v.z >= vec[m_pPoint.p0].p.z &&
			v.z <= vec[m_pPoint.p2].p.z)
		{
			
			if(Child[i])
				Child[i]->Check(vec, v, vec2 , index);
			if (Child[i] == nullptr)
			{
				setvertex();
				index = vecCulIndex;
				/*int col = sqrt(vecCulIndex.size());
				for (int z = 0; z< col - 1; z++)
				{
					for (int x = 0; x < col - 1; x++)
					{
						vec2.push_back(vec[vecCulIndex[x + z * col]]);
						vec2.push_back(vec[vecCulIndex[x + (z+1) * col]]);
						vec2.push_back(vec[vecCulIndex[x+1 + (z+1) * col]]);

						vec2.push_back(vec[vecCulIndex[x + z * col]]);
						vec2.push_back(vec[vecCulIndex[x+1 + (z+1) * col]]);
						vec2.push_back(vec[vecCulIndex[x+1 + z * col]]);
					}
				}*/
				vec2.push_back(vec[m_pPoint.p0]);
				vec2.push_back(vec[m_pPoint.p1]);
				vec2.push_back(vec[m_pPoint.p2]);
				vec2.push_back(vec[m_pPoint.p0]);
				vec2.push_back(vec[m_pPoint.p2]);
				vec2.push_back(vec[m_pPoint.p3]);
				
				//p.p0 = m_pPoint.p0;
				//p.p1 = m_pPoint.p1;
				//p.p2 = m_pPoint.p2;
				//p.p3 = m_pPoint.p3;
				//p.C = m_pPoint.C;
				return;
			}
		}
		else
		{
			return;
		}
			
	}


}

int cQuadTree::CheckFrustum(cFrustum * f, ST_PTN_VERTEX* vp)
{
	bool in[4];
	bool insphere;
	
	insphere = f->isInside((D3DXVECTOR3*)(vp + m_pPoint.C), m_radius);
	if(!insphere)
		return F_OUT;
	in[0] = f->isInside((D3DXVECTOR3*)(vp + m_pPoint.p0));
	in[1] = f->isInside((D3DXVECTOR3*)(vp + m_pPoint.p1));
	in[2] = f->isInside((D3DXVECTOR3*)(vp + m_pPoint.p2));
	in[3] = f->isInside((D3DXVECTOR3*)(vp + m_pPoint.p3));
	
	if (in[0]+ in[1]+ in[2] + in[3]==4)
		return F_IN;

	return F_PARTIALLY_IN;

}

int cQuadTree::GetTri(int nTris, LPVOID pIndex)
{
	if (iscull)
	{
		iscull = false;
		return nTris;
	}

	if (IsVisible())
	{
		LPDWORD p = ((LPDWORD)pIndex) + nTris * 3;

		*p++ = m_pPoint.p0;
		*p++ = m_pPoint.p1;
		*p++ = m_pPoint.p2;
		nTris++;

		*p++ = m_pPoint.p0;
		*p++ = m_pPoint.p2;
		*p++ = m_pPoint.p3;
		nTris++;

		return nTris;
	}
	if (Child[0])
		nTris = Child[0]->GetTri(nTris, pIndex);
	if (Child[1])
		nTris = Child[1]->GetTri(nTris, pIndex);
	if (Child[2])
		nTris = Child[2]->GetTri(nTris, pIndex);
	if (Child[3])
		nTris = Child[3]->GetTri(nTris, pIndex);


	return nTris;
}


void cQuadTree::Cull(cFrustum * f, ST_PTN_VERTEX* vp)
{
	int c = CheckFrustum(f, vp);
	switch (c)
	{
	case F_IN:
		iscull = false;
		return;
	
	case F_PARTIALLY_IN:
		iscull = false;
		break;
	
	case F_OUT:
		iscull = true;
		return;
	}

	if (Child[0]) Child[0]->Cull(f, vp);
	if (Child[1]) Child[1]->Cull(f, vp);
	if (Child[2]) Child[2]->Cull(f, vp);
	if (Child[3]) Child[3]->Cull(f, vp);

}

int cQuadTree::GenerateIndex(LPVOID pIndex, ST_PTN_VERTEX* vp, cFrustum * f)
{
	Cull(f, vp);
	return GetTri(0,pIndex);
}

void cQuadTree::setvertex()
{
	int _0 = m_pPoint.p0;
	int _1 = m_pPoint.p1;
	int _2 = m_pPoint.p2;
	int _3 = m_pPoint.p3;
	vecCulIndex.clear();
	//left
	if (_0%_col == 0)
	{
		if (_0 == 0)
		{
			int i = _0;
			vecCulIndex.push_back(i);
			i = _3;
			vecCulIndex.push_back(i);
			i = _3 + 1;
			vecCulIndex.push_back(i);
			i = _1;
			vecCulIndex.push_back(i);
			i = _2;
			vecCulIndex.push_back(i);
			i = _2 + 1;
			vecCulIndex.push_back(i);
			i = _1 + _col;
			vecCulIndex.push_back(i);
			i = _2 + _col;
			vecCulIndex.push_back(i);
			i = _2 + _col + 1;
			vecCulIndex.push_back(i);

			return;
		}
		if (_0 == (_col) * (_row - 2))
		{
			int i = _0 - _col;
			vecCulIndex.push_back(i);
			i = _3 - _col;
			vecCulIndex.push_back(i);
			i = _3 - _col + 1;
			vecCulIndex.push_back(i);
			i = _0;
			vecCulIndex.push_back(i);
			i = _3;
			vecCulIndex.push_back(i);
			i = _3 + 1;
			vecCulIndex.push_back(i);
			i = _1;
			vecCulIndex.push_back(i);
			i = _2;
			vecCulIndex.push_back(i);
			i = _2 + 1;
			vecCulIndex.push_back(i);

			return;
		}
		else
		{
			int i = _0 - _col;
			vecCulIndex.push_back(i);
			i = _3 - _col;
			vecCulIndex.push_back(i);
			i = _3 - _col + 1;
			vecCulIndex.push_back(i);
			i = _0;
			vecCulIndex.push_back(i);
			i = _3;
			vecCulIndex.push_back(i);
			i = _3 + 1;
			vecCulIndex.push_back(i);
			i = _1;
			vecCulIndex.push_back(i);
			i = _2;
			vecCulIndex.push_back(i);
			i = _2 + 1;
			vecCulIndex.push_back(i);
			i = _1 + _col;
			vecCulIndex.push_back(i);
			i = _2 + _col;
			vecCulIndex.push_back(i);
			i = _2 + _col + 1;
			vecCulIndex.push_back(i);

			return;
		}
	}
	//bottom
	else if (_0>0 && _0 < _col - 2)
	{
		int i = _0 - 1;
		vecCulIndex.push_back(i);
		i = _0;
		vecCulIndex.push_back(i);
		i = _3;
		vecCulIndex.push_back(i);
		i = _3 + 1;
		vecCulIndex.push_back(i);

		i = _1 - 1;
		vecCulIndex.push_back(i);
		i = _1;
		vecCulIndex.push_back(i);
		i = _2;
		vecCulIndex.push_back(i);
		i = _2 + 1;
		vecCulIndex.push_back(i);
		i = _1 + _col - 1;
		vecCulIndex.push_back(i);
		i = _1 + _col;
		vecCulIndex.push_back(i);
		i = _2 + _col;
		vecCulIndex.push_back(i);
		i = _2 + _col + 1;
		vecCulIndex.push_back(i);
		return;
	}
	//top
	else if (_0< (_col - 1)*_row - 2 && _0 > _col*(_row - 2))
	{
		int i = _0 - _col - 1;
		vecCulIndex.push_back(i);
		i = _0 - _col;
		vecCulIndex.push_back(i);
		i = _3 - _col;
		vecCulIndex.push_back(i);
		i = _3 - _col + 1;
		vecCulIndex.push_back(i);
		i = _0 - 1;
		vecCulIndex.push_back(i);
		i = _0;
		vecCulIndex.push_back(i);
		i = _3;
		vecCulIndex.push_back(i);
		i = _3 + 1;
		vecCulIndex.push_back(i);
		i = _1 - 1;
		vecCulIndex.push_back(i);
		i = _1;
		vecCulIndex.push_back(i);
		i = _2;
		vecCulIndex.push_back(i);
		i = _2 + 1;
		vecCulIndex.push_back(i);

		return;
	}
	//right
	else if (_0 % _col == _col - 2)
	{
		if (_0 == _col - 2)
		{
			int i = _0 - 1;
			vecCulIndex.push_back(i);
			i = _0;
			vecCulIndex.push_back(i);
			i = _3;
			vecCulIndex.push_back(i);
			i = _1 - 1;
			vecCulIndex.push_back(i);
			i = _1;
			vecCulIndex.push_back(i);
			i = _2;
			vecCulIndex.push_back(i);
			i = _1 + _col - 1;
			vecCulIndex.push_back(i);
			i = _1 + _col;
			vecCulIndex.push_back(i);
			i = _2 + _col;
			vecCulIndex.push_back(i);
			return;
		}
		else if (_0 == (_col - 1)*_row - 2)
		{
			int i = _0 - _col - 1;
			vecCulIndex.push_back(i);
			i = _0 - _col;
			vecCulIndex.push_back(i);
			i = _3 - _col;
			vecCulIndex.push_back(i);
			i = _0 - 1;
			vecCulIndex.push_back(i);
			i = _0;
			vecCulIndex.push_back(i);
			i = _3;
			vecCulIndex.push_back(i);
			i = _1 - 1;
			vecCulIndex.push_back(i);
			i = _1;
			vecCulIndex.push_back(i);
			i = _2;
			vecCulIndex.push_back(i);
			return;
		}
		else
		{
			int i = _0 - _col - 1;
			vecCulIndex.push_back(i);
			i = _0 - _col;
			vecCulIndex.push_back(i);
			i = _3 - _col;
			vecCulIndex.push_back(i);
			i = _0 - 1;
			vecCulIndex.push_back(i);
			i = _0;
			vecCulIndex.push_back(i);
			i = _3;
			vecCulIndex.push_back(i);
			i = _1 - 1;
			vecCulIndex.push_back(i);
			i = _1;
			vecCulIndex.push_back(i);
			i = _2;
			vecCulIndex.push_back(i);
			i = _1 + _col - 1;
			vecCulIndex.push_back(i);
			i = _1 + _col;
			vecCulIndex.push_back(i);
			i = _2 + _col;
			vecCulIndex.push_back(i);
			return;
		}
	}
	//rest
	else
	{
		int i = _0 - _col - 1;
		vecCulIndex.push_back(i);
		i = _0 - _col;
		vecCulIndex.push_back(i);
		i = _3 - _col;
		vecCulIndex.push_back(i);
		i = _3 - _col + 1;
		vecCulIndex.push_back(i);
		i = _0 - 1;
		vecCulIndex.push_back(i);
		i = _0;
		vecCulIndex.push_back(i);
		i = _3;
		vecCulIndex.push_back(i);
		i = _3 + 1;
		vecCulIndex.push_back(i);
		i = _1 - 1;
		vecCulIndex.push_back(i);
		i = _1;
		vecCulIndex.push_back(i);
		i = _2;
		vecCulIndex.push_back(i);
		i = _2 + 1;
		vecCulIndex.push_back(i);
		i = _1 + _col - 1;
		vecCulIndex.push_back(i);
		i = _1 + _col;
		vecCulIndex.push_back(i);
		i = _2 + _col;
		vecCulIndex.push_back(i);
		i = _2 + _col + 1;
		vecCulIndex.push_back(i);
		return;
	}
}

cQuadTree* cQuadTree::SetChild(int point)
{
	cQuadTree* q;
	q = new cQuadTree(this);
	q->_col = _col;
	q->_row = _row;
	
	if (point == 0)
	{
		q->m_pPoint.p0 = m_pPoint.p0;
		q->m_pPoint.p1 = (m_pPoint.p1 + m_pPoint.p0) / 2;
		q->m_pPoint.p2 = m_pPoint.C;
		q->m_pPoint.p3 = (m_pPoint.p3 + m_pPoint.p0) / 2;
		q->m_pPoint.C = (q->m_pPoint.p0 + q->m_pPoint.p1 + q->m_pPoint.p2 + q->m_pPoint.p3) / 4;
		return q;
	}
	if (point == 1)
	{
		q->m_pPoint.p0 = (m_pPoint.p1 + m_pPoint.p0) / 2;
		q->m_pPoint.p1 = m_pPoint.p1;
		q->m_pPoint.p2 = (m_pPoint.p2 + m_pPoint.p1) / 2;
		q->m_pPoint.p3 = m_pPoint.C;
		q->m_pPoint.C = (q->m_pPoint.p0 + q->m_pPoint.p1 + q->m_pPoint.p2 + q->m_pPoint.p3) / 4;
		return q;
	}
	if (point == 2)
	{
		q->m_pPoint.p0 = m_pPoint.C;
		q->m_pPoint.p1 = (m_pPoint.p2 + m_pPoint.p1) / 2;
		q->m_pPoint.p2 = m_pPoint.p2;
		q->m_pPoint.p3 = (m_pPoint.p2 + m_pPoint.p3)/ 2 ;
		q->m_pPoint.C = (q->m_pPoint.p0 + q->m_pPoint.p1 + q->m_pPoint.p2 + q->m_pPoint.p3) / 4;
		return q;
	}
	if (point == 3)
	{
		q->m_pPoint.p0 = (m_pPoint.p3 + m_pPoint.p0) / 2;
		q->m_pPoint.p1 = m_pPoint.C;
		q->m_pPoint.p2 = (m_pPoint.p2 + m_pPoint.p3) / 2;
		q->m_pPoint.p3 = m_pPoint.p3;
		q->m_pPoint.C = (q->m_pPoint.p0 + q->m_pPoint.p1 + q->m_pPoint.p2 + q->m_pPoint.p3) / 4;
		return q;
	}

	
}


bool cQuadTree::SetCorners(int p0, int p1, int p2, int p3)
{
	m_pPoint.p0 = p0;
	m_pPoint.p1 = p1;
	m_pPoint.p2 = p2;
	m_pPoint.p3 = p3;
	m_pPoint.C =(m_pPoint.p0 +
		m_pPoint.p1 +
		m_pPoint.p2 +
		m_pPoint.p3) / 4;


	return true;
}

cQuadTree* cQuadTree::AddChild(int p0, int p1, int p2, int p3)
{
	cQuadTree* pChild;

	pChild = new cQuadTree(this);
	pChild->SetCorners(p0, p1, p2, p3);

	return pChild;
}


bool cQuadTree::SubDivide()
{
	int nTopEdgeCenter;
	int nBottomEdgeCenter;
	int nLeftEdgeCenter;
	int nRightEdgeCenter;
	int nCentralPoint;

	//상단변 가운데
	nTopEdgeCenter = (m_pPoint.p1 + m_pPoint.p2) / 2;
	//하단변 가운데
	nBottomEdgeCenter = (m_pPoint.p0 + m_pPoint.p3) / 2;
	//좌측변 가운데
	nLeftEdgeCenter = (m_pPoint.p0 + m_pPoint.p1) / 2;
	//우측변 가운데
	nRightEdgeCenter = (m_pPoint.p2 + m_pPoint.p3) / 2;
	//한가운데
	nCentralPoint = (m_pPoint.p0 +
		m_pPoint.p1 +
		m_pPoint.p2 +
		m_pPoint.p3) / 4;

	//더 이상 분할이 불가능한가? 그렇다면 SubDivide() 종료
	if ((m_pPoint.p2 - m_pPoint.p1) <= 1)
	{
		return false;
	}

	//4개의 자식 노드 추가
	Child[0] = AddChild(m_pPoint.p0,
		nLeftEdgeCenter, nCentralPoint, nBottomEdgeCenter);

	Child[1] = AddChild(nLeftEdgeCenter,
		m_pPoint.p1, nTopEdgeCenter, nCentralPoint);

	Child[2] = AddChild(nCentralPoint,
		nTopEdgeCenter, m_pPoint.p2, nRightEdgeCenter);

	Child[3] = AddChild(nBottomEdgeCenter,
		nCentralPoint, nRightEdgeCenter, m_pPoint.p3);

	
	return true;
}



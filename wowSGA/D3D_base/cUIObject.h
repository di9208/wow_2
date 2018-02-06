#pragma once
#include "cObject.h"

class cUIObject :public cObject
{
protected:
	std::vector<cUIObject*>		m_vecChild;
	D3DXMATRIXA16				m_matWorld;

	SYNTHESIZE(D3DXVECTOR3, m_vPos, Pos);
	ST_SIZE						m_stSize;

	SYNTHESIZE(bool, m_isHidden, hidden);

	SYNTHESIZE(cUIObject*, m_pParent, Parent);
	SYNTHESIZE(int, m_nTag, Tag);

	SYNTHESIZE(D3DXVECTOR3, MatS, Scal);

public:
	cUIObject();
	virtual ~cUIObject();

	void AddChild(cUIObject* pChild);
	void Destroy();

	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
};


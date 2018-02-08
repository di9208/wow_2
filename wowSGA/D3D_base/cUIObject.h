#pragma once
#include "cObject.h"

enum ENUMTAG
{
	TAG_SHOP,
	TAG_BUYBACK,
	TAG_CLOSE,
	TAG_CHILD_CLOSE
};

class cUIObject :public cObject
{
protected:
	SYNTHESIZE_REF(std::vector<cUIObject*>, m_vecChild, Child);
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


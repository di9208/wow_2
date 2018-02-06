#pragma once
#include "cObject.h"

enum BUTTONTAG
{
	TAG_TAB,
	TAG_SAVE,
	TAG_LOAD
};
class cUIObject :public cObject
{
protected:
	SYNTHESIZE_REF(std::vector<cUIObject*>,	m_vecChild, Child);
	SYNTHESIZE_REF(D3DXMATRIXA16, m_matWorld, World);

	SYNTHESIZE(D3DXVECTOR3, m_vPos, Pos);
	SYNTHESIZE(D3DXVECTOR3, m_Scale, Scale);
	ST_SIZE						m_stSize;

	SYNTHESIZE(bool, m_isHidden, isHidden);

	SYNTHESIZE(cUIObject*, m_pParent, Parent);
	SYNTHESIZE(int, m_nTag, Tag);


public:
	cUIObject();
	virtual ~cUIObject();

	void AddChild(cUIObject* pChild);
	void Destroy();

	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
};


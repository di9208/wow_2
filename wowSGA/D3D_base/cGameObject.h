#pragma once
#include "cObject.h"

class cGameObject : public cObject
{
protected:
	SYNTHESIZE(D3DXVECTOR3, m_vPos, Position);
	SYNTHESIZE(D3DXVECTOR3, m_vDir, Direction);

public:
	cGameObject();
	virtual ~cGameObject();
};


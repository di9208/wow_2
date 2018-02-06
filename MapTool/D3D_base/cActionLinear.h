#pragma once
#include "cAction.h"

class cGameObject;

class cActionLinear : public cAction
{
private:
	float m_fStartTime;
	float m_fPassedTime;
	D3DXVECTOR3		m_vPrevPosition;

	SYNTHESIZE(float, m_fActionTime, ActionTime);
	SYNTHESIZE(cGameObject*, m_pOwner, Owner);
	SYNTHESIZE(D3DXVECTOR3, m_vFrom, From);
	SYNTHESIZE(D3DXVECTOR3, m_vTo, To);

public:
	cActionLinear();
	virtual ~cActionLinear();

	virtual void Start() override;
	virtual void Update() override;
};


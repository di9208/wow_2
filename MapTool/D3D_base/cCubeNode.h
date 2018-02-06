#pragma once

#include "cCubePTN.h"

class cCubeNode : public cCubePTN
{
protected:
	D3DXMATRIXA16				m_matWorldTM;
	D3DXMATRIXA16				m_matLocalTM;
	D3DXVECTOR3					m_vLocalPos;
	std::vector<cCubeNode*>		m_vecChild;
	float						m_fRotX;
	D3DXVECTOR3					m_vDir;

	SYNTHESIZE(D3DXMATRIXA16*, m_pParentWorldTM, ParentWorldTM);
	SYNTHESIZE(float, m_fRotDeltaX, RotDeltaX);


public:
	cCubeNode();
	virtual ~cCubeNode();

	void AddChild(cCubeNode* pChild);
	void Destroy();

	void Setup() override;
	void Update() override;
	void Render() override;
};


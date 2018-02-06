#pragma once
class cCubePTN
{
protected:
	std::vector<ST_PTN_VERTEX>		m_vecVertex;

public:
	cCubePTN();
	virtual ~cCubePTN();

	virtual void Setup();
	virtual void Render();
	virtual void Update();
};


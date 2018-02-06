#pragma once
class cCube
{
protected:
	std::vector<ST_PT_VERTEX>	m_vecVertex;

public:
	cCube();
	virtual ~cCube();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
};


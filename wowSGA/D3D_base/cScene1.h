#pragma once
class cStage1;
class cFrustum;
class cScene1
{
private:
	cStage1 * m_Map;
	cFrustum * m_frustum;
public:
	cScene1();
	~cScene1();

	void Setup();
	void Update();
	void Render();
};


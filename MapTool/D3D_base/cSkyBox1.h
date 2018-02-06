#pragma once

class cSkinnedMesh;

class cSkyBox1
{
private:
	cSkinnedMesh * m_skybox;

public:
	cSkyBox1();
	~cSkyBox1();

	void Setup();
	void Update();
	void Render(D3DXVECTOR3 camera);
};


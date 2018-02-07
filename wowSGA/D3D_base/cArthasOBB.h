#pragma once
#include "cUnit.h"

class cOBB;
class cSkinnedMesh;

class cArthasOBB
{
private:
	SYNTHESIZE(cOBB*, m_arthasOBB, arthasOBB);

public:
	cArthasOBB();
	~cArthasOBB();
	void Setup(cSkinnedMesh* bskinned, D3DXMATRIXA16* bWorld);
	void Update(D3DXMATRIXA16* pMatWorld);
	void Render(D3DXMATRIXA16* bWorld, D3DXMATRIXA16* pMatWorld);

	void Collision(cOBB* box);

};


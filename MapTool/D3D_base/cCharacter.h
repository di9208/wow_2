#pragma once
#include "cGameObject.h"

class iMap;
class cCharacter : public cGameObject
{
protected:
	float			m_fRotY;
	D3DXMATRIXA16	m_matWorld;

public:
	cCharacter();
	~cCharacter();

	void Setup();
	void Update(iMap* pMap = NULL);
};


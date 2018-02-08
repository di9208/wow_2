#include "stdafx.h"
#include "cRagPaticle.h"


cRagPaticle::cRagPaticle(int num, int size)
{
	_size = 1.5f;
	_vbSize = 2048;
	_vbOffset = 0;
	_vbBatchSize = 512;
	m_nSize = size;
	for (int i = 0; i < num; i++)
	{
		addParticle();
	}
}


cRagPaticle::~cRagPaticle()
{
}

void cRagPaticle::resetParticle(Attribute * attribute)
{
	int a = rand() % 2;
	int b = rand() % 2;

	//x는 모름
	//y는 가로
	//z는 세로	
	if (a == 0)			attribute->position.x = (rand() % 10) *0.03f*7.0f;
	else if (a == 1.f)	attribute->position.x = -(rand() % 10) *0.03f*7.0f;
	if (b == 0)			attribute->position.z = (rand() % 10) *0.03f*5.0f;
	else if (b == 1.f)	attribute->position.z = -(rand() % 10) *0.03f*5.0f;
	attribute->position.y = -rand() % 7 +5.f;

	attribute->velocity.x = 0;
	attribute->velocity.y = 0.5f;
	attribute->velocity.z = 0;

	attribute->color = D3DCOLOR_ARGB(255, 255, 0, 0);
}

void cRagPaticle::update(float timeDelta)
{
	std::list<Attribute>::iterator i;
	for (i = _particles.begin(); i != _particles.end(); i++)
	{
		static float a = 0.3f;
		D3DXMATRIXA16 matR, matT, matW, matRX, matRZ;
		D3DXMatrixRotationY(&matR, a);
		D3DXMatrixRotationX(&matRX, a);
		D3DXMatrixRotationZ(&matRZ, a);
		D3DXMatrixTranslation(&matT, 0, 0, 0);

		matW = matR * /*matRZ*matRX* */matT;
		D3DXVec3TransformCoord(&i->position, &i->position, &matW);
		//D3DXVec3TransformCoord(&i->position, &i->position, &matR);
		//i->position 

		/*if (i->position.y >= 70 )
		{
		resetParticle(&(*i));
		}*/
	}
	//removeDeadParticles();
}

#pragma once

#define EPSILON 1.0f		//User Range of Frustum
class cFrustum
{
private:
	D3DXVECTOR3 vertex[8];	//Frustum Vertex	
	D3DXPLANE plane[6];		//Frustum Plane
public:
	cFrustum();
	~cFrustum();

	void SetupVertex();		//Setup Plane
	bool isInside(D3DXVECTOR3 *v);		//Is Vertex Inside Frustum?
	bool isInside(D3DXVECTOR3 *v, float radius); //Is Vertex(Sphere) Inside Frustum?
};


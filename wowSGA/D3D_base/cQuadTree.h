#pragma once
class cFrustum;
struct tagpoint
{
	int p0;
	int p1;
	int p2;
	int p3;
	int C;
};
struct ST_INDEX
{
	DWORD	_0, _1, _2;
};

class cQuadTree
{
public:
	enum tagFrustum			//Frustum Condition
	{
		F_IN=2,
		F_PARTIALLY_IN=1,
		F_OUT=0,
		F_UNKNOWN =-1
	};

private:
	SYNTHESIZE(tagpoint, m_pPoint, Point); //5 Point	
	//P1---------P2
	//:			 :
	//:		C    :
	//:			 :
	//P0---------P3

	cQuadTree* Child[4];
	bool iscull;						//Decision Culled
	float m_radius;						//Sphere Radius

	std::vector<int> vecCulIndex;		//No More Using This Vector
	int _col;							//Column
	int _row;							//Row

public:
	cQuadTree(int col, int row);		//Setup Root
	cQuadTree(cQuadTree* Parent);		//Setup Children
	~cQuadTree();

	
	void Add();							//No More using This Function
	bool Add(ST_PTN_VERTEX* vp);		//Setup QuadTree

	//No More using This Function
	void Check(std::vector<ST_PTN_VERTEX> vec, D3DXVECTOR3 v, std::vector<ST_PTN_VERTEX> &vec2, std::vector<int> &index);
	
	//Judge in Frustum or out Frustum
	int CheckFrustum(cFrustum* f, ST_PTN_VERTEX* vp);
	//Setup Triangle Index
	int GetTri(int nTris, LPVOID pIndex);
	//Judge has Children or has Not
	bool IsVisible() { return (m_pPoint.p2 - m_pPoint.p1 <= 1); }

	//Decision Frustum Condition
	void Cull(cFrustum* f, ST_PTN_VERTEX* vp);

	//Setup Culled Index
	int GenerateIndex(LPVOID pIndex, ST_PTN_VERTEX* vp, cFrustum* f);

	//Setup 5 Point
	bool SetCorners(int p0, int p1, int p2, int p3);

	/// Add Child
	cQuadTree* AddChild(int p0, int p1, int p2, int p3);
	bool SubDivide();
	///

	void setvertex();					//No More using This Function
	cQuadTree* SetChild(int point);		//No More using This Function
};


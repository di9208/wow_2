#pragma once
class cSkinnedMesh;
class cOBB
{
private:
	D3DXVECTOR3		m_vOrgCenterPos;
	D3DXVECTOR3		m_vOrgAxisDir[3];

	SYNTHESIZE(D3DXVECTOR3, m_vCenterPos, CenterPos);
	D3DXVECTOR3		m_vAxisDir[3];
	float			m_fAxisLen[3];
	float			m_fAxisHalfLen[3];

	D3DXMATRIXA16	m_matWorldTM;
	ST_SPHERE		m_vecSphere;
	ST_SPHERE		m_vecSphereC;
	LPD3DXMESH		m_pMeshSphere;

	LPD3DXFONT		m_pFont;

	std::vector<ST_PC_VERTEX>	vecVertex;
	std::vector<ST_PC_VERTEX>	m_vecVertex;
	std::vector<WORD>	vecIndex;
public:
	cOBB();
	~cOBB();

	void Setup(cSkinnedMesh* pSkinnedMesh, D3DXMATRIXA16* playerWorld);
	void Update(D3DXMATRIXA16* pMatWorld);
	bool IsCollision(cOBB* pObb1, cOBB* pObb2);
	void Render_Debug(D3DCOLOR c, D3DXMATRIXA16* playerWorld, D3DXMATRIXA16* World);


	void SetFont();
	void RenderFont(std::vector<ST_PC_VERTEX> pc);

	D3DXVECTOR3 getCheck(int i) { return m_vAxisDir[i]; }
	float getMax();
};


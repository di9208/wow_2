#pragma once
class cSkinnedMesh;
class cOBB
{
private:
	////D3DXVECTOR3		m_vOrgCenterPos;
	//SYNTHESIZE(D3DXVECTOR3, m_vOrgCenterPos, CenterPos);
	//D3DXVECTOR3		m_vOrgAxisDir[3];
	////SYNTHESIZE(D3DXVECTOR3, m_vOrgAxisDir[3], OrgAxisDir);//x,y,z√‡

	//D3DXVECTOR3		m_vCenterPos;
	////D3DXVECTOR3		m_vAxisDir[3];
	//SYNTHESIZE(std::vector<D3DXVECTOR3>, m_vAxisDir, AxisDir); 
	////float			m_fAxisLen[3];
	//SYNTHESIZE(std::vector<float>, m_fAxisLen, AxisLen);
	//float			m_fAxisHalfLen[3];

	D3DXVECTOR3		m_vOrgCenterPos;
	D3DXVECTOR3		m_vOrgAxisDir[3];

	D3DXVECTOR3		m_vCenterPos;
	D3DXVECTOR3		m_vAxisDir[3];
	float			m_fAxisLen[3];
	float			m_fAxisHalfLen[3];

	D3DXMATRIXA16	m_matWorldTM;
	ST_SPHERE		m_vecSphere;
	ST_SPHERE		m_vecSphereC;
	LPD3DXMESH		m_pMeshSphere;

	LPD3DXFONT		m_pFont;
public:
	cOBB();
	~cOBB();


	//D3DXVECTOR3 GetOrgAxisDir(int n) { return m_vOrgAxisDir[n]; }
	//D3DXVECTOR3 GetAxisDir(int n) { return m_vAxisDir[n]; }
	//float		GetAxisLen(int n) { return m_fAxisHalfLen[n]; }

	void Setup(cSkinnedMesh* pSkinnedMesh, D3DXMATRIXA16* playerWorld);
	void Update(D3DXMATRIXA16* pMatWorld);
	bool IsCollision(cOBB* pObb1, cOBB* pObb2);
	void Render_Debug(D3DCOLOR c, D3DXMATRIXA16* playerWorld, D3DXMATRIXA16* World);


	void SetFont();
	void RenderFont(std::vector<ST_PC_VERTEX> pc);
};


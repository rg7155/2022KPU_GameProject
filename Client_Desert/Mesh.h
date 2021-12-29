//------------------------------------------------------- ----------------------
// File: Mesh.h
//-----------------------------------------------------------------------------

#pragma once

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
class CVertex
{
public:
	XMFLOAT3						m_xmf3Position;

public:
	CVertex(){ m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f); }
	CVertex(float x, float y, float z){ m_xmf3Position = XMFLOAT3(x, y, z); }
	CVertex(XMFLOAT3 xmf3Position){ m_xmf3Position = xmf3Position; }
	~CVertex(){ }
};

class CDiffusedVertex : public CVertex
{
public:
	XMFLOAT4						m_xmf4Diffuse;

public:
	CDiffusedVertex(){ m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f); m_xmf4Diffuse = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f); }
	CDiffusedVertex(float x, float y, float z, XMFLOAT4 xmf4Diffuse){ m_xmf3Position = XMFLOAT3(x, y, z); m_xmf4Diffuse = xmf4Diffuse; }
	CDiffusedVertex(XMFLOAT3 xmf3Position, XMFLOAT4 xmf4Diffuse = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f)){ m_xmf3Position = xmf3Position; m_xmf4Diffuse = xmf4Diffuse; }
	~CDiffusedVertex(){ }
};

class CParticleVertex : public CVertex
{
public:
	XMFLOAT3						m_xmf3Color = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3						m_xmf3Velocity = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3						m_xmf3Acceleration = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT2						m_xmf2Size = XMFLOAT2(0.0f, 0.0f);
	XMFLOAT2						m_xmf2AgeLifetime = XMFLOAT2(0.0f, 0.0f); //(Age, Lifetime)
	UINT							m_nType = 0;

public:
	CParticleVertex() {}
	~CParticleVertex() {}
};

class CTexturedVertex : public CVertex
{
public:
	XMFLOAT2						m_xmf2TexCoord;

public:
	CTexturedVertex(){ m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f); m_xmf2TexCoord = XMFLOAT2(0.0f, 0.0f); }
	CTexturedVertex(float x, float y, float z, XMFLOAT2 xmf2TexCoord){ m_xmf3Position = XMFLOAT3(x, y, z); m_xmf2TexCoord = xmf2TexCoord; }
	CTexturedVertex(XMFLOAT3 xmf3Position, XMFLOAT2 xmf2TexCoord = XMFLOAT2(0.0f, 0.0f)){ m_xmf3Position = xmf3Position; m_xmf2TexCoord = xmf2TexCoord; }
	~CTexturedVertex(){ }
};

class CDiffusedTexturedVertex : public CDiffusedVertex
{
public:
	XMFLOAT2						m_xmf2TexCoord;

public:
	CDiffusedTexturedVertex(){ m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f); m_xmf4Diffuse = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f); m_xmf2TexCoord = XMFLOAT2(0.0f, 0.0f); }
	CDiffusedTexturedVertex(float x, float y, float z, XMFLOAT4 xmf4Diffuse, XMFLOAT2 xmf2TexCoord){ m_xmf3Position = XMFLOAT3(x, y, z); m_xmf4Diffuse = xmf4Diffuse; m_xmf2TexCoord = xmf2TexCoord; }
	CDiffusedTexturedVertex(XMFLOAT3 xmf3Position, XMFLOAT4 xmf4Diffuse = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f), XMFLOAT2 xmf2TexCoord = XMFLOAT2(0.0f, 0.0f)){ m_xmf3Position = xmf3Position; m_xmf4Diffuse = xmf4Diffuse; m_xmf2TexCoord = xmf2TexCoord; }
	~CDiffusedTexturedVertex(){ }
};

class CDiffused2TexturedVertex : public CDiffusedVertex
{
public:
	XMFLOAT2						m_xmf2TexCoord0;
	XMFLOAT2						m_xmf2TexCoord1;

public:
	CDiffused2TexturedVertex(){ m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f); m_xmf4Diffuse = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f); m_xmf2TexCoord0 = m_xmf2TexCoord1 = XMFLOAT2(0.0f, 0.0f); }
	CDiffused2TexturedVertex(float x, float y, float z, XMFLOAT4 xmf4Diffuse, XMFLOAT2 xmf2TexCoord0, XMFLOAT2 xmf2TexCoord1){ m_xmf3Position = XMFLOAT3(x, y, z); m_xmf4Diffuse = xmf4Diffuse; m_xmf2TexCoord0 = xmf2TexCoord0; m_xmf2TexCoord1 = xmf2TexCoord1; }
	CDiffused2TexturedVertex(XMFLOAT3 xmf3Position, XMFLOAT4 xmf4Diffuse = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f), XMFLOAT2 xmf2TexCoord0 = XMFLOAT2(0.0f, 0.0f), XMFLOAT2 xmf2TexCoord1 = XMFLOAT2(0.0f, 0.0f)){ m_xmf3Position = xmf3Position; m_xmf4Diffuse = xmf4Diffuse; m_xmf2TexCoord0 = xmf2TexCoord0; m_xmf2TexCoord1 = xmf2TexCoord1; }
	~CDiffused2TexturedVertex(){ }
};

class CIlluminatedVertex : public CVertex
{
protected:
	XMFLOAT3						m_xmf3Normal;

public:
	CIlluminatedVertex(){ m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f); m_xmf3Normal = XMFLOAT3(0.0f, 0.0f, 0.0f); }
	CIlluminatedVertex(float x, float y, float z, XMFLOAT3 xmf3Normal = XMFLOAT3(0.0f, 0.0f, 0.0f)){ m_xmf3Position = XMFLOAT3(x, y, z); m_xmf3Normal = xmf3Normal; }
	CIlluminatedVertex(XMFLOAT3 xmf3Position, XMFLOAT3 xmf3Normal = XMFLOAT3(0.0f, 0.0f, 0.0f)){ m_xmf3Position = xmf3Position; m_xmf3Normal = xmf3Normal; }
	~CIlluminatedVertex(){ }
};

class CIlluminatedTexturedVertex : public CIlluminatedVertex
{
protected:
	XMFLOAT2						m_xmf2TexCoord;

public:
	CIlluminatedTexturedVertex(){ m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f); m_xmf2TexCoord = XMFLOAT2(0.0f, 0.0f); m_xmf3Normal = XMFLOAT3(0.0f, 0.0f, 0.0f); }
	CIlluminatedTexturedVertex(float x, float y, float z, XMFLOAT2 xmf2TexCoord, XMFLOAT3 xmf3Normal = XMFLOAT3(0.0f, 0.0f, 0.0f)){ m_xmf3Position = XMFLOAT3(x, y, z); m_xmf3Normal = xmf3Normal; m_xmf2TexCoord = xmf2TexCoord; }
	CIlluminatedTexturedVertex(XMFLOAT3 xmf3Position, XMFLOAT3 xmf3Normal = XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2 xmf2TexCoord = XMFLOAT2(0.0f, 0.0f)){ m_xmf3Position = xmf3Position; m_xmf3Normal = xmf3Normal; m_xmf2TexCoord = xmf2TexCoord; }
	~CIlluminatedTexturedVertex(){ }
};

class CGeometryShadowVertex : public CVertex
{
public:
	XMFLOAT2						m_xmf2Size;		

public:
	CGeometryShadowVertex(){ m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f); m_xmf2Size = XMFLOAT2(5.0f, 10.0f); }
	CGeometryShadowVertex(float x, float y, float z, XMFLOAT2 xmf2Size = XMFLOAT2(5.0f, 10.0f), UINT nTexture = 0){ m_xmf3Position = XMFLOAT3(x, y, z); m_xmf2Size = xmf2Size; }
	CGeometryShadowVertex(XMFLOAT3 xmf3Position, XMFLOAT2 xmf2Size=XMFLOAT2(5.0f, 10.0f)){ m_xmf3Position = xmf3Position; m_xmf2Size = xmf2Size; }
	~CGeometryShadowVertex(){ }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
class CMesh
{
public:
	CMesh(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	virtual ~CMesh();

private:
	int								m_nReferences = 0;

public:
	void AddRef(){ m_nReferences++; }
	void Release(){ if (--m_nReferences <= 0) delete this; }

	void ReleaseUploadBuffers();

protected:
	ID3D12Resource					*m_pd3dVertexBuffer = NULL;
	ID3D12Resource					*m_pd3dVertexUploadBuffer = NULL;

	ID3D12Resource					*m_pd3dIndexBuffer = NULL;
	ID3D12Resource					*m_pd3dIndexUploadBuffer = NULL;

	D3D12_VERTEX_BUFFER_VIEW		m_d3dVertexBufferView;
	D3D12_INDEX_BUFFER_VIEW			m_d3dIndexBufferView;

	D3D12_PRIMITIVE_TOPOLOGY		m_d3dPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	UINT							m_nSlot = 0;
	UINT							m_nVertices = 0;
	UINT							m_nStride = 0;
	UINT							m_nOffset = 0;

	UINT							m_nIndices = 0;
	UINT							m_nStartIndex = 0;
	int								m_nBaseVertex = 0;

public:
	BoundingBox						m_xmBoundingBox;

public:
	virtual void PreRender(ID3D12GraphicsCommandList* pd3dCommandList, int nPipelineState) {}
	virtual void Render(ID3D12GraphicsCommandList* pd3dCommandList);
	virtual void Render(ID3D12GraphicsCommandList* pd3dCommandList, int nPipelineState) {}
	virtual void PostRender(ID3D12GraphicsCommandList* pd3dCommandList, int nPipelineState) {}

	void CalculateBoundingBox(XMFLOAT3 *pxmf3Points, UINT nStride);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
class CMeshDiffused : public CMesh
{
public:
	CMeshDiffused(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList) : CMesh(pd3dDevice, pd3dCommandList){ }
	virtual ~CMeshDiffused(){ }
};

/////////////////////////////////////////////////////////////////////////////////////////////////
//
class CAirplaneMeshDiffused : public CMesh
{
public:
	CAirplaneMeshDiffused(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, float fWidth = 20.0f, float fHeight = 20.0f, float fDepth = 4.0f, XMFLOAT4 xmf4Color = XMFLOAT4(1.0f, 1.0f, 0.0f, 0.0f));
	virtual ~CAirplaneMeshDiffused();
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
class CMeshIlluminated : public CMesh
{
public:
	CMeshIlluminated(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	virtual ~CMeshIlluminated();

public:
	void CalculateTriangleListVertexNormals(XMFLOAT3 *pxmf3Normals, XMFLOAT3 *pxmf3Positions, int nVertices);
	void CalculateTriangleListVertexNormals(XMFLOAT3 *pxmf3Normals, XMFLOAT3 *pxmf3Positions, UINT nVertices, UINT *pnIndices, UINT nIndices);
	void CalculateTriangleStripVertexNormals(XMFLOAT3 *pxmf3Normals, XMFLOAT3 *pxmf3Positions, UINT nVertices, UINT *pnIndices, UINT nIndices);
	void CalculateVertexNormals(XMFLOAT3 *pxmf3Normals, XMFLOAT3 *pxmf3Positions, int nVertices, UINT *pnIndices, int nIndices);
};

/////////////////////////////////////////////////////////////////////////////////////////////////
//
class CAirPlaneMeshIlluminated : public CMeshIlluminated
{
public:
	CAirPlaneMeshIlluminated(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, float fWidth = 20.0f, float fHeight = 20.0f, float fDepth = 4.0f);
	virtual ~CAirPlaneMeshIlluminated();
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
class CCubeMeshIlluminated : public CMeshIlluminated
{
public:
	CCubeMeshIlluminated(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, float fWidth = 2.0f, float fHeight = 2.0f, float fDepth = 2.0f);
	virtual ~CCubeMeshIlluminated();
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
class CPlaneMeshIlluminated : public CMeshIlluminated
{
public:
	CPlaneMeshIlluminated(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, float fWidth=20.0f, float fHeight=20.0f, float fDepth=20.0f, float fxPosition=0.0f, float fyPosition=0.0f, float fzPosition=0.0f);
	virtual ~CPlaneMeshIlluminated();
};



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CMeshIlluminatedTextured : public CMeshIlluminated
{
public:
	CMeshIlluminatedTextured(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList);
	virtual ~CMeshIlluminatedTextured();
};

class CCubeMeshIlluminatedTextured : public CMeshIlluminatedTextured
{
public:
	CCubeMeshIlluminatedTextured(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, float fWidth = 2.0f, float fHeight = 2.0f, float fDepth = 2.0f);
	virtual ~CCubeMeshIlluminatedTextured();
};

class CPlaneMeshIlluminatedTextured : public CMeshIlluminatedTextured
{
public:
	CPlaneMeshIlluminatedTextured(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, float fWidth = 20.0f, float fHeight = 20.0f, float fDepth = 20.0f, float fxPosition = 0.0f, float fyPosition = 0.0f, float fzPosition = 0.0f);
	virtual ~CPlaneMeshIlluminatedTextured();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
class CGeometryShadowMesh : public CMesh
{
public:
	CGeometryShadowMesh(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, CGeometryShadowVertex *pGeometryShadowVertices, UINT nGeometryShadowVertices);
	virtual ~CGeometryShadowMesh();
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#define MAX_PARTICLES					100/*9999999*/
//#define _WITH_QUERY_DATA_SO_STATISTICS
//디파인 안되있으면 직접 읽어옴

class CParticleMesh : public CMesh
{
public:
	CParticleMesh(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, XMFLOAT3 xmf3Position, XMFLOAT3 xmf3Velocity, XMFLOAT3 xmf3Acceleration, XMFLOAT3 xmf3Color, XMFLOAT2 xmf2Size, float fLifetime, UINT nMaxParticles);
	virtual ~CParticleMesh();

	bool								m_bStart = true;

	UINT								m_nMaxParticles = MAX_PARTICLES;

	ID3D12Resource* m_pd3dStreamOutputBuffer = NULL;
	ID3D12Resource* m_pd3dDrawBuffer = NULL;

	ID3D12Resource* m_pd3dDefaultBufferFilledSize = NULL;
	ID3D12Resource* m_pd3dUploadBufferFilledSize = NULL;
	UINT64* m_pnUploadBufferFilledSize = NULL;
#ifdef _WITH_QUERY_DATA_SO_STATISTICS
	ID3D12QueryHeap* m_pd3dSOQueryHeap = NULL;
	ID3D12Resource* m_pd3dSOQueryBuffer = NULL;
	D3D12_QUERY_DATA_SO_STATISTICS* m_pd3dSOQueryDataStatistics = NULL;
#else
	ID3D12Resource* m_pd3dReadBackBufferFilledSize = NULL;
#endif

	D3D12_STREAM_OUTPUT_BUFFER_VIEW		m_d3dStreamOutputBufferView;

	virtual void CreateVertexBuffer(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, XMFLOAT3 xmf3Position, XMFLOAT3 xmf3Velocity, XMFLOAT3 xmf3Acceleration, XMFLOAT3 xmf3Color, XMFLOAT2 xmf2Size, float fLifetime);
	virtual void CreateStreamOutputBuffer(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, UINT nMaxParticles);

	virtual void PreRender(ID3D12GraphicsCommandList* pd3dCommandList, int nPipelineState);
	virtual void Render(ID3D12GraphicsCommandList* pd3dCommandList, int nPipelineState);
	virtual void PostRender(ID3D12GraphicsCommandList* pd3dCommandList, int nPipelineState);
};

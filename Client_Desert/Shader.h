//-----------------------------------------------------------------------------
// File: Shader.h
//-----------------------------------------------------------------------------

#pragma once

#include "Object.h"
#include "Camera.h"

struct LIGHT;

class CShader
{
public:
	CShader();
	virtual ~CShader();

private:
	int								m_nReferences = 0;

public:
	void AddRef(){ m_nReferences++; }
	void Release(){ if (--m_nReferences <= 0) delete this; }

	virtual D3D12_INPUT_LAYOUT_DESC CreateInputLayout(int nPipelineState);
	virtual D3D12_RASTERIZER_DESC CreateRasterizerState(int nPipelineState);
	virtual D3D12_BLEND_DESC CreateBlendState(int nPipelineState);
	virtual D3D12_DEPTH_STENCIL_DESC CreateDepthStencilState(int nPipelineState);
	virtual D3D12_STREAM_OUTPUT_DESC CreateStreamOuputState(int nPipelineState);

	virtual D3D12_PRIMITIVE_TOPOLOGY_TYPE GetPrimitiveTopologyType(int nPipelineState) { return(D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE); }
	virtual UINT GetNumRenderTargets(int nPipelineState) { return(1); }
	virtual DXGI_FORMAT GetRTVFormat(int nPipelineState, int nRenderTarget) { return(DXGI_FORMAT_R8G8B8A8_UNORM); }
	virtual DXGI_FORMAT GetDSVFormat(int nPipelineState) { return(DXGI_FORMAT_D24_UNORM_S8_UINT); }

	virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob **ppd3dShaderBlob, int nPipelineState);
	virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob **ppd3dShaderBlob, int nPipelineState);
	virtual D3D12_SHADER_BYTECODE CreateGeometryShader(ID3DBlob **ppd3dShaderBlob, int nPipelineState);
	virtual D3D12_SHADER_BYTECODE CreateHullShader(ID3DBlob** ppd3dShaderBlob, int nPipelineState);
	virtual D3D12_SHADER_BYTECODE CreateDomainShader(ID3DBlob** ppd3dShaderBlob, int nPipelineState);
	virtual D3D12_SHADER_BYTECODE CreateComputeShader(ID3DBlob** ppd3dShaderBlob);

	D3D12_SHADER_BYTECODE CompileShaderFromFile(WCHAR *pszFileName, LPCSTR pszShaderName, LPCSTR pszShaderProfile, ID3DBlob **ppd3dShaderBlob);

	virtual void CreateShader(ID3D12Device* pd3dDevice, ID3D12RootSignature* pd3dGraphicsRootSignature, int nPipelineState = 0);

	void CreateCbvSrvDescriptorHeaps(ID3D12Device *pd3dDevice, int nConstantBufferViews, int nShaderResourceViews);
	void CreateConstantBufferViews(ID3D12Device *pd3dDevice, int nConstantBufferViews, ID3D12Resource *pd3dConstantBuffers, UINT nStride);
	void CreateShaderResourceViews(ID3D12Device* pd3dDevice, CTexture* pTexture, UINT nDescriptorHeapIndex, UINT nRootParameterStartIndex);
	void CreateShaderResourceViews(ID3D12Device* pd3dDevice, int nResources, ID3D12Resource** ppd3dResources, DXGI_FORMAT *pdxgiSrvFormats);

	virtual void CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void ReleaseShaderVariables();

	virtual void UpdateShaderVariable(ID3D12GraphicsCommandList *pd3dCommandList, XMFLOAT4X4 *pxmf4x4World);

	virtual void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, void *pContext=NULL){ }
	virtual void AnimateObjects(float fTimeElapsed){ }
	virtual void ReleaseObjects(){ }

	virtual void ReleaseUploadBuffers();

	virtual void OnPrepareRender(ID3D12GraphicsCommandList *pd3dCommandList, int nPipelineState);
	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera, int nPipelineState = 0);
	virtual void OnPostRender(ID3D12GraphicsCommandList *pd3dCommandList);

	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandleForHeapStart(){ return(m_pd3dCbvSrvDescriptorHeap->GetCPUDescriptorHandleForHeapStart()); }
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandleForHeapStart(){ return(m_pd3dCbvSrvDescriptorHeap->GetGPUDescriptorHandleForHeapStart()); }

	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUCbvDescriptorStartHandle(){ return(m_d3dCbvCPUDescriptorStartHandle); }
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUCbvDescriptorStartHandle(){ return(m_d3dCbvGPUDescriptorStartHandle); }
	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUSrvDescriptorStartHandle(){ return(m_d3dSrvCPUDescriptorStartHandle); }
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUSrvDescriptorStartHandle(){ return(m_d3dSrvGPUDescriptorStartHandle); }

public:
	ID3D12DescriptorHeap			*m_pd3dCbvSrvDescriptorHeap = NULL;

/*protected*/public:
	ID3D12PipelineState** m_ppd3dPipelineStates = NULL;
	int								m_nPipelineStates = 0;

	D3D12_CPU_DESCRIPTOR_HANDLE		m_d3dCbvCPUDescriptorStartHandle;
	D3D12_GPU_DESCRIPTOR_HANDLE		m_d3dCbvGPUDescriptorStartHandle;
	D3D12_CPU_DESCRIPTOR_HANDLE		m_d3dSrvCPUDescriptorStartHandle;
	D3D12_GPU_DESCRIPTOR_HANDLE		m_d3dSrvGPUDescriptorStartHandle;

	D3D12_CPU_DESCRIPTOR_HANDLE		m_d3dSrvCPUDescriptorNextHandle;
	D3D12_GPU_DESCRIPTOR_HANDLE		m_d3dSrvGPUDescriptorNextHandle;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CIlluminatedShader : public CShader
{
public:
	CIlluminatedShader();
	virtual ~CIlluminatedShader();

	virtual D3D12_INPUT_LAYOUT_DESC CreateInputLayout(int nPipelineState);

	virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob** ppd3dShaderBlob, int nPipelineState);
	virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob** ppd3dShaderBlob, int nPipelineState);

	virtual void CreateShader(ID3D12Device* pd3dDevice, ID3D12RootSignature* pd3dGraphicsRootSignature, int nPipelineState = 0);
};


//class CPlayerShader : public CShader
class CPlayerShader : public CIlluminatedShader
{
public:
	CPlayerShader();
	virtual ~CPlayerShader();

	//virtual D3D12_INPUT_LAYOUT_DESC CreateInputLayout(int nPipelineState);

	//virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob **ppd3dShaderBlob, int nPipelineState);
	//virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob **ppd3dShaderBlob, int nPipelineState);

	virtual void CreateShader(ID3D12Device* pd3dDevice, ID3D12RootSignature* pd3dGraphicsRootSignature, int nPipelineState = 0);

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CTexturedShader : public CShader
{
public:
	CTexturedShader();
	virtual ~CTexturedShader();

	virtual D3D12_INPUT_LAYOUT_DESC CreateInputLayout(int nPipelineState);

	virtual void CreateShader(ID3D12Device* pd3dDevice, ID3D12RootSignature* pd3dGraphicsRootSignature, int nPipelineState = 0);

	virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob** ppd3dShaderBlob, int nPipelineState);
	virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob** ppd3dShaderBlob, int nPipelineState);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CBillboardShader : public CTexturedShader
{
public:
	CBillboardShader();
	virtual ~CBillboardShader();

	virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob** ppd3dShaderBlob, int nPipelineState);
	virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob** ppd3dShaderBlob, int nPipelineState);

	virtual D3D12_RASTERIZER_DESC CreateRasterizerState(int nPipelineState);
	virtual D3D12_BLEND_DESC CreateBlendState(int nPipelineState);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CParticleShader : public CBillboardShader
{
public:
	CParticleShader();
	virtual ~CParticleShader();

	virtual D3D12_PRIMITIVE_TOPOLOGY_TYPE GetPrimitiveTopologyType(int nPipelineState);
	virtual UINT GetNumRenderTargets(int nPipelineState);
	virtual DXGI_FORMAT GetRTVFormat(int nPipelineState, int nRenderTarget);
	virtual DXGI_FORMAT GetDSVFormat(int nPipelineState);

	virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob** ppd3dShaderBlob, int nPipelineState);
	virtual D3D12_SHADER_BYTECODE CreateGeometryShader(ID3DBlob** ppd3dShaderBlob, int nPipelineState);
	virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob** ppd3dShaderBlob, int nPipelineState);

	virtual D3D12_INPUT_LAYOUT_DESC CreateInputLayout(int nPipelineState);
	virtual D3D12_STREAM_OUTPUT_DESC CreateStreamOuputState(int nPipelineState);
	virtual D3D12_BLEND_DESC CreateBlendState(int nPipelineState);
	virtual D3D12_DEPTH_STENCIL_DESC CreateDepthStencilState(int nPipelineState);

	virtual void CreateShader(ID3D12Device* pd3dDevice, ID3D12RootSignature* pd3dGraphicsRootSignature, int nPipelineState = 0);
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class CIlluminatedTexturedShader : public CTexturedShader
{
public:
	CIlluminatedTexturedShader();
	virtual ~CIlluminatedTexturedShader();

	virtual D3D12_INPUT_LAYOUT_DESC CreateInputLayout(int nPipelineState);

	virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob** ppd3dShaderBlob, int nPipelineState);
	virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob** ppd3dShaderBlob, int nPipelineState);
};



class CObjectsShader : public CIlluminatedShader /*CIlluminatedTexturedShader*/ 
{
public:
	CObjectsShader();
	virtual ~CObjectsShader();

	virtual void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, void *pContext=NULL);
	virtual void AnimateObjects(float fTimeElapsed);
	virtual void ReleaseObjects();

	//virtual void CreateShaderVariables(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList);
	//virtual void UpdateShaderVariables(ID3D12GraphicsCommandList* pd3dCommandList) override;
	//virtual void ReleaseShaderVariables();

	virtual void ReleaseUploadBuffers();

	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera, int nPipelineState = 0);
	virtual void OnPostRender(ID3D12GraphicsCommandList *pd3dCommandList, int nPipelineState = 0);

	BoundingBox CalculateBoundingBox();

public:
	CGameObject						**m_ppObjects = 0;
	int								m_nObjects = 0;

	//ID3D12Resource*					m_pd3dcbGameObject = NULL;
	//CB_GAMEOBJECT_INFO*				m_pcbMappedGameObject = NULL;

};

struct TOOBJECTSPACEINFO
{
	XMFLOAT4X4						m_xmf4x4ToTexture;//조명좌표계로 바꾸는 행렬
	XMFLOAT4						m_xmf4Position;//조명위치
};

struct TOLIGHTSPACES
{
	TOOBJECTSPACEINFO				m_pToLightSpaces[MAX_LIGHTS];
};

class CDepthRenderShader : public CIlluminatedShader
{
public:
	CDepthRenderShader(CObjectsShader* pObjectsShader, LIGHT *pLights);
	virtual ~CDepthRenderShader();

	//virtual D3D12_PRIMITIVE_TOPOLOGY_TYPE GetPrimitiveTopologyType(int nPipelineState) { return(D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE); }
	//virtual UINT GetNumRenderTargets(int nPipelineState) { return(1); }
	virtual DXGI_FORMAT GetRTVFormat(int nPipelineState, int nRenderTarget) { return(DXGI_FORMAT_R32_FLOAT); }
	virtual DXGI_FORMAT GetDSVFormat(int nPipelineState) { return(DXGI_FORMAT_D32_FLOAT); }

	virtual D3D12_DEPTH_STENCIL_DESC CreateDepthStencilState(int nPipelineState);
	virtual D3D12_RASTERIZER_DESC CreateRasterizerState(int nPipelineState);

	virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob **ppd3dShaderBlob, int nPipelineState);

	virtual void CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void ReleaseShaderVariables();

	virtual void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, void *pContext=NULL);
	virtual void ReleaseObjects();

	void PrepareShadowMap(ID3D12GraphicsCommandList *pd3dCommandList);

	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera, int nPipelineState = 0);

protected:
	//깊이 저장 텍스쳐
	CTexture						*m_pDepthTexture = NULL;

	//조명 위치에서 깊이정보 저장하기위한 카메라 4개
	CCamera*						m_ppDepthRenderCameras[MAX_DEPTH_TEXTURES];

	ID3D12DescriptorHeap			*m_pd3dRtvDescriptorHeap = NULL;
	D3D12_CPU_DESCRIPTOR_HANDLE		m_pd3dRtvCPUDescriptorHandles[MAX_DEPTH_TEXTURES];

	ID3D12DescriptorHeap*			m_pd3dDsvDescriptorHeap = NULL;
	ID3D12Resource					*m_pd3dDepthBuffer = NULL;
	D3D12_CPU_DESCRIPTOR_HANDLE		m_d3dDsvDescriptorCPUHandle;

	//프로젝션을 텍스쳐로 바꾸는 행렬
	XMMATRIX						m_xmProjectionToTexture;

public:
	CTexture* GetDepthTexture() { return(m_pDepthTexture); }
	ID3D12Resource* GetDepthTextureResource(UINT nIndex) { return(m_pDepthTexture->GetResource(nIndex)); }

public:
	CObjectsShader*					m_pObjectsShader = NULL;
	CPlayer* m_pPlayer = NULL;

protected:
	LIGHT							*m_pLights = NULL;

	TOLIGHTSPACES					*m_pToLightSpaces;

	ID3D12Resource					*m_pd3dcbToLightSpaces = NULL;
	TOLIGHTSPACES					*m_pcbMappedToLightSpaces = NULL;
};

class CShadowMapShader : public CIlluminatedShader
{
public:
	CShadowMapShader(CObjectsShader* pObjectsShader);
	virtual ~CShadowMapShader();

	virtual D3D12_DEPTH_STENCIL_DESC CreateDepthStencilState(int nPipelineState);

	virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob **ppd3dShaderBlob, int nPipelineState);
	virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob **ppd3dShaderBlob, int nPipelineState);

	virtual void CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void ReleaseShaderVariables();

	virtual void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, void *pContext=NULL);
	virtual void AnimateObjects(float fTimeElapsed) { }
	virtual void ReleaseObjects();

	virtual void ReleaseUploadBuffers();

	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera, int nPipelineState = 0);

public:
	CObjectsShader*					m_pObjectsShader = NULL;
	CPlayer*						m_pPlayer = NULL;

	//DepthRenderShader에 있는
	CTexture*						m_pDepthTexture = NULL;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
class CTextureToViewportShader : public CShader
{
public:
	CTextureToViewportShader();
	virtual ~CTextureToViewportShader();

	//virtual DXGI_FORMAT GetRTVFormat(int nPipelineState, int nRenderTarget) { return DXGI_FORMAT_UNKNOWN; }

	virtual D3D12_DEPTH_STENCIL_DESC CreateDepthStencilState();

	virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob **ppd3dShaderBlob, int nPipelineState);
	virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob **ppd3dShaderBlob, int nPipelineState);

	virtual void CreateShader(ID3D12Device* pd3dDevice, ID3D12RootSignature* pd3dGraphicsRootSignature, int nPipelineState = 0);

	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList);

	virtual void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, void *pContext=NULL);
	virtual void ReleaseObjects();

	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera, int nPipelineState = 0);

	bool		m_bRender = true;
protected:
	CTexture*						m_pDepthTexture = NULL;
};


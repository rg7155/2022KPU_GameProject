//-----------------------------------------------------------------------------
// File: Scene.h
//-----------------------------------------------------------------------------

#pragma once

#include "Shader.h"
#include "Player.h"

struct LIGHT
{
	XMFLOAT4				m_xmf4Ambient;
	XMFLOAT4				m_xmf4Diffuse;
	XMFLOAT4				m_xmf4Specular;
	XMFLOAT3				m_xmf3Position;
	float 					m_fFalloff;
	XMFLOAT3				m_xmf3Direction;
	float 					m_fTheta; //cos(m_fTheta)
	XMFLOAT3				m_xmf3Attenuation;
	float					m_fPhi; //cos(m_fPhi)
	bool					m_bEnable;
	int						m_nType;
	float					m_fRange;
	float					padding;
};

struct LIGHTS
{
	LIGHT					m_pLights[MAX_LIGHTS];
	XMFLOAT4				m_xmf4GlobalAmbient;
};

struct MATERIAL
{
	XMFLOAT4				m_xmf4Ambient;
	XMFLOAT4				m_xmf4Diffuse;
	XMFLOAT4				m_xmf4Specular; //(r,g,b,a=power)
	XMFLOAT4				m_xmf4Emissive;
};

struct MATERIALS
{
	MATERIAL				m_pReflections[MAX_MATERIALS];
};

class CScene
{
public:
    CScene();
    ~CScene();

	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, D3D12_CPU_DESCRIPTOR_HANDLE d3dRtvCPUDescriptorHandle, ID3D12Resource *pd3dDepthStencilBuffer);
	void ReleaseObjects();

	void BuildLightsAndMaterials();

	ID3D12RootSignature *CreateGraphicsRootSignature(ID3D12Device *pd3dDevice);
	ID3D12RootSignature *GetGraphicsRootSignature(){ return(m_pd3dGraphicsRootSignature); }
	void SetGraphicsRootSignature(ID3D12GraphicsCommandList *pd3dCommandList){ pd3dCommandList->SetGraphicsRootSignature(m_pd3dGraphicsRootSignature); }

	virtual void CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void ReleaseShaderVariables();

	bool ProcessInput(UCHAR *pKeysBuffer);
    void AnimateObjects(float fTimeElapsed);
    void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera=NULL);

	void OnPrepareRender(ID3D12GraphicsCommandList* pd3dCommandList);
	void OnPreRender(ID3D12GraphicsCommandList* pd3dCommandList);
	void OnPostRender(ID3D12GraphicsCommandList *pd3dCommandList);

	void RenderParticle(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera);

	void ReleaseUploadBuffers();

	void SetDescriptorRange(D3D12_DESCRIPTOR_RANGE pd3dDescriptorRanges[], int iIndex, D3D12_DESCRIPTOR_RANGE_TYPE RangeType, UINT NumDescriptors, UINT BaseShaderRegister, UINT RegisterSpace);
	void SetRootParameterCBV____________(D3D12_ROOT_PARAMETER pd3dRootParameter[], int iIndex, UINT ShaderRegister, UINT RegisterSpace, D3D12_SHADER_VISIBILITY ShaderVisibility);
	void SetRootParameterDescriptorTable(D3D12_ROOT_PARAMETER pd3dRootParameter[], int iIndex, UINT NumDescriptorRanges, const D3D12_DESCRIPTOR_RANGE* pDescriptorRanges, D3D12_SHADER_VISIBILITY ShaderVisibility);
	void SetRootParameterConstants______(D3D12_ROOT_PARAMETER pd3dRootParameter[], int iIndex, UINT Num32BitValues, UINT ShaderRegister, UINT RegisterSpace, D3D12_SHADER_VISIBILITY ShaderVisibility);


	CPlayer							*m_pPlayer = NULL;

protected:
	ID3D12RootSignature				*m_pd3dGraphicsRootSignature = NULL;

	CShader							**m_ppShaders = NULL;
	int								m_nShaders = 0;

	BoundingBox						m_xmBoundingBox;

	LIGHTS							*m_pLights = NULL;
	float							m_fLightRotationAngle = 0.0f;

	ID3D12Resource					*m_pd3dcbLights = NULL;
	LIGHTS							*m_pcbMappedLights = NULL;

	MATERIALS						*m_pMaterials = NULL;

	ID3D12Resource					*m_pd3dcbMaterials = NULL;
	MATERIAL						*m_pcbMappedMaterials = NULL;

	CParticleObject**			m_ppParticleObjects = NULL;
	int							m_nParticleObjects = 0;
public:
	//obj 그릴때 이걸 읽어서 뎁스들을 dp, sp비교해서 그림자 여부 판단
	CDepthRenderShader*				m_pDepthRenderShader = NULL; //쉐도우맵 만들기 위해 렌더해야하니깐 ㅇ

	CShadowMapShader*				m_pShadowShader = NULL;
	//화면에 뎁스텍스쳐 그리기 위해, 디버깅 목적, 4개 다 그릴수도이씅ㅁ
	CTextureToViewportShader*		m_pShadowMapToViewport = NULL;
};

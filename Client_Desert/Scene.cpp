//-----------------------------------------------------------------------------
// File: CScene.cpp
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Scene.h"

CScene::CScene()
{
}

CScene::~CScene()
{
}

void CScene::BuildLightsAndMaterials()
{
	m_pLights = new LIGHTS;
	::ZeroMemory(m_pLights, sizeof(LIGHTS));

	m_pLights->m_xmf4GlobalAmbient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);

	m_pLights->m_pLights[0].m_bEnable = true;
	m_pLights->m_pLights[0].m_nType = DIRECTIONAL_LIGHT;
	m_pLights->m_pLights[0].m_fRange = 2000.0f;
	m_pLights->m_pLights[0].m_xmf4Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	m_pLights->m_pLights[0].m_xmf4Diffuse = XMFLOAT4(0.73f, 0.73f, 0.73f, 1.0f);
	m_pLights->m_pLights[0].m_xmf4Specular = XMFLOAT4(0.3f, 0.3f, 0.3f, 0.0f);
	m_pLights->m_pLights[0].m_xmf3Position = XMFLOAT3(-(_PLANE_WIDTH * 0.5f), 512.0f, 0.0f);
	m_pLights->m_pLights[0].m_xmf3Direction = XMFLOAT3(+1.0f, -1.0f, 0.0f);

	m_pLights->m_pLights[1].m_bEnable = false;
	m_pLights->m_pLights[1].m_nType = SPOT_LIGHT;
	m_pLights->m_pLights[1].m_fRange = 1000.0f;
	m_pLights->m_pLights[1].m_xmf4Ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	m_pLights->m_pLights[1].m_xmf4Diffuse = XMFLOAT4(0.54f, 0.54f, 0.54f, 1.0f);
	m_pLights->m_pLights[1].m_xmf4Specular = XMFLOAT4(0.13f, 0.13f, 0.13f, 0.0f);
	m_pLights->m_pLights[1].m_xmf3Position = XMFLOAT3(-50.0f, 120.0f, -5.0f);
	m_pLights->m_pLights[1].m_xmf3Direction = XMFLOAT3(0.0f, -1.0f, 1.0f);
	m_pLights->m_pLights[1].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.1f, 0.001f);
	m_pLights->m_pLights[1].m_fFalloff = 16.0f;
	m_pLights->m_pLights[1].m_fPhi = (float)cos(XMConvertToRadians(60.0f));
	m_pLights->m_pLights[1].m_fTheta = (float)cos(XMConvertToRadians(30.0f));

	m_pLights->m_pLights[2].m_bEnable = false;
	m_pLights->m_pLights[2].m_nType = SPOT_LIGHT;
	m_pLights->m_pLights[2].m_fRange = 500.0f;
	m_pLights->m_pLights[2].m_xmf4Ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	m_pLights->m_pLights[2].m_xmf4Diffuse = XMFLOAT4(0.85f, 0.85f, 0.85f, 1.0f);
	m_pLights->m_pLights[2].m_xmf4Specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	m_pLights->m_pLights[2].m_xmf3Position = XMFLOAT3(0.0f, 256.0f, 0.0f);
	m_pLights->m_pLights[2].m_xmf3Direction = XMFLOAT3(+1.0f, -1.0f, 0.0f);
	m_pLights->m_pLights[2].m_xmf3Attenuation = XMFLOAT3(0.5f, 0.01f, 0.0001f);
	m_pLights->m_pLights[2].m_fFalloff = 4.0f;
	m_pLights->m_pLights[2].m_fPhi = (float)cos(XMConvertToRadians(60.0f));
	m_pLights->m_pLights[2].m_fTheta = (float)cos(XMConvertToRadians(30.0f));

	m_pLights->m_pLights[3].m_bEnable = false;
	m_pLights->m_pLights[3].m_nType = DIRECTIONAL_LIGHT;
	m_pLights->m_pLights[3].m_fRange = 500.0f;
	m_pLights->m_pLights[3].m_xmf4Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	m_pLights->m_pLights[3].m_xmf4Diffuse = XMFLOAT4(0.83f, 0.83f, 0.83f, 1.0f);
	m_pLights->m_pLights[3].m_xmf4Specular = XMFLOAT4(0.3f, 0.3f, 0.3f, 0.0f);
	m_pLights->m_pLights[3].m_xmf3Position = XMFLOAT3(0.0f, 128.0f, 0.0f);
	m_pLights->m_pLights[3].m_xmf3Direction = XMFLOAT3(+1.0f, -1.0f, 0.0f);

	//m_pLights->m_pLights[3].m_bEnable = false;
	//m_pLights->m_pLights[3].m_nType = POINT_LIGHT;
	//m_pLights->m_pLights[3].m_fRange = 100.0f;
	//m_pLights->m_pLights[3].m_xmf4Ambient = XMFLOAT4(0.1f, 0.0f, 0.0f, 1.0f);
	//m_pLights->m_pLights[3].m_xmf4Diffuse = XMFLOAT4(0.8f, 0.0f, 0.0f, 1.0f);
	//m_pLights->m_pLights[3].m_xmf4Specular = XMFLOAT4(0.1f, 0.1f, 0.1f, 0.0f);
	//m_pLights->m_pLights[3].m_xmf3Position = XMFLOAT3(130.0f, 30.0f, 30.0f);
	//m_pLights->m_pLights[3].m_xmf3Direction = XMFLOAT3(0.0f, 0.0f, 0.0f);
	//m_pLights->m_pLights[3].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.001f, 0.0001f);

	m_pMaterials = new MATERIALS;
	::ZeroMemory(m_pMaterials, sizeof(MATERIALS));

	m_pMaterials->m_pReflections[0] = { XMFLOAT4(0.128f, 0.128f, 0.128f, 1.0f), XMFLOAT4(0.8f, 0.18f, 0.18f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 10.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)};
	m_pMaterials->m_pReflections[1] = { XMFLOAT4(0.28f, 0.28f, 0.28f, 1.0f), XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 10.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)};
	m_pMaterials->m_pReflections[2] = { XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 15.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)};
	m_pMaterials->m_pReflections[3] = { XMFLOAT4(0.5f, 0.0f, 1.0f, 1.0f), XMFLOAT4(0.0f, 0.5f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 20.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)};
	m_pMaterials->m_pReflections[4] = { XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 25.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)};
	m_pMaterials->m_pReflections[5] = { XMFLOAT4(0.0f, 0.5f, 0.5f, 1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 30.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)};
	m_pMaterials->m_pReflections[6] = { XMFLOAT4(0.5f, 0.5f, 1.0f, 1.0f), XMFLOAT4(0.5f, 0.5f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 35.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)};
	m_pMaterials->m_pReflections[7] = { XMFLOAT4(1.0f, 0.5f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 40.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)};
}

void CScene::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, D3D12_CPU_DESCRIPTOR_HANDLE d3dRtvCPUDescriptorHandle, ID3D12Resource *pd3dDepthStencilBuffer)
{
	m_pd3dGraphicsRootSignature = CreateGraphicsRootSignature(pd3dDevice);

	BuildLightsAndMaterials();

	m_nShaders = 1;
	m_ppShaders = new CShader*[m_nShaders];

	CObjectsShader *pObjectShader = new CObjectsShader();
	//pObjectShader->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, 1, NULL, DXGI_FORMAT_D24_UNORM_S8_UINT);
	pObjectShader->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);

	pObjectShader->BuildObjects(pd3dDevice, pd3dCommandList, NULL);

	m_xmBoundingBox = pObjectShader->CalculateBoundingBox();

	m_ppShaders[0] = pObjectShader;

	m_pDepthRenderShader = new CDepthRenderShader(pObjectShader, m_pLights->m_pLights);
	DXGI_FORMAT pdxgiRtvFormats[1] = { DXGI_FORMAT_R32_FLOAT };
	//m_pDepthRenderShader->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, 1, pdxgiRtvFormats, DXGI_FORMAT_D32_FLOAT);
	m_pDepthRenderShader->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);
	m_pDepthRenderShader->BuildObjects(pd3dDevice, pd3dCommandList, NULL);

	m_pShadowShader = new CShadowMapShader(pObjectShader);
	//m_pShadowShader->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, 1, NULL, DXGI_FORMAT_D24_UNORM_S8_UINT);
	m_pShadowShader->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);
	m_pShadowShader->BuildObjects(pd3dDevice, pd3dCommandList, m_pDepthRenderShader->GetDepthTexture());

	m_pShadowMapToViewport = new CTextureToViewportShader();
	//m_pShadowMapToViewport->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, 1, NULL, DXGI_FORMAT_D24_UNORM_S8_UINT);
	m_pShadowMapToViewport->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);

	m_pShadowMapToViewport->BuildObjects(pd3dDevice, pd3dCommandList, m_pDepthRenderShader->GetDepthTexture());

	CreateShaderVariables(pd3dDevice, pd3dCommandList);

	/// //////////////////////////////////
//	m_nParticleObjects = 1;	
//	m_ppParticleObjects = new CParticleObject * [m_nParticleObjects];
//
//#ifdef _WITH_BALLOON_TEXTURE
//	m_ppParticleObjects[0] = new CParticleObject(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, XMFLOAT3(0.0f, 20.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(8.0f, 12.0f), 1.0f, MAX_PARTICLES);
//#endif
}

void CScene::ReleaseObjects()
{
	if (m_pd3dGraphicsRootSignature) m_pd3dGraphicsRootSignature->Release();

	if (m_ppParticleObjects)
	{
		for (int i = 0; i < m_nParticleObjects; i++) delete m_ppParticleObjects[i];
		delete[] m_ppParticleObjects;
	}

	if (m_ppShaders)
	{
		for (int i = 0; i < m_nShaders; i++)
		{
			m_ppShaders[i]->ReleaseShaderVariables();
			m_ppShaders[i]->ReleaseObjects();
			m_ppShaders[i]->Release();
		}
		delete[] m_ppShaders;
	}

	if (m_pDepthRenderShader)
	{
		m_pDepthRenderShader->ReleaseShaderVariables();
		m_pDepthRenderShader->ReleaseObjects();
		m_pDepthRenderShader->Release();
	}

	if (m_pShadowShader)
	{
		m_pShadowShader->ReleaseShaderVariables();
		m_pShadowShader->ReleaseObjects();
		m_pShadowShader->Release();
	}

	if (m_pShadowMapToViewport)
	{
		m_pShadowMapToViewport->ReleaseShaderVariables();
		m_pShadowMapToViewport->ReleaseObjects();
		m_pShadowMapToViewport->Release();
	}

	ReleaseShaderVariables();

	if (m_pLights) delete m_pLights;
	if (m_pMaterials) delete m_pMaterials;


}

void CScene::ReleaseUploadBuffers()
{
	for (int i = 0; i < m_nShaders; i++) m_ppShaders[i]->ReleaseUploadBuffers();

	if (m_pShadowShader) m_pShadowShader->ReleaseUploadBuffers();

	if (m_pDepthRenderShader) m_pDepthRenderShader->ReleaseUploadBuffers();

	for (int i = 0; i < m_nParticleObjects; i++) m_ppParticleObjects[i]->ReleaseUploadBuffers();

}

ID3D12RootSignature *CScene::CreateGraphicsRootSignature(ID3D12Device *pd3dDevice)
{
	ID3D12RootSignature *pd3dGraphicsRootSignature = NULL;

	D3D12_DESCRIPTOR_RANGE pd3dDescriptorRanges[4];
	int iIndex = 0;
	//2번 부터 4개
	SetDescriptorRange(pd3dDescriptorRanges, iIndex++, D3D12_DESCRIPTOR_RANGE_TYPE_SRV, MAX_DEPTH_TEXTURES, 2, 0);//t2: Depth Buffer
	SetDescriptorRange(pd3dDescriptorRanges, iIndex++, D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0, 0);//t0 gtxtTexture
	SetDescriptorRange(pd3dDescriptorRanges, iIndex++, D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 1, 0);//t1: gtxtRandomTexture
	SetDescriptorRange(pd3dDescriptorRanges, iIndex++, D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 7, 0);//t1: b7 particle

	D3D12_ROOT_PARAMETER pd3dRootParameters[11];
	iIndex = 0;
	SetRootParameterConstants(pd3dRootParameters, iIndex++, 17, 0, 0, D3D12_SHADER_VISIBILITY_ALL); //Game Object
	SetRootParameterCBV(pd3dRootParameters, iIndex++, 1, 0, D3D12_SHADER_VISIBILITY_ALL);//Camera
	SetRootParameterCBV(pd3dRootParameters, iIndex++, 5, 0, D3D12_SHADER_VISIBILITY_ALL);//ToProjector
	SetRootParameterCBV(pd3dRootParameters, iIndex++, 3, 0, D3D12_SHADER_VISIBILITY_ALL);//Materials
	SetRootParameterCBV(pd3dRootParameters, iIndex++, 4, 0, D3D12_SHADER_VISIBILITY_ALL);//Lights
	SetRootParameterDescriptorTable(pd3dRootParameters, iIndex++, 1, &pd3dDescriptorRanges[0], D3D12_SHADER_VISIBILITY_PIXEL);//Depth Buffer
	SetRootParameterCBV(pd3dRootParameters, iIndex++, 6, 0, D3D12_SHADER_VISIBILITY_ALL);//ToLight
	SetRootParameterDescriptorTable(pd3dRootParameters, iIndex++, 1, &pd3dDescriptorRanges[1], D3D12_SHADER_VISIBILITY_ALL);//gtxtTexture
	SetRootParameterDescriptorTable(pd3dRootParameters, iIndex++, 1, &pd3dDescriptorRanges[2], D3D12_SHADER_VISIBILITY_ALL);//gtxtRandomTexture
	SetRootParameterDescriptorTable(pd3dRootParameters, iIndex++, 1, &pd3dDescriptorRanges[3], D3D12_SHADER_VISIBILITY_ALL);//particle
	SetRootParameterCBV(pd3dRootParameters, iIndex++, 8, 0, D3D12_SHADER_VISIBILITY_ALL);//Framework Info

	D3D12_STATIC_SAMPLER_DESC d3dSamplerDescs[4];

	d3dSamplerDescs[0].Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
	d3dSamplerDescs[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	d3dSamplerDescs[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	d3dSamplerDescs[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	d3dSamplerDescs[0].MipLODBias = 0;
	d3dSamplerDescs[0].MaxAnisotropy = 1;
	d3dSamplerDescs[0].ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
	d3dSamplerDescs[0].BorderColor = D3D12_STATIC_BORDER_COLOR_OPAQUE_WHITE; 
	d3dSamplerDescs[0].MinLOD = 0;
	d3dSamplerDescs[0].MaxLOD = D3D12_FLOAT32_MAX;
	d3dSamplerDescs[0].ShaderRegister = 0;
	d3dSamplerDescs[0].RegisterSpace = 0;
	d3dSamplerDescs[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	d3dSamplerDescs[1].Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
	d3dSamplerDescs[1].AddressU = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
	d3dSamplerDescs[1].AddressV = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
	d3dSamplerDescs[1].AddressW = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
	d3dSamplerDescs[1].MipLODBias = 0;
	d3dSamplerDescs[1].MaxAnisotropy = 1;
	d3dSamplerDescs[1].ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
	d3dSamplerDescs[1].BorderColor = D3D12_STATIC_BORDER_COLOR_OPAQUE_WHITE;
	d3dSamplerDescs[1].MinLOD = 0;
	d3dSamplerDescs[1].MaxLOD = D3D12_FLOAT32_MAX;
	d3dSamplerDescs[1].ShaderRegister = 1;
	d3dSamplerDescs[1].RegisterSpace = 0;
	d3dSamplerDescs[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	//비교 필터
	d3dSamplerDescs[2].Filter = D3D12_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
	d3dSamplerDescs[2].AddressU = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
	d3dSamplerDescs[2].AddressV = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
	d3dSamplerDescs[2].AddressW = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
	d3dSamplerDescs[2].MipLODBias = 0.0f;
	d3dSamplerDescs[2].MaxAnisotropy = 1;
	//텍스처 읽은색과 현재 깊이와 비교 - 깊이보다 더 작으면 성공 ->그림자가 아님
	d3dSamplerDescs[2].ComparisonFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL; //D3D12_COMPARISON_FUNC_LESS
	d3dSamplerDescs[2].BorderColor = D3D12_STATIC_BORDER_COLOR_OPAQUE_WHITE; // D3D12_STATIC_BORDER_COLOR_OPAQUE_BLACK;
	d3dSamplerDescs[2].MinLOD = 0;
	d3dSamplerDescs[2].MaxLOD = D3D12_FLOAT32_MAX;
	d3dSamplerDescs[2].ShaderRegister = 2;
	d3dSamplerDescs[2].RegisterSpace = 0;
	d3dSamplerDescs[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	d3dSamplerDescs[3].Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
	d3dSamplerDescs[3].AddressU = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
	d3dSamplerDescs[3].AddressV = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
	d3dSamplerDescs[3].AddressW = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
	d3dSamplerDescs[3].MipLODBias = 0.0f;
	d3dSamplerDescs[3].MaxAnisotropy = 1;
	d3dSamplerDescs[3].ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
	d3dSamplerDescs[3].BorderColor = D3D12_STATIC_BORDER_COLOR_OPAQUE_BLACK; 
	d3dSamplerDescs[3].MinLOD = 0;
	d3dSamplerDescs[3].MaxLOD = D3D12_FLOAT32_MAX;
	d3dSamplerDescs[3].ShaderRegister = 3;
	d3dSamplerDescs[3].RegisterSpace = 0;
	d3dSamplerDescs[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	//so단계 허용
	D3D12_ROOT_SIGNATURE_FLAGS d3dRootSignatureFlags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT | D3D12_ROOT_SIGNATURE_FLAG_ALLOW_STREAM_OUTPUT;
	D3D12_ROOT_SIGNATURE_DESC d3dRootSignatureDesc;
	::ZeroMemory(&d3dRootSignatureDesc, sizeof(D3D12_ROOT_SIGNATURE_DESC));
	d3dRootSignatureDesc.NumParameters = _countof(pd3dRootParameters);
	d3dRootSignatureDesc.pParameters = pd3dRootParameters;
	d3dRootSignatureDesc.NumStaticSamplers = _countof(d3dSamplerDescs);
	d3dRootSignatureDesc.pStaticSamplers = d3dSamplerDescs;
	d3dRootSignatureDesc.Flags = d3dRootSignatureFlags;

	ID3DBlob *pd3dSignatureBlob = NULL;
	ID3DBlob *pd3dErrorBlob = NULL;
	HRESULT hResult = D3D12SerializeRootSignature(&d3dRootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &pd3dSignatureBlob, &pd3dErrorBlob);
	pd3dDevice->CreateRootSignature(0, pd3dSignatureBlob->GetBufferPointer(), pd3dSignatureBlob->GetBufferSize(), __uuidof(ID3D12RootSignature), (void **)&pd3dGraphicsRootSignature);
	if (pd3dSignatureBlob) pd3dSignatureBlob->Release();
	if (pd3dErrorBlob) pd3dErrorBlob->Release();

	return(pd3dGraphicsRootSignature);
}

void CScene::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
	UINT ncbLightElementBytes = ((sizeof(LIGHTS) + 255) & ~255); //256의 배수
	m_pd3dcbLights = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, ncbLightElementBytes, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);

	m_pd3dcbLights->Map(0, NULL, (void **)&m_pcbMappedLights);

	UINT ncbMaterialElementBytes = ((sizeof(MATERIALS) + 255) & ~255); //256의 배수
	m_pd3dcbMaterials = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, ncbMaterialElementBytes, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);

	m_pd3dcbMaterials->Map(0, NULL, (void **)&m_pcbMappedMaterials);
}

void CScene::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
{
	::memcpy(m_pcbMappedLights, m_pLights, sizeof(LIGHTS));
	::memcpy(m_pcbMappedMaterials, m_pMaterials, sizeof(MATERIALS));
}

void CScene::ReleaseShaderVariables()
{
	if (m_pd3dcbLights)
	{
		m_pd3dcbLights->Unmap(0, NULL);
		m_pd3dcbLights->Release();
	}
	if (m_pd3dcbMaterials)
	{
		m_pd3dcbMaterials->Unmap(0, NULL);
		m_pd3dcbMaterials->Release();
	}
}

bool CScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	return(false);
}

bool CScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	return(false);
}

bool CScene::ProcessInput(UCHAR *pKeysBuffer)
{
	return(false);
}

void CScene::AnimateObjects(float fTimeElapsed)
{
	for (int i = 0; i < m_nShaders; i++)
	{
		m_ppShaders[i]->AnimateObjects(fTimeElapsed);
	}

	if (m_pLights)
	{
//		m_pLights->m_pLights[1].m_xmf3Position = m_pPlayer->GetCamera()->GetPosition();
//		m_pLights->m_pLights[1].m_xmf3Direction = m_pPlayer->GetCamera()->GetLookVector();

		m_fLightRotationAngle += fTimeElapsed * 0.25f;
		XMMATRIX xmmtxRotation = XMMatrixRotationY(fTimeElapsed * 0.25f);
		XMStoreFloat3(&m_pLights->m_pLights[1].m_xmf3Direction, XMVector3TransformNormal(XMLoadFloat3(&m_pLights->m_pLights[1].m_xmf3Direction), xmmtxRotation));
	}

	for (int i = 0; i < m_nParticleObjects; i++) m_ppParticleObjects[i]->Animate(fTimeElapsed);
}

//각 프레임마다 제일 먼저 호출됨
void CScene::OnPreRender(ID3D12GraphicsCommandList* pd3dCommandList)
{
	//각 조명에서 쉐도우맵 만드는 역할, 
	m_pDepthRenderShader->PrepareShadowMap(pd3dCommandList);
}

void CScene::OnPostRender(ID3D12GraphicsCommandList* pd3dCommandList)
{
}

void CScene::OnPrepareRender(ID3D12GraphicsCommandList* pd3dCommandList)
{
	pd3dCommandList->SetGraphicsRootSignature(m_pd3dGraphicsRootSignature);

	UpdateShaderVariables(pd3dCommandList);

	if (m_pd3dcbMaterials)
	{
		D3D12_GPU_VIRTUAL_ADDRESS d3dcbMaterialsGpuVirtualAddress = m_pd3dcbMaterials->GetGPUVirtualAddress();
		pd3dCommandList->SetGraphicsRootConstantBufferView(3, d3dcbMaterialsGpuVirtualAddress); //Materials
	}
	if (m_pd3dcbLights)
	{
		D3D12_GPU_VIRTUAL_ADDRESS d3dcbLightsGpuVirtualAddress = m_pd3dcbLights->GetGPUVirtualAddress();
		pd3dCommandList->SetGraphicsRootConstantBufferView(4, d3dcbLightsGpuVirtualAddress); //Lights
	}
}

void CScene::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	//쉐도우맵이 갖고있는 텍스쳐 정보를 set
	m_pDepthRenderShader->UpdateShaderVariables(pd3dCommandList);

	pCamera->SetViewportsAndScissorRects(pd3dCommandList);
	pCamera->UpdateShaderVariables(pd3dCommandList);

	//그림자 그린다-오브젝트 그린다
	if (m_pShadowShader) m_pShadowShader->Render(pd3dCommandList, pCamera);
	
	//화면에 뎁스 텍스쳐 그린다
	if (m_pShadowMapToViewport) m_pShadowMapToViewport->Render(pd3dCommandList, pCamera);

	pCamera->SetViewportsAndScissorRects(pd3dCommandList);
	pCamera->UpdateShaderVariables(pd3dCommandList);
}

void CScene::RenderParticle(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	for (int i = 0; i < m_nParticleObjects; i++) m_ppParticleObjects[i]->Render(pd3dCommandList, pCamera);
}





/// ////////////////////////////////////////////////////////////
void CScene::SetDescriptorRange(D3D12_DESCRIPTOR_RANGE pd3dDescriptorRanges[], int iIndex, D3D12_DESCRIPTOR_RANGE_TYPE RangeType, UINT NumDescriptors, UINT BaseShaderRegister, UINT RegisterSpace)
{
	pd3dDescriptorRanges[iIndex].RangeType = RangeType;
	pd3dDescriptorRanges[iIndex].NumDescriptors = NumDescriptors;
	pd3dDescriptorRanges[iIndex].BaseShaderRegister = BaseShaderRegister;
	pd3dDescriptorRanges[iIndex].RegisterSpace = RegisterSpace;
	pd3dDescriptorRanges[iIndex].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
}

void CScene::SetRootParameterCBV(D3D12_ROOT_PARAMETER pd3dRootParameter[], int iIndex, UINT ShaderRegister, UINT RegisterSpace, D3D12_SHADER_VISIBILITY ShaderVisibility)
{
	pd3dRootParameter[iIndex].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	pd3dRootParameter[iIndex].Descriptor.ShaderRegister = ShaderRegister;
	pd3dRootParameter[iIndex].Descriptor.RegisterSpace = RegisterSpace;
	pd3dRootParameter[iIndex].ShaderVisibility = ShaderVisibility;
}

void CScene::SetRootParameterDescriptorTable(D3D12_ROOT_PARAMETER pd3dRootParameter[], int iIndex, UINT NumDescriptorRanges, const D3D12_DESCRIPTOR_RANGE* pDescriptorRanges, D3D12_SHADER_VISIBILITY ShaderVisibility)
{
	pd3dRootParameter[iIndex].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameter[iIndex].DescriptorTable.NumDescriptorRanges = NumDescriptorRanges;
	pd3dRootParameter[iIndex].DescriptorTable.pDescriptorRanges = pDescriptorRanges;
	pd3dRootParameter[iIndex].ShaderVisibility = ShaderVisibility;
}

void CScene::SetRootParameterConstants(D3D12_ROOT_PARAMETER pd3dRootParameter[], int iIndex, UINT Num32BitValues, UINT ShaderRegister, UINT RegisterSpace, D3D12_SHADER_VISIBILITY ShaderVisibility)
{
	pd3dRootParameter[iIndex].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	pd3dRootParameter[iIndex].Constants.Num32BitValues = Num32BitValues;
	pd3dRootParameter[iIndex].Constants.ShaderRegister = ShaderRegister;
	pd3dRootParameter[iIndex].Constants.RegisterSpace = RegisterSpace;
	pd3dRootParameter[iIndex].ShaderVisibility = ShaderVisibility;
}


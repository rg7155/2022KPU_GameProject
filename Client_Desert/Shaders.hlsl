cbuffer cbGameObjectInfo : register(b0)
{
	matrix		gmtxWorld : packoffset(c0);
	uint		gnMaterial : packoffset(c4);
};

cbuffer cbCameraInfo : register(b1)
{
	matrix		gmtxView : packoffset(c0);
	matrix		gmtxProjection : packoffset(c4);
	float3		gvCameraPosition : packoffset(c8);
};

#include "Light.hlsl"

struct CB_TOOBJECTSPACE
{
	matrix		mtxToTexture;
	float4		f4Position;
};

cbuffer cbToLightSpace : register(b6)
{
	CB_TOOBJECTSPACE gcbToLightSpaces[MAX_LIGHTS];
};

cbuffer cbParticleInfo : register(b7)
{
    matrix gmtxParticleWorld : packoffset(c0);
};

cbuffer cbFrameworkInfo : register(b8)
{
    float gfCurrentTime : packoffset(c0.x);
    float gfElapsedTime : packoffset(c0.y);
    float gfShadowMapIndex : packoffset(c0.z);
};

//ConstantBuffer<CB_TOOBJECTSPACE> gcbToLightSpaces[MAX_LIGHTS] : register(b6);

struct VS_DIFFUSED_INPUT
{
	float3 position : POSITION;
	float4 color : COLOR;
};

struct VS_DIFFUSED_OUTPUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

VS_DIFFUSED_OUTPUT VSDiffused(VS_DIFFUSED_INPUT input)
{
	VS_DIFFUSED_OUTPUT output;

	output.position = mul(mul(mul(float4(input.position, 1.0f), gmtxWorld), gmtxView), gmtxProjection);
	output.color = input.color;

	return(output);
}

float4 PSDiffused(VS_DIFFUSED_OUTPUT input) : SV_TARGET
{
	return(input.color);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//VS_DIFFUSED_OUTPUT VSPlayer(VS_DIFFUSED_INPUT input)
//{
//	VS_DIFFUSED_OUTPUT output;

//	output.position = mul(mul(mul(float4(input.position, 1.0f), gmtxWorld), gmtxView), gmtxProjection);
//	output.color = input.color;

//	return(output);
//}

//float4 PSPlayer(VS_DIFFUSED_OUTPUT input) : SV_TARGET
//{
//	return(input.color);
//}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
struct VS_LIGHTING_INPUT
{
	float3 position : POSITION;
	float3 normal : NORMAL;
};

struct VS_LIGHTING_OUTPUT
{
	float4 position : SV_POSITION;
	float3 positionW : POSITION;
	float3 normalW : NORMAL;
};

VS_LIGHTING_OUTPUT VSLighting(VS_LIGHTING_INPUT input)
{
	VS_LIGHTING_OUTPUT output;

	output.normalW = mul(input.normal, (float3x3)gmtxWorld);
	output.positionW = (float3)mul(float4(input.position, 1.0f), gmtxWorld);
	output.position = mul(mul(float4(output.positionW, 1.0f), gmtxView), gmtxProjection);

	return(output);
}

float4 PSLighting(VS_LIGHTING_OUTPUT input) : SV_TARGET
{
	input.normalW = normalize(input.normalW);
	float4 uvs[MAX_LIGHTS];
	float4 cIllumination = Lighting(input.positionW, input.normalW, false, uvs);

//	return(cIllumination);
	return(float4(input.normalW * 0.5f + 0.5f, 1.0f));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//


//struct VS_TEXTURED_LIGHTING_INPUT
//{
//    float3 position : POSITION;
//    float3 normal : NORMAL;
//    float2 uv : TEXCOORD;
//};

//struct VS_TEXTURED_LIGHTING_OUTPUT
//{
//    float4 position : SV_POSITION;
//    float3 positionW : POSITION;
//    float3 normalW : NORMAL;
//    float2 uv : TEXCOORD;
//};

//VS_TEXTURED_LIGHTING_OUTPUT VSTexturedLighting(VS_TEXTURED_LIGHTING_INPUT input)
//{
//    VS_TEXTURED_LIGHTING_OUTPUT output;

//    output.normalW = mul(input.normal, (float3x3) gmtxWorld);
//    output.positionW = (float3) mul(float4(input.position, 1.0f), gmtxWorld);
//    output.position = mul(mul(float4(output.positionW, 1.0f), gmtxView), gmtxProjection);
//    output.uv = input.uv;

//    return (output);
//}

//float4 PSTexturedLighting(VS_TEXTURED_LIGHTING_OUTPUT input, uint nPrimitiveID : SV_PrimitiveID) : SV_TARGET
//{
//    float4 cColor = gtxtTexture.Sample(gWrapSamplerState, input.uv);
//    input.normalW = normalize(input.normalW);
//	float4 uvs[MAX_LIGHTS];
//    float4 cIllumination = Lighting(input.positionW, input.normalW, false, uvs);

//    return (cColor * cIllumination);
//}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

struct PS_DEPTH_OUTPUT
{
	float fzPosition : SV_Target;
	float fDepth : SV_Depth;
};

//깊이를 저장하는 PS
PS_DEPTH_OUTPUT PSDepthWriteShader(VS_LIGHTING_OUTPUT input)
{
	PS_DEPTH_OUTPUT output;

	//원투 나누기 한 좌표-깊이
	output.fzPosition = input.position.z;
	output.fDepth = input.position.z;

	return(output);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
struct VS_SHADOW_MAP_OUTPUT 
{
	float4 position : SV_POSITION;
	float3 positionW : POSITION;     
	float3 normalW : NORMAL;

	float4 uvs[MAX_LIGHTS] : TEXCOORD0;
};

VS_SHADOW_MAP_OUTPUT VSShadowMapShadow(VS_LIGHTING_INPUT input)
{
	VS_SHADOW_MAP_OUTPUT output = (VS_SHADOW_MAP_OUTPUT)0;

	float4 positionW = mul(float4(input.position, 1.0f), gmtxWorld);
	output.positionW = positionW.xyz;
	output.position = mul(mul(positionW, gmtxView), gmtxProjection);
	output.normalW = mul(float4(input.normal, 0.0f), gmtxWorld).xyz;

	for (int i = 0; i < MAX_LIGHTS; i++)
	{
		//0은 조명끔, 조명 좌표계로 바꾸고 텍스쳐 좌표계로 바꿈
		if (gcbToLightSpaces[i].f4Position.w != 0.0f) output.uvs[i] = mul(positionW, gcbToLightSpaces[i].mtxToTexture);
	}

	return(output);
}

float4 PSShadowMapShadow(VS_SHADOW_MAP_OUTPUT input) : SV_TARGET
{
	//그림자면 어둡고 아니면 원래 조명 색
	float4 cIllumination = Lighting(input.positionW, normalize(input.normalW), true, input.uvs);

	return(cIllumination);
}

///////////////////////////////////////////////////////////////////////////////
//
struct VS_TEXTURED_OUTPUT
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
};

VS_TEXTURED_OUTPUT VSTextureToViewport(uint nVertexID : SV_VertexID)
{
	VS_TEXTURED_OUTPUT output = (VS_TEXTURED_OUTPUT)0;

	if (nVertexID == 0) { output.position = float4(-1.0f, +1.0f, 0.0f, 1.0f); output.uv = float2(0.0f, 0.0f); }
	if (nVertexID == 1) { output.position = float4(+1.0f, +1.0f, 0.0f, 1.0f); output.uv = float2(1.0f, 0.0f); }
	if (nVertexID == 2) { output.position = float4(+1.0f, -1.0f, 0.0f, 1.0f); output.uv = float2(1.0f, 1.0f); }
	if (nVertexID == 3) { output.position = float4(-1.0f, +1.0f, 0.0f, 1.0f); output.uv = float2(0.0f, 0.0f); }
	if (nVertexID == 4) { output.position = float4(+1.0f, -1.0f, 0.0f, 1.0f); output.uv = float2(1.0f, 1.0f); }
	if (nVertexID == 5) { output.position = float4(-1.0f, -1.0f, 0.0f, 1.0f); output.uv = float2(0.0f, 1.0f); }

	return(output);
}

float4 GetColorFromDepth(float fDepth)
{
	float4 cColor = float4(0.0f, 0.0f, 0.0f, 1.0f);

	if (fDepth < 0.00625f) cColor = float4(1.0f, 0.0f, 0.0f, 1.0f);
	else if (fDepth < 0.0125f) cColor = float4(0.0f, 1.0f, 0.0f, 1.0f);
	else if (fDepth < 0.025f) cColor = float4(0.0f, 0.0f, 1.0f, 1.0f);
	else if (fDepth < 0.05f) cColor = float4(1.0f, 1.0f, 0.0f, 1.0f);
	else if (fDepth < 0.075f) cColor = float4(0.0f, 1.0f, 1.0f, 1.0f);
	else if (fDepth < 0.1f) cColor = float4(1.0f, 0.5f, 0.5f, 1.0f);
	else if (fDepth < 0.4f) cColor = float4(0.5f, 1.0f, 1.0f, 1.0f);
	else if (fDepth < 0.6f) cColor = float4(1.0f, 0.0f, 1.0f, 1.0f);
	else if (fDepth < 0.8f) cColor = float4(0.5f, 0.5f, 1.0f, 1.0f);
	else if (fDepth < 0.9f) cColor = float4(0.5f, 1.0f, 0.5f, 1.0f);
	else if (fDepth < 0.95f) cColor = float4(0.5f, 0.0f, 0.5f, 1.0f);
	else if (fDepth < 0.99f) cColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
	else if (fDepth < 0.999f) cColor = float4(1.0f, 0.0f, 1.0f, 1.0f);
	else if (fDepth == 1.0f) cColor = float4(0.5f, 0.5f, 0.5f, 1.0f);
	else if (fDepth > 1.0f) cColor = float4(0.0f, 0.0f, 0.5f, 1.0f);
	else cColor = float4(0.0f, 0.0f, 0.0f, 1.0f);

	return(cColor);
}

SamplerState gssBorder : register(s3);

float4 PSTextureToViewport(VS_TEXTURED_OUTPUT input) : SV_Target
{
    float fDepthFromLight0 = gtxtDepthTextures[ /*0*/gfShadowMapIndex].SampleLevel(gssBorder, input.uv, 0).r;

	return((float4)(fDepthFromLight0 * 0.8f));
}






////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//Texture2D gtxtTexture : register(t0);
SamplerState gWrapSamplerState : register(s0);

#define PARTICLE_TYPE_EMITTER	0 //정점을 만드는
#define PARTICLE_TYPE_FLARE		0x0ff //다른파티클을 생성하지 못하는?

struct VS_PARTICLE_INPUT
{
    float3 position : POSITION;
    float3 color : COLOR;
    float3 velocity : VELOCITY;
    float3 acceleration : ACCELERATION; //가속도
    float2 size : SIZE;
    float2 age : AGELIFETIME; //(Age, Lifetime)
    uint type : PARTICLETYPE;
};

VS_PARTICLE_INPUT VSParticleStreamOutput(VS_PARTICLE_INPUT input)
{
    return (input);
}

Buffer<float4> gRandomBuffer : register(t1);

float3 GetParticleColor(float fAge, float fLifetime)
{
    float3 cColor = float3(1.0f, 1.0f, 1.0f);

    if (fAge == 0.0f)
        cColor = float3(0.0f, 1.0f, 0.0f);
    else if (fLifetime == 0.0f) 
        cColor = float3(1.0f, 1.0f, 0.0f);
    else
    {
        float t = fAge / fLifetime;
        cColor = lerp(float3(1.0f, 0.0f, 0.0f), float3(0.0f, 0.0f, 1.0f), t * 1.0f);
    }

    return (cColor);
}

void GetBillboardCorners(float3 position, float2 size, out float4 pf4Positions[4])
{
    float3 f3Up = float3(0.0f, 1.0f, 0.0f);
    float3 f3Look = normalize(gvCameraPosition - position);
    float3 f3Right = normalize(cross(f3Up, f3Look));

    pf4Positions[0] = float4(position + size.x * f3Right - size.y * f3Up, 1.0f);
    pf4Positions[1] = float4(position + size.x * f3Right + size.y * f3Up, 1.0f);
    pf4Positions[2] = float4(position - size.x * f3Right - size.y * f3Up, 1.0f);
    pf4Positions[3] = float4(position - size.x * f3Right + size.y * f3Up, 1.0f);
}

void GetPositions(float3 position, float2 f2Size, out float3 pf3Positions[8])
{
    float3 f3Right = float3(1.0f, 0.0f, 0.0f);
    float3 f3Up = float3(0.0f, 1.0f, 0.0f);
    float3 f3Look = float3(0.0f, 0.0f, 1.0f);

    float3 f3Extent = normalize(float3(1.0f, 1.0f, 1.0f));

    pf3Positions[0] = position + float3(-f2Size.x, 0.0f, -f2Size.y);
    pf3Positions[1] = position + float3(-f2Size.x, 0.0f, +f2Size.y);
    pf3Positions[2] = position + float3(+f2Size.x, 0.0f, -f2Size.y);
    pf3Positions[3] = position + float3(+f2Size.x, 0.0f, +f2Size.y);
    pf3Positions[4] = position + float3(-f2Size.x, 0.0f, 0.0f);
    pf3Positions[5] = position + float3(+f2Size.x, 0.0f, 0.0f);
    pf3Positions[6] = position + float3(0.0f, 0.0f, +f2Size.y);
    pf3Positions[7] = position + float3(0.0f, 0.0f, -f2Size.y);
}

[maxvertexcount(9)]
//[maxvertexcount(2)]

void GSParticleStreamOutput(point VS_PARTICLE_INPUT input[1], inout PointStream<VS_PARTICLE_INPUT> output)
{
    VS_PARTICLE_INPUT particle = input[0];

    particle.age.x += gfElapsedTime;
    if (particle.age.x <= particle.age.y)
    {
        if (particle.type == PARTICLE_TYPE_EMITTER)
        {
            particle.color = float3(1.0f, 0.0f, 0.0f);
            output.Append(particle);

            float4 f4Random = gRandomBuffer.Load(int(fmod(gfCurrentTime - floor(gfCurrentTime) * 1000.0f, 1000.0f)));

            float3 pf3Positions[8];
            GetPositions(particle.position, float2(particle.size.x /** 1.25f*/, particle.size.x/* * 1.25f*/), pf3Positions);

            particle.color = float3(0.f, 0.0f, 1.0f);
            
            particle.age.x = 0.0f;

            for (int j = 0; j < 8; j++)
            {
                float4 f4Random2 = gRandomBuffer.Load(int(fmod((gfCurrentTime - floor(gfCurrentTime)) * 1000.0f, 1000.0f)));
                
                particle.type = PARTICLE_TYPE_FLARE;
                
                particle.position = pf3Positions[j].xyz + (f4Random2.xyz * 100.f);
                particle.velocity = float3(0.0f, particle.size.x * particle.age.y * 10.0f, 0.0f);
                particle.acceleration = float3(10.0f, 250.f, 10.0f) * abs(f4Random2.x);
                particle.age.y = 2.f; //수명
                
                output.Append(particle);
            }
        }
        else
        {
            //particle.color = GetParticleColor(particle.age.x, particle.age.y);
            particle.color = float3(1.f, 1.f, 1.f);
            
            particle.position += (0.5f * particle.acceleration * gfElapsedTime * gfElapsedTime) + (particle.velocity * gfElapsedTime);

            output.Append(particle);
        }
    }
	
	
    //VS_PARTICLE_INPUT particle = input[0];
    //particle.age.x += gfElapsedTime;
    //if (particle.type == PARTICLE_TYPE_EMITTER)
    //{
    //    if (particle.age.x > 0.2f) //2초마다 생성
    //    {
    //        VS_PARTICLE_INPUT newParticle = input[0];
    //        for (int i = 0; i < 1 /*9*/; ++i)
    //        {
    //            float4 f4Random = gRandomBuffer.Load(int(fmod((gfCurrentTime - floor(gfCurrentTime)) * 1000.0f, 1000.0f)));
    //            //float4 f4Random = gRandomBuffer.Load(int((gfCurrentTime * 1000.f) % 1000.f));
    //            //float4 f4Random = gRandomBuffer.Load(int( (gfCurrentTime - floor(gfCurrentTime))  * 1000.0f));
                
				
    //            //f4Random = normalize(f4Random);
    //            //f4Random.x = (f4Random.x * 500.f) % 500.f;
    //            //f4Random.z = (f4Random.z * 500.f) % 500.f;
    //            f4Random *= 500.f;
    //            f4Random.y = 20.f;

    //            newParticle.position = float3(f4Random.x, f4Random.y, f4Random.z);
    //            //newParticle.position = float3(0.f + i * 10.f, 40.f, 0.f);
    //            //float fColor = normalize(f4Random.x);
    //            //newParticle.color = float3(fColor, fColor, fColor);
    //            newParticle.velocity = float3(0.f, 1.f, 0.f);
    //            newParticle.age = float2(0.f, 10.f);
    //            newParticle.type = PARTICLE_TYPE_FLARE; // 0?
    //            output.Append(newParticle);
    //        }
			
    //        particle.age.x = 0.f;
    //    }
    //    output.Append(particle);
    //}
    //else
    //{
    //    if (particle.age.x <= particle.age.y) //lifetime
    //    {
    //        output.Append(particle);
    //    }
    //}
		
	
}

VS_PARTICLE_INPUT VSParticleDraw(VS_PARTICLE_INPUT input)
{
    return (input);
	
	
    //VS_PARTICLE_INPUT output = input;
    //float t = input.age.x;
    ////output.position = (input.velocity * t * 100.f) + input.position;
    //float3 f3Acceleration = float3(0.f, 40.f, 1.f);
    //output.position = (0.5f * f3Acceleration * t * t) + (input.velocity * t * 10.f) + input.position;
    
    //return output;

}

struct GS_PARTICLE_OUTPUT
{
    float4 position : SV_Position;
    float3 color : COLOR;
    float2 uv : TEXCOORD;
    float2 age : AGELIFETIME; //(Age, Lifetime)
    uint type : PARTICLETYPE;
};

static float2 gf2QuadUVs[4] = { float2(0.0f, 1.0f), float2(0.0f, 0.0f), float2(1.0f, 1.0f), float2(1.0f, 0.0f) };

//빌보드 사각형으로 파티클 그림
[maxvertexcount(4)]
void GSParticleDraw(point VS_PARTICLE_INPUT input[1], inout TriangleStream<GS_PARTICLE_OUTPUT> outputStream)
{
    float4 pVertices[4];
//	GetBillboardCorners(input[0].position, input[0].size * 0.5f, pVertices);
    GetBillboardCorners(mul(float4(input[0].position, 1.0f), /*gmtxWorld*/gmtxParticleWorld).xyz, input[0].size * 0.5f, pVertices);

    GS_PARTICLE_OUTPUT output = (GS_PARTICLE_OUTPUT) 0;
    output.color = input[0].color;
    output.age = input[0].age;
    output.type = input[0].type;
    for (int i = 0; i < 4; i++)
    {
        output.position = mul(mul(pVertices[i], gmtxView), gmtxProjection);
        output.uv = gf2QuadUVs[i];

        outputStream.Append(output);
    }
}

Texture2D<float4> gtxtParticleTexture : register(t0);

float4 PSParticleDraw(GS_PARTICLE_OUTPUT input) : SV_TARGET
{
    float4 cColor = gtxtParticleTexture.Sample(gWrapSamplerState, input.uv);
    if (input.type == PARTICLE_TYPE_FLARE)
    {
        cColor *= float4(input.color,1.f);
        
//		cColor.a *= saturate(0.10f + (1.0f - (input.age.x / input.age.y)));
		//	cColor.rgb *= input.color * (input.age.x / input.age.y);
		//	cColor.rgb = GetParticleColor(gfElapsedTime, gfElapsedTime);
        //cColor.rgb *= GetParticleColor(input.age.x, input.age.y);
//		cColor.rgb = saturate(1.0f - input.age.x);
		//	cColor.rgb = abs(gRandomBuffer.Load(int(fmod(gfCurrentTime, 1000.0f))).rgb);
		//	cColor.rgb = 1.0f;
		//	cColor.b = (input.age.x / input.age.y);
    }

    return (cColor);
}
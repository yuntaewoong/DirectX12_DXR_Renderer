#ifndef DATA_TYPE_SHARED_BOTH_HLSL_AND_CPP_H
#define DATA_TYPE_SHARED_BOTH_HLSL_AND_CPP_H

#define NUM_LIGHT 2 //빛 개수
#define MAX_RECURSION_DEPTH 20 //TraceRay재귀 호출 depth
#define NUM_RTAO_RAY 4 // RTAO에 사용할 Ray수
#define RTAO_RADIUS 0.2  // RTAO에 적용할 반구의 반지름


#ifdef HLSL//HLSL에서 include시
//전처리기를 이용해 HLSL에서도 c++에서도 같은 파일을 Include시켜주는 트릭
typedef float FLOAT;
typedef float2 XMFLOAT2;
typedef float3 XMFLOAT3;
typedef float4 XMFLOAT4;
typedef float4 XMVECTOR;
typedef float4x4 XMMATRIX;
typedef uint UINT;

#else//CPP에서 include시
#include <DirectXMath.h>
using namespace DirectX;
struct Index//Index구조체는 HLSL에서 필요없음(HLSL Index버퍼 형식인 ByteAddressBuffer는 기본 2바이트씩 Offset을 가짐)
{
    UINT16 index;
};

#endif

struct CameraConstantBuffer
{
    XMMATRIX projectionToWorld;
    XMVECTOR cameraPosition;
};

struct PointLightConstantBuffer
{
    XMVECTOR position[NUM_LIGHT];
};

struct MeshConstantBuffer
{
    XMMATRIX world;//float(32bit)가 16개 -> DWORD 16개필요
    XMFLOAT4 albedo;//float(32bit)가 4개 -> DWORD 4개 필요
    UINT hasDiffuseTexture;//1이면 texture있음, 0이면 없음, 32bit가 1개 -> DWORD 1개 필요
    UINT hasNormalTexture;//1이면 texture있음, 0이면 없음, 32bit가 1개 -> DWORD 1개 필요
    UINT hasSpecularTexture;//1이면 texture있음, 0이면 없음, 32bit가 1개 -> DWORD 1개 필요
    UINT hasRoughnessTexture;//1이면 texture있음, 0이면 없음, 32bit가 1개 -> DWORD 1개 필요
    UINT hasMetallicTexture;//1이면 texture있음, 0이면 없음, 32bit가 1개 -> DWORD 1개 필요
    UINT materialType;//MaterialType::Enum자료형을 UINT로 표현, 32bit가 1개 -> DWORD 1개 필요
    FLOAT reflectivity;//1이면 거울,0이면 무반사, 32bit가 1개 -> DWORD 1개 필요
    FLOAT roughness;//거친정도, 32bit가 1개 -> DWORD 1개 필요
    FLOAT metallic;//금속인 정도, 32bit가 1개 -> DWORD 1개 필요
};

struct Vertex
{
    XMFLOAT3 position;
    XMFLOAT2 uv;
    XMFLOAT3 normal;
    XMFLOAT3 tangent;
    XMFLOAT3 biTangent;
};
struct RayPayload
{
    XMFLOAT4 color;
    UINT recursionDepth;//얼마나 재귀호출되었는가?
};

struct ShadowRayPayload
{
    FLOAT hit; // 1이면 Hit, 0이면 Miss
};

struct RTAORayPayload
{
    FLOAT tHit; // at + b직선 방정식의 t값
};

namespace MaterialType
{
    enum Enum {
        Phong = 0,
        PBR
    };
}


namespace RayType 
{
    enum Enum {
        Radiance = 0,   
        Shadow,
        RTAO
    };
    static const UINT Count = 3;
}

namespace TraceRayParameters
{
    static const UINT InstanceMask = ~0; 
    static const UINT HitGroupOffset[RayType::Count] = {
        0, // Radiance ray
        1, // Shadow ray
        2  // RTAO ray
    };
    static const UINT GeometryStride = RayType::Count;
    static const UINT MissShaderOffset[RayType::Count] = {
        0, // Radiance ray
        1, // Shadow ray
        2  // RTAO ray
    };
}



#endif
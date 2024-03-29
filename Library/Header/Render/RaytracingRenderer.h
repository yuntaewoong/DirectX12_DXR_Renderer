#pragma once

#include "Common\Common.h"
#include "Render\FundamentalRenderingResources.h"
#include "AccelerationStructure\TopLevelAccelerationStructure.h"
#include "AccelerationStructure\BottomLevelAccelerationStructure.h"
#include "Scene\Scene.h"
#include "Camera\Camera.h"
#include "ShaderTable\HitGroupShaderTable.h"
#include "ShaderTable\MissShaderTable.h"
#include "ShaderTable\RayGenerationShaderTable.h"
#include "RootSignature\GlobalRootSignature.h"
#include "RootSignature\LocalRootSignature.h"
#include "RaytracingPipelineStateObject\RaytracingPipelineStateObject.h"
#include "Texture\Texture.h"

namespace library
{
	class RaytracingRenderer
	{
	public:
        RaytracingRenderer();
        RaytracingRenderer(const RaytracingRenderer& other) = delete;
        RaytracingRenderer(RaytracingRenderer&& other) = delete;
        RaytracingRenderer& operator=(const RaytracingRenderer& other) = delete;
        RaytracingRenderer& operator=(RaytracingRenderer&& other) = delete;
		~RaytracingRenderer() = default;

        HRESULT Initialize(_In_ HWND hWnd);
        void HandleInput(_In_ const DirectionsInput& directions, _In_ const MouseRelativeMovement& mouseRelativeMovement, _In_ FLOAT deltaTime);
        void SetMainScene(_In_ const std::shared_ptr<Scene>& pScene);
        void Render();
        void Update(_In_ FLOAT deltaTime);
    private:
        HRESULT populateCommandList();

        //이하 함수는 ray tacing 관련함수

        HRESULT createRaytracingInterfaces();
        HRESULT createRaytracingRootSignature();
        HRESULT createRaytracingPipelineStateObject();
        HRESULT createAccelerationStructure();
        HRESULT createShaderTable();
        HRESULT createRaytacingOutputResource(_In_ HWND hWnd);
    private:
        FundamentalRenderingResources m_renderingResources;
        std::shared_ptr<Scene> m_scene;
        Camera m_camera;

        // DXR파이프라인 관련
        ComPtr<ID3D12Device5> m_dxrDevice;
        ComPtr<ID3D12GraphicsCommandList4> m_dxrCommandList;

        // Pipeline State Object
        RaytracingPipelineStateObject m_raytracingPipelineStateObject;

        //ray tracing전용 root signature
        GlobalRootSignature m_globalRootSignature;
        LocalRootSignature m_localRootSignature;
        
        //ray tracing BLAS,TLAS
        TopLevelAccelerationStructure m_topLevelAccelerationStructure;
        std::vector<std::unique_ptr<BottomLevelAccelerationStructure>> m_bottomLevelAccelerationStructures;

        //ray tracing Shader Table자원
        MissShaderTable m_missShaderTable;
        HitGroupShaderTable m_hitGroupShaderTable;
        RayGenerationShaderTable m_rayGenShaderTable;

        // Raytracing  결과 UAV자원
        ComPtr<ID3D12Resource> m_raytracingOutput;
        D3D12_GPU_DESCRIPTOR_HANDLE m_raytracingOutputGPUHandle;


	};
}
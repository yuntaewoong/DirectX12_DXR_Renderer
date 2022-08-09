#pragma once

#include "Common\Common.h"
#include "Common\ShaderDataType.h"
#include "Render\FundamentalRenderingResources.h"
#include "AccelerationStructure\TopLevelAccelerationStructure.h"
#include "AccelerationStructure\BottomLevelAccelerationStructure.h"
#include "Scene\Scene.h"
#include "Camera\Camera.h"
#include "RootSignature\GlobalRootSignature.h"
#include "RootSignature\LocalRootSignature.h"

namespace library
{
	class Renderer
	{
	public:
		Renderer();
		Renderer(const Renderer& other) = delete;
		Renderer(Renderer&& other) = delete;
		Renderer& operator=(const Renderer& other) = delete;
		Renderer& operator=(Renderer&& other) = delete;
		~Renderer() = default;

        HRESULT Initialize(_In_ HWND hWnd);
        void HandleInput(_In_ const DirectionsInput& directions, _In_ const MouseRelativeMovement& mouseRelativeMovement, _In_ FLOAT deltaTime);
        void SetMainScene(_In_ std::shared_ptr<Scene>& pScene);
        void Render();
        void Update(_In_ FLOAT deltaTime);
	private:
        FundamentalRenderingResources m_renderingResources;

        std::shared_ptr<Scene> m_scene;
        std::unique_ptr<Camera> m_camera;

        // DXR파이프라인 관련
        ComPtr<ID3D12Device5> m_dxrDevice;
        ComPtr<ID3D12GraphicsCommandList4> m_dxrCommandList;
        ComPtr<ID3D12StateObject> m_dxrStateObject;

        //ray tracing전용 root signature
        GlobalRootSignature m_globalRootSignature;
        LocalRootSignature m_localRootSignature;
        
        //ray tracing BLAS,TLAS
        TopLevelAccelerationStructure m_topLevelAccelerationStructure;
        std::vector<std::unique_ptr<BottomLevelAccelerationStructure>> m_bottomLevelAccelerationStructures;

        //Ray tracing Shader에서 접근하는 UAV에 대한 descriptor heap
        ComPtr<ID3D12DescriptorHeap> m_descriptorHeap;
        UINT m_descriptorsAllocated;
        UINT m_uavHeapDescriptorSize;

        //Per Cube Constant Buffer
        CubeConstantBuffer m_cubeCB;

        //ray tracing Shader Table자원
        ComPtr<ID3D12Resource> m_missShaderTable;
        ComPtr<ID3D12Resource> m_hitGroupShaderTable;
        ComPtr<ID3D12Resource> m_rayGenShaderTable;

        // Raytracing  결과 UAV자원
        ComPtr<ID3D12Resource> m_raytracingOutput;
        D3D12_GPU_DESCRIPTOR_HANDLE m_raytracingOutputResourceUAVGpuDescriptor;
        UINT m_raytracingOutputResourceUAVDescriptorHeapIndex;


        D3D12_CPU_DESCRIPTOR_HANDLE m_indexBufferCpuDescriptorHandle;
        D3D12_GPU_DESCRIPTOR_HANDLE m_indexBufferGpuDescriptorHandle;
        D3D12_CPU_DESCRIPTOR_HANDLE m_vertexBufferCpuDescriptorHandle;
        D3D12_GPU_DESCRIPTOR_HANDLE m_vertexBufferGpuDescriptorHandle;
        
    private:
        HRESULT populateCommandList();

        //이하 함수는 ray tacing 관련함수
        
        HRESULT createRaytracingInterfaces();
        HRESULT createRaytracingRootSignature();
        HRESULT createRaytracingPipelineStateObject();
        HRESULT createUAVDescriptorHeap();
        HRESULT createAccelerationStructure();
        HRESULT createShaderTable();
        HRESULT createRaytacingOutputResource(_In_ HWND hWnd);
        UINT createBufferSRV(_In_ ID3D12Resource* buffer,_Out_ D3D12_CPU_DESCRIPTOR_HANDLE* cpuDescriptorHandle, _Out_ D3D12_GPU_DESCRIPTOR_HANDLE* gpuDescriptorHandle, _In_ UINT numElements, _In_ UINT elementSize);
	};
}
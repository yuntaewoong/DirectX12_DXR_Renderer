#pragma once

#include "Common/Common.h"
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
        void Render(_In_ FLOAT deltaTime);
        void SetRenderMode(_In_ ERenderMode renderMode);
	private:
        ERenderMode m_renderMode;
        static const UINT FRAME_COUNT = 2;
        struct Vertex
        {
            XMFLOAT3 position;
            XMFLOAT4 color;
        };
        using Index = UINT16;
        ComPtr<IDXGIFactory4> m_dxgiFactory;
        ComPtr<IDXGISwapChain3> m_swapChain;
        ComPtr<ID3D12Device> m_device;
        ComPtr<ID3D12Resource> m_renderTargets[FRAME_COUNT];
        ComPtr<ID3D12CommandAllocator> m_commandAllocator;
        ComPtr<ID3D12CommandQueue> m_commandQueue;
        ComPtr<ID3D12RootSignature> m_rasterRootSignature;
        ComPtr<ID3D12DescriptorHeap> m_rtvHeap;
        ComPtr<ID3D12PipelineState> m_pipelineState;
        ComPtr<ID3D12GraphicsCommandList> m_commandList;

        ComPtr<ID3D12Resource> m_vertexBuffer;
        D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;
        ComPtr<ID3D12Resource> m_indexBuffer;
        D3D12_INDEX_BUFFER_VIEW m_indexBufferView;
        // DXR파이프라인 관련
        ComPtr<ID3D12Device5> m_dxrDevice;
        ComPtr<ID3D12GraphicsCommandList4> m_dxrCommandList;
        ComPtr<ID3D12StateObject> m_dxrStateObject;

        //ray tracing전용 root signature
        ComPtr<ID3D12RootSignature> m_raytracingGlobalRootSignature;
        ComPtr<ID3D12RootSignature> m_raytracingLocalRootSignature;
        
        //ray tracing BLAS,TLAS
        ComPtr<ID3D12Resource> m_bottomLevelAccelerationStructure;
        ComPtr<ID3D12Resource> m_topLevelAccelerationStructure;
        
        //Ray tracing Shader에서 접근하는 UAV에 대한 descriptor heap
        ComPtr<ID3D12DescriptorHeap> m_uavHeap;
        UINT m_uavHeapDescriptorSize;

        //RayGeneration Shader Constant Buffer 구조체
        RayGenConstantBuffer m_rayGenCB;

        UINT m_rtvDescriptorSize;
        UINT m_frameIndex;
        HANDLE m_fenceEvent;
        ComPtr<ID3D12Fence> m_fence;
        UINT64 m_fenceValue;


    private:
        HRESULT initializePipeLine(_In_ HWND hWnd);
        HRESULT initializeAssets();
        HRESULT getHardwareAdapter(
            _In_ IDXGIFactory1* pFactory,
            _Outptr_result_maybenull_ IDXGIAdapter1** ppAdapter,
            bool requestHighPerformanceAdapter = false
        );
        HRESULT populateCommandList();
        HRESULT waitForPreviousFrame();
        void getWindowWidthHeight(_In_ HWND hWnd, _Out_ PUINT pWidth, _Out_ PUINT pHeight);
        

        HRESULT createDevice();
        HRESULT createCommandQueue();
        HRESULT createSwapChain(_In_ HWND hWnd);
        HRESULT createRenderTargetView();
        HRESULT createCommandAllocator();

        HRESULT createRasterRootSignature();
        HRESULT createPipelineState();
        HRESULT createVertexBuffer();
        HRESULT createIndexBuffer();

        //이하 함수는 ray tacing 관련함수
        BOOL isDeviceSupportRayTracing(IDXGIAdapter1* adapter) const;
        HRESULT createRaytracingInterfaces();
        HRESULT createRaytracingRootSignature();
        HRESULT createRaytracingPipelineStateObject();
        HRESULT createUAVDescriptorHeap();
        HRESULT createAccelerationStructure();
	};
}
#include "pch.h"
#include "Render\Mesh.h"

namespace library
{
    Mesh::Mesh(
        _In_ XMVECTOR location,
        _In_ XMVECTOR rotation,
        _In_ XMVECTOR scale,
        _In_ XMFLOAT4 color
    ) :
		m_vertexBuffer(nullptr),
		m_indexBuffer(nullptr),
        m_world(XMMatrixIdentity()),
        m_color(color),
        m_material()
	{
        m_world = m_world *
            XMMatrixRotationRollPitchYawFromVector(rotation) *
            XMMatrixScalingFromVector(scale) *
            XMMatrixTranslationFromVector(location);
    }
    ComPtr<ID3D12Resource>& Mesh::GetVertexBuffer()
    {
        return m_vertexBuffer;
    }
    ComPtr<ID3D12Resource>& Mesh::GetIndexBuffer()
    {
        return m_indexBuffer;
    }
    XMMATRIX Mesh::GetWorldMatrix() const
    {
        return m_world;
    }
    XMFLOAT4 Mesh::GetColor() const
    {
        return m_color;
    }
    const std::shared_ptr<Material>& Mesh::GetMaterial() const
    {
        return m_material;
    }
    void Mesh::SetMaterial(_In_ const std::shared_ptr<Material>& pMaterial)
    {
        m_material = pMaterial;
    }
    HRESULT Mesh::initialize(_In_ const ComPtr<ID3D12Device>& pDevice)
	{
		HRESULT hr = S_OK;
        hr = createVertexBuffer(pDevice);
        if (FAILED(hr))
        {
            return hr;
        }
        hr = createIndexBuffer(pDevice);
        if (FAILED(hr))
        {
            return hr;
        }
		return hr;
	}
	HRESULT Mesh::createVertexBuffer(_In_ const ComPtr<ID3D12Device>& pDevice)
	{
        HRESULT hr = S_OK;
        const Vertex* triangleVertices = GetVertices();
        const UINT vertexBufferSize = sizeof(Vertex) * GetNumVertices();

        //���� heap type�� upload�� �� ���·� vertex buffer�� gpu�޸𸮿� �����ϴµ�, �̴� ���� ���� ���
        //GPU�� �����Ҷ����� �������� �Ͼ�ٰ� ���������� �ּ��� ����
        CD3DX12_HEAP_PROPERTIES heapProperties(D3D12_HEAP_TYPE_UPLOAD);
        D3D12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize);
        hr = pDevice->CreateCommittedResource(//�� ũ�� == ������ ũ��� ����, �ڿ� �Ҵ�
            &heapProperties,                    //�� Ÿ��
            D3D12_HEAP_FLAG_NONE,
            &resourceDesc,                      //�ڿ� ũ������
            D3D12_RESOURCE_STATE_GENERIC_READ,  //���� ����
            nullptr,
            IID_PPV_ARGS(&m_vertexBuffer)       //CPU�޸𸮿��� ���ٰ����� ComPtr��ü
        );

        UINT8* pVertexDataBegin = nullptr;    // gpu�޸𸮿� mapping �� cpu�޸�(virtual memory�� �ü�� ���� �����ϴµ�)
        CD3DX12_RANGE readRange(0, 0);        // 0~0���� ������ CPU�޸𸮷� gpu������ �б� ���� ����, nullptr�Է��ϸ� gpu������ �б� ����
        hr = m_vertexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&pVertexDataBegin));//����
        if (FAILED(hr))
        {
            return hr;
        }
        memcpy(pVertexDataBegin, triangleVertices, vertexBufferSize);//gpu �޸� ����
        m_vertexBuffer->Unmap(0, nullptr);//���� ����
        return hr;
	}
	HRESULT Mesh::createIndexBuffer(_In_ const ComPtr<ID3D12Device>& pDevice)
	{
        HRESULT hr = S_OK;
        const Index* indices = GetIndices();
        const UINT indexBufferSize = sizeof(Index) * GetNumIndices();

        CD3DX12_HEAP_PROPERTIES heapProperties(D3D12_HEAP_TYPE_UPLOAD);//heap type�� upload
        D3D12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(indexBufferSize);
        hr = pDevice->CreateCommittedResource(//�� ũ�� == ������ ũ��� ����, �ڿ� �Ҵ�
            &heapProperties,                    //�� Ÿ��
            D3D12_HEAP_FLAG_NONE,
            &resourceDesc,                      //�ڿ� ũ������
            D3D12_RESOURCE_STATE_GENERIC_READ,  //���� ����
            nullptr,
            IID_PPV_ARGS(&m_indexBuffer)       //CPU�޸𸮿��� ���ٰ����� ComPtr��ü
        );
        if (FAILED(hr))
        {
            return hr;
        }
        UINT8* pIndexDataBegin = nullptr;    // gpu�޸𸮿� mapping �� cpu�޸�(virtual memory�� �ü�� ���� �����ϴµ�)
        CD3DX12_RANGE readRange(0, 0);        // 0~0���� ������ CPU�޸𸮷� gpu������ �б� ���� ����, nullptr�Է��ϸ� gpu������ �б� ����
        hr = m_indexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&pIndexDataBegin));//����
        if (FAILED(hr))
        {
            return hr;
        }
        memcpy(pIndexDataBegin, indices, indexBufferSize);//gpu �޸� ����
        m_indexBuffer->Unmap(0, nullptr);//���� ����
        return hr;
	}
}
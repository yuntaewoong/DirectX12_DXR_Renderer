#include "RootSignature\LocalRootSignature.h"

namespace library
{
    LocalRootSignature::LocalRootSignature() :
        m_rootParameter()
    {}
    HRESULT LocalRootSignature::Initialize(_In_ ID3D12Device* pDevice)
    {
        m_rootParameter[static_cast<UINT>(ELocalRootSignatureSlot::CubeConstantSlot)].InitAsConstants(4u, 1u);//1번 레지스터에 32비트(4바이트) 값 4개를 쓰겠다
        m_rootParameter[static_cast<UINT>(ELocalRootSignatureSlot::VertexBufferSlot)].InitAsShaderResourceView(2);//2번 레지스터는 VB
        m_rootParameter[static_cast<UINT>(ELocalRootSignatureSlot::IndexBufferSlot)].InitAsShaderResourceView(3);//3번 레지스터는 IB

        CD3DX12_ROOT_SIGNATURE_DESC localRootSignatureDesc(ARRAYSIZE(m_rootParameter), m_rootParameter);
        localRootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_LOCAL_ROOT_SIGNATURE;
        return RootSignature::initialize(pDevice, localRootSignatureDesc);
    }
}
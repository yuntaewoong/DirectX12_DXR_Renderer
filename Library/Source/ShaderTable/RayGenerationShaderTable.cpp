#include "pch.h"
#include "ShaderTable\RayGenerationShaderTable.h"
namespace library
{
    RayGenerationShaderTable::RayGenerationShaderTable() :
        ShaderTable::ShaderTable()
    {}

    HRESULT RayGenerationShaderTable::Initialize(_In_ const ComPtr<ID3D12Device>& pDevice, _In_ const ComPtr<ID3D12StateObject>& pStateObject)
    {
        HRESULT hr = S_OK;
        UINT shaderIdentifierSize = D3D12_SHADER_IDENTIFIER_SIZE_IN_BYTES;
        UINT numShaderRecords = 1;
        UINT shaderRecordSize = shaderIdentifierSize;
        hr = ShaderTable::initialize(pDevice,numShaderRecords, shaderRecordSize);
        if (FAILED(hr))
        {
            return hr;
        }
        ComPtr<ID3D12StateObjectProperties> stateObjectProperties(nullptr);
        pStateObject.As(&stateObjectProperties);
        void* rayGenShaderIdentifier = stateObjectProperties->GetShaderIdentifier(RAY_GEN_SHADER_NAME);
        Push_back(ShaderRecord(rayGenShaderIdentifier, shaderIdentifierSize));
        return hr;
    }
}
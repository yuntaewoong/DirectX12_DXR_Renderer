#pragma once
#include "Render\Renderable.h"

class BasePlane : public library::Renderable
{
public:
	BasePlane(
		_In_ XMVECTOR location,
		_In_ XMVECTOR rotation,
		_In_ XMVECTOR scale,
		_In_ XMFLOAT4 color
	);
	BasePlane(const BasePlane& other) = delete;
	BasePlane(BasePlane&& other) = delete;
	BasePlane& operator=(const BasePlane& other) = delete;
	BasePlane& operator=(BasePlane&& other) = delete;
	virtual ~BasePlane() = default;

	HRESULT Initialize(_In_ const ComPtr<ID3D12Device>& pDevice) override;
	void Update(_In_ FLOAT deltaTime) override;
	virtual UINT GetNumVertices() const override;
	virtual UINT GetNumIndices() const override;
protected:
	const virtual Vertex* GetVertices() const override;
	const virtual Index* GetIndices() const override;
private:
	static constexpr const Vertex VERTICES[] =
	{
		{.position = XMFLOAT3(-1.0f, 0.f, -1.0f), .uv = XMFLOAT2(1.0f, 0.0f), .normal = XMFLOAT3(0.0f, 1.0f, 0.0f) },
		{.position = XMFLOAT3(1.0f, 0.f, -1.0f), .uv = XMFLOAT2(0.0f, 0.0f), .normal = XMFLOAT3(0.0f, 1.0f, 0.0f) },
		{.position = XMFLOAT3(1.0f, 0.f,  1.0f), .uv = XMFLOAT2(0.0f, 1.0f), .normal = XMFLOAT3(0.0f, 1.0f, 0.0f) },
		{.position = XMFLOAT3(-1.0f, 0.f,  1.0f), .uv = XMFLOAT2(1.0f, 1.0f), .normal = XMFLOAT3(0.0f, 1.0f, 0.0f) }
	};
	static constexpr const Index INDICES[] =
	{
		{3}, {1}, {0},
		{2},{1},{3},
	};
};
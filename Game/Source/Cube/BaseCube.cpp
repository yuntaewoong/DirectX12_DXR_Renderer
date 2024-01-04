#include "pch_game.h"
#include "Cube\BaseCube.h"

BaseCube::BaseCube(
	_In_ XMVECTOR location,
	_In_ XMVECTOR rotation,
	_In_ XMVECTOR scale,
	_In_ XMFLOAT4 color
) :
	Mesh::Mesh(location,rotation,scale,color)
{
	for (int i = 0; i < ARRAYSIZE(VERTICES); i++)
		AddVertex(VERTICES[i]);
	for (int i = 0; i < ARRAYSIZE(INDICES); i++)
		AddIndex(INDICES[i]);
}
void BaseCube::Update(_In_ FLOAT deltaTime)
{

}
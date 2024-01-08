#include "pch_game.h"
#include "Plane\BasePlane.h"

BasePlane::BasePlane(
	_In_ XMVECTOR location,
	_In_ XMVECTOR rotation,
	_In_ XMVECTOR scale
) :
	Mesh::Mesh(location, rotation, scale)
{
	for (int i = 0; i < ARRAYSIZE(VERTICES); i++)
		AddVertex(VERTICES[i]);
	for (int i = 0; i < ARRAYSIZE(INDICES); i++)
		AddIndex(INDICES[i]);
}
void BasePlane::Update(_In_ FLOAT deltaTime)
{

}
#pragma once
#include "../../DirectX/Direct3D.h"

// メッシュの頂点情報
struct MeshVertex
{
	XMFLOAT3 position;
	XMFLOAT3 normal;
	XMFLOAT3 uv;
	XMFLOAT3 tangent;
};
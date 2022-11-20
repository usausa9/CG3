#pragma once
#include <d3dcompiler.h>
#include <DirectXTex.h>

#pragma comment(lib, "d3dcompiler.lib")

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <forward_list>

using namespace DirectX;

// XMFLOAT3“¯m‚Ì‰ÁZˆ—
const DirectX::XMFLOAT3 operator+(const DirectX::XMFLOAT3& Ihs, const DirectX::XMFLOAT3& rhs)
{
	XMFLOAT3 result;
	result.x = Ihs.x + rhs.x;
	result.y = Ihs.y + rhs.y;
	result.z = Ihs.z + rhs.z;
	return result;
}
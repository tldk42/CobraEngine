#include "Graphics.h"

namespace Cobra
{
	Graphics::Graphics(): mDirect3D(nullptr)
	{
	}

	bool Graphics::Initialize(float Width, float Height, HWND Hwnd)
	{
#pragma region D3D

		mDirect3D = new Direct3D(true);
		if (!mDirect3D)
		{
			return false;
		}

		if (!mDirect3D->Initialize(Hwnd, Width, Height, false, 1000.f, 0.1f))
		{
			MessageBox(Hwnd, L"Could not Initialize Direct3D", L"Error", MB_OK);
			return false;
		}

#pragma endregion D3D

		return true;
	}

	void Graphics::Clear()
	{
		if (mDirect3D)
		{
			mDirect3D->Clear();
			mDirect3D = nullptr;
		}
	}

	bool Graphics::Render()
	{
		DirectX::XMMATRIX viewMatrix, projectionMatrix, worldMatrix{};
		
		mDirect3D->BeginScene(0.401f, 0.401f, 0.401f, 1.0f);


		mDirect3D->GetWorldMatrix(worldMatrix);
		mDirect3D->GetProjectionMatrix(projectionMatrix);

		mDirect3D->EndScene();

		return true;
	}

	void Graphics::RenderScene()
	{
	}

	void Graphics::RenderInfo()
	{
	}
}

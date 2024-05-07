#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

namespace Cobra
{
	using namespace DirectX;

	class Direct3D
	{
	public:
		Direct3D() = delete;
		Direct3D(bool InbVsync);
		~Direct3D() = default;

	public:
		bool Initialize(HWND  hWnd, const float winWidth, const float winHeight, bool fullScreen, float screenDepth,
		                float screenNear);
		void Clear();

		void BeginScene(float R, float G, float B, float A);
		void EndScene();

		HRESULT ResizeSwapChain(UINT Width, UINT Height);

	public:
		inline ID3D11Device*           GetDevice() const { return mD3D; }
		inline ID3D11DeviceContext*    GetDeviceContext() const { return mD3DDC; }
		inline IDXGISwapChain*         GetSwapChain() const { return mSwapChain; }
		inline ID3D11RenderTargetView* GetRTV() const { return mRenderTargetView; }
		inline const char*             GetGraphicCardInfo() const { return mVideoCardDescription; }

		inline void GetProjectionMatrix(XMMATRIX& mat) const
		{
			mat = mProjectionMatrix;
		}

		inline void GetWorldMatrix(XMMATRIX& mat) const
		{
			mat = mWorldMatrix;
		}

		inline void GetOrthoMatrix(XMMATRIX& mat) const
		{
			mat = mOrthoMatrix;
		}

	private:
		bool bVsync;
		int  mVideoCardMemory;
		char mVideoCardDescription[128];

		ID3D11Device*            mD3D;
		ID3D11DeviceContext*     mD3DDC;
		IDXGISwapChain*          mSwapChain;
		ID3D11RenderTargetView*  mRenderTargetView;
		ID3D11Texture2D*         mDepthStencilBuffer;
		ID3D11DepthStencilState* mDepthStencilState;
		ID3D11DepthStencilView*  mDepthStencilView;
		ID3D11RasterizerState*   mRasterState;

		DXGI_SWAP_CHAIN_DESC          mSwapChainDesc;
		D3D11_TEXTURE2D_DESC          mDepthBufferDesc;
		D3D11_DEPTH_STENCIL_DESC      mDepthStencilDesc;
		D3D11_DEPTH_STENCIL_VIEW_DESC mDepthStencilViewDesc;

		XMMATRIX          mProjectionMatrix;
		XMMATRIX          mWorldMatrix;
		XMMATRIX          mOrthoMatrix;
		D3D_FEATURE_LEVEL mFeatureLevel;

		D3D11_VIEWPORT mViewport; // 렌더링 될 영역지정

		float mFOV;
		float mScreenAspect;
	};
}

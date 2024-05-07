#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include "../App/Window/Window.h"

namespace Cobra
{
	namespace Directx
	{
		template <typename T>
		inline void ReleaseCOM(T* Entity)
		{
			if (Entity)
			{
				Entity->Release();
				Entity = nullptr;
			}
		}

		class Context
		{
		public:
			Context(const WindowData& WindowData, void* DeviceContext);

		public:
			static void Create(const WindowData& WindowData, void* DeviceContext);

			void Present3D();

			void Present();

			void SetSolid();

		public:
			inline static Context* GetContext() { return s_Context; }
			inline static Context* Get() { return s_Context; }

			inline static ID3D11Device*           GetDevice() { return GetContext()->mD3D; }
			inline static ID3D11DeviceContext*    GetDeviceContext() { return GetContext()->mD3DDC; }
			inline static IDXGISwapChain*         GetSwapChain() { return GetContext()->mSwapChain; }
			inline static ID3D11RenderTargetView* GetRTV() { return GetContext()->mRenderTargetView; }
			inline static ID3D11DepthStencilView* GetDepthStencilView() { return GetContext()->mDepthStencilView; }

			inline static const char* GetGraphicCardInfo() { return GetContext()->mVideoCardDescription; }

			inline static const WindowData& GetWindowData() { return GetContext()->mWindowData; }

			inline static void Bind() { return GetContext()->BindInternal(); }

		private:
			bool Initialize3D(HWND Hwnd);

			bool Resize();

			void BindInternal();

		private:
			/** DX Context ����ƽ ��ü */
			static Context* s_Context;

		private:
			/** ����̽� �������̽� ������ (���ҽ� ����) */
			ID3D11Device* mD3D;
			/** ����̽� ���ؽ�Ʈ ������ (���������� ����) */
			ID3D11DeviceContext* mD3DDC;
			/** ����ü�� �������̽� ������ (���÷��� ����) */
			IDXGISwapChain* mSwapChain;
			/** ȭ�鿡 �������� ���� ��ü (RTV) */
			ID3D11RenderTargetView* mRenderTargetView;
			/** ����/���ٽ� ���� ��� �� ���� ��ü */
			ID3D11DepthStencilView* mDepthStencilView;
			/** 2D �̹��� ���� ��ü �������̽� */
			ID3D11Texture2D* mDepthStencilBuffer;
			/** ������ ����Ʈ */
			D3D11_VIEWPORT mViewport;

			/** DX��� ���� ���� */
			D3D_FEATURE_LEVEL mFeatureLevel;

			/** ����ī�� �޸� �뷮 */
			int mVideoCardMemory;
			/** ����ī�� �� ���� */
			char mVideoCardDescription[128];

			/** ������ ������Ƽ */
			WindowData mWindowData;
		};
	}
}

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
			/** DX Context 스태틱 개체 */
			static Context* s_Context;

		private:
			/** 디바이스 인터페이스 포인터 (리소스 생성) */
			ID3D11Device* mD3D;
			/** 디바이스 컨텍스트 포인터 (파이프라인 설정) */
			ID3D11DeviceContext* mD3DDC;
			/** 스왑체인 인터페이스 포인터 (디스플레이 제어) */
			IDXGISwapChain* mSwapChain;
			/** 화면에 보여지는 버퍼 개체 (RTV) */
			ID3D11RenderTargetView* mRenderTargetView;
			/** 깊이/스텐실 정보 기반 뷰 관리 개체 */
			ID3D11DepthStencilView* mDepthStencilView;
			/** 2D 이미지 관리 개체 인터페이스 */
			ID3D11Texture2D* mDepthStencilBuffer;
			/** 렌더링 뷰포트 */
			D3D11_VIEWPORT mViewport;

			/** DX기능 수준 레벨 */
			D3D_FEATURE_LEVEL mFeatureLevel;

			/** 비디오카드 메모리 용량 */
			int mVideoCardMemory;
			/** 비디오카드 상세 정보 */
			char mVideoCardDescription[128];

			/** 윈도우 프로퍼티 */
			WindowData mWindowData;
		};
	}
}

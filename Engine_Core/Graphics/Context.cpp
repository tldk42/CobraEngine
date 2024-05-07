#include "Context.h"

namespace Cobra
{
	namespace Directx
	{
		Context* Context::s_Context = nullptr;

		Context::Context(const WindowData& WindowData, void* DeviceContext)
			: mD3D(nullptr),
			  mD3DDC(nullptr),
			  mSwapChain(nullptr),
			  mRenderTargetView(nullptr),
			  mDepthStencilView(nullptr),
			  mDepthStencilBuffer(nullptr),
			  mViewport(),
			  mFeatureLevel(),
			  mVideoCardMemory(0),
			  mVideoCardDescription{},
			  mWindowData(WindowData)
		{
			Initialize3D((HWND)DeviceContext);
		}

		void Context::Create(const WindowData& WindowData, void* DeviceContext)
		{
			s_Context = new Context(WindowData, DeviceContext);
		}

		void Context::Present3D()
		{
		}

		void Context::Present()
		{
		}

		void Context::SetSolid()
		{
		}

		bool Context::Initialize3D(HWND Hwnd)
		{
#pragma region swapChain Description

			// SwapChain Info 구조체 & 초기화
			DXGI_SWAP_CHAIN_DESC swapChainDesc;
			ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

			swapChainDesc.BufferCount                        = 1;
			swapChainDesc.BufferDesc.Width                   = mWindowData.Width;               // Buffer Width
			swapChainDesc.BufferDesc.Height                  = mWindowData.Height;              // Buffer Height
			swapChainDesc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;      // 색상 출력 형식
			swapChainDesc.BufferDesc.RefreshRate.Numerator   = 60;                              // FPS 분자
			swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;                               // FPS 분모
			swapChainDesc.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 버퍼 (렌더링 버퍼)
			swapChainDesc.OutputWindow                       = Hwnd;                            // 출력될 윈도우 핸들
			swapChainDesc.SampleDesc.Count                   = 1;                               // 멀티 샘플링 개수
			swapChainDesc.SampleDesc.Quality                 = 0;                               // 멀티 샘플링 품질
			swapChainDesc.Windowed                           = !(mWindowData.bFullScreen);      // 창 전체 화면 모드
			swapChainDesc.SwapEffect                         = DXGI_SWAP_EFFECT_DISCARD;
			swapChainDesc.Flags                              = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

#pragma endregion swapChain Description

#pragma region Direct3D Device, DeviceContext 초기화

			mFeatureLevel = D3D_FEATURE_LEVEL_11_0;

			if (FAILED(D3D11CreateDeviceAndSwapChain(
				NULL,                               // pAdapter (모니터) : null이면 주 모니터 사용
				D3D_DRIVER_TYPE_HARDWARE,           // 하드웨어 가속 사용
				NULL,                               // 소프트웨어로 구동? (하드웨어 사용시 NULL)
				D3D11_CREATE_DEVICE_SINGLETHREADED, // 디버그 계층 활성화
				&mFeatureLevel,                     // DX 기능 수준
				1,                                  // 배열 원소
				D3D11_SDK_VERSION,                  // DX SDK Version
				&swapChainDesc,                     // SwapChain 구조체 정보
				&mSwapChain,
				&mD3D, // 생성한 장치
				NULL,
				&mD3DDC // 생성된 장치 컨텍스트
			)))
			{
				return false;
			}

#pragma endregion Direct3D Device, DeviceContext 초기화
		}

		bool Context::Resize()
		{
			ReleaseCOM(mRenderTargetView);
			ReleaseCOM(mDepthStencilView);
			ReleaseCOM(mDepthStencilBuffer);

			if (FAILED(
				mSwapChain->ResizeBuffers(1, mWindowData.Width, mWindowData.Height, DXGI_FORMAT_R8G8B8A8_UNORM, 0)))
			{
				return false;
			}

			ID3D11Texture2D* backBufferPtr;

			if (FAILED(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&backBufferPtr))))
			{
				return false;
			}

			if (FAILED(mD3D->CreateRenderTargetView(backBufferPtr, NULL, &mRenderTargetView)))
			{
				return false;
			}

			backBufferPtr->Release();

			// 텍스쳐 정보 구조체 (스텐실)
			D3D11_TEXTURE2D_DESC depthStencilDesc;
			{
				depthStencilDesc.Width     = mWindowData.Width; // 생성할 텍스쳐의 너비 길이
				depthStencilDesc.Height    = mWindowData.Height; // 생성할 텍스쳐의 높이 길이
				depthStencilDesc.MipLevels = 1; // 최대 밉맵 레벨을 지정 (밉맵: 한 장의 그림에 여러 스케일 장면을 포함한 텍스쳐)
				depthStencilDesc.ArraySize = 1; // 텍스쳐 배열의 텍스쳐 갯수
				depthStencilDesc.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT; // 깊이-depth로 24비트, 스텐실 값으로 8바이트를 사용하는 형식

				depthStencilDesc.SampleDesc.Count   = 1; // 멀티샘플링 개수
				depthStencilDesc.SampleDesc.Quality = 0; // 멀티샘플링 품질

				// 텍스쳐의 읽기/쓰기 지정
				depthStencilDesc.Usage = D3D11_USAGE_DEFAULT; // 기본 읽기 쓰기로 사용됨을 명시

				// 렌더링(렌더 파이프)에서 바인딩을 지정하는 플래그
				depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL; // 깊이/스텐실 용도로 사용됨 의미

				// CPU의 접근을 지정하는 플래그
				depthStencilDesc.CPUAccessFlags = 0; // 0은 CPU가 읽기/쓰기를 할 수 없을을 의미

				// 기타 속정 지정 플래그
				depthStencilDesc.MiscFlags = 0; // 0은 사용하지 않음을 의미
			}

			if (FAILED(mD3D->CreateTexture2D(&depthStencilDesc, nullptr, &mDepthStencilBuffer)))
			{
				return false;
			}


		}

		void Context::BindInternal()
		{
		}
	}
}

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

			// SwapChain Info ����ü & �ʱ�ȭ
			DXGI_SWAP_CHAIN_DESC swapChainDesc;
			ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

			swapChainDesc.BufferCount                        = 1;
			swapChainDesc.BufferDesc.Width                   = mWindowData.Width;               // Buffer Width
			swapChainDesc.BufferDesc.Height                  = mWindowData.Height;              // Buffer Height
			swapChainDesc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;      // ���� ��� ����
			swapChainDesc.BufferDesc.RefreshRate.Numerator   = 60;                              // FPS ����
			swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;                               // FPS �и�
			swapChainDesc.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT; // ���� (������ ����)
			swapChainDesc.OutputWindow                       = Hwnd;                            // ��µ� ������ �ڵ�
			swapChainDesc.SampleDesc.Count                   = 1;                               // ��Ƽ ���ø� ����
			swapChainDesc.SampleDesc.Quality                 = 0;                               // ��Ƽ ���ø� ǰ��
			swapChainDesc.Windowed                           = !(mWindowData.bFullScreen);      // â ��ü ȭ�� ���
			swapChainDesc.SwapEffect                         = DXGI_SWAP_EFFECT_DISCARD;
			swapChainDesc.Flags                              = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

#pragma endregion swapChain Description

#pragma region Direct3D Device, DeviceContext �ʱ�ȭ

			mFeatureLevel = D3D_FEATURE_LEVEL_11_0;

			if (FAILED(D3D11CreateDeviceAndSwapChain(
				NULL,                               // pAdapter (�����) : null�̸� �� ����� ���
				D3D_DRIVER_TYPE_HARDWARE,           // �ϵ���� ���� ���
				NULL,                               // ����Ʈ����� ����? (�ϵ���� ���� NULL)
				D3D11_CREATE_DEVICE_SINGLETHREADED, // ����� ���� Ȱ��ȭ
				&mFeatureLevel,                     // DX ��� ����
				1,                                  // �迭 ����
				D3D11_SDK_VERSION,                  // DX SDK Version
				&swapChainDesc,                     // SwapChain ����ü ����
				&mSwapChain,
				&mD3D, // ������ ��ġ
				NULL,
				&mD3DDC // ������ ��ġ ���ؽ�Ʈ
			)))
			{
				return false;
			}

#pragma endregion Direct3D Device, DeviceContext �ʱ�ȭ
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

			// �ؽ��� ���� ����ü (���ٽ�)
			D3D11_TEXTURE2D_DESC depthStencilDesc;
			{
				depthStencilDesc.Width     = mWindowData.Width; // ������ �ؽ����� �ʺ� ����
				depthStencilDesc.Height    = mWindowData.Height; // ������ �ؽ����� ���� ����
				depthStencilDesc.MipLevels = 1; // �ִ� �Ӹ� ������ ���� (�Ӹ�: �� ���� �׸��� ���� ������ ����� ������ �ؽ���)
				depthStencilDesc.ArraySize = 1; // �ؽ��� �迭�� �ؽ��� ����
				depthStencilDesc.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT; // ����-depth�� 24��Ʈ, ���ٽ� ������ 8����Ʈ�� ����ϴ� ����

				depthStencilDesc.SampleDesc.Count   = 1; // ��Ƽ���ø� ����
				depthStencilDesc.SampleDesc.Quality = 0; // ��Ƽ���ø� ǰ��

				// �ؽ����� �б�/���� ����
				depthStencilDesc.Usage = D3D11_USAGE_DEFAULT; // �⺻ �б� ����� ������ ���

				// ������(���� ������)���� ���ε��� �����ϴ� �÷���
				depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL; // ����/���ٽ� �뵵�� ���� �ǹ�

				// CPU�� ������ �����ϴ� �÷���
				depthStencilDesc.CPUAccessFlags = 0; // 0�� CPU�� �б�/���⸦ �� �� ������ �ǹ�

				// ��Ÿ ���� ���� �÷���
				depthStencilDesc.MiscFlags = 0; // 0�� ������� ������ �ǹ�
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

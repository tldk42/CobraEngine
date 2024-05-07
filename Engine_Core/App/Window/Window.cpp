#include "Window.h"

#include "../../EngineHelper.h"
#include "../App/Input/InputManager.h"
#include "../Graphics/Graphics.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"


// https://gcyong.tistory.com/145#:~:text=GetEXEInstance%20/%20GetDLLInstance-,%EC%9C%88%EB%8F%84%EC%9A%B0,-%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%98%EB%B0%8D%EC%9D%84%20%ED%95%98%EB%8B%A4%20%EB%B3%B4%EB%A9%B4
EXTERN_C IMAGE_DOS_HEADER __ImageBase; // 인스턴스 핸들 주소 (모듈의 기본 주소)

namespace Cobra
{
	LRESULT CALLBACK WndProc(HWND HWnd, UINT Message, WPARAM WParam, LPARAM LParam)
	{
		LRESULT result = NULL;

		Window* window = Window::GetWindow(HWnd);

		if (window == nullptr)
			return DefWindowProc(HWnd, Message, WParam, LParam);
		switch (Message)
		{
		case WM_SETFOCUS:
			break;
		case WM_KILLFOCUS:
			break;
		case WM_CLOSE:
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
			break;
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
			break;
		case WM_SIZE:
			ResizeCallback(window, LOWORD(LParam), HIWORD(LParam));
			break;
		default:
			result = DefWindowProc(HWnd, Message, WParam, LParam);
		}

		return result;
	}

	void ResizeCallback(Window* Window, int Width, int Height)
	{
		Window->mWindowData.Width  = Width;
		Window->mWindowData.Height = Height;

		// if (window->mEventCallback)
		// window->mEventCallback(Events::ResizeEvent((unsigned int)width, (unsigned int)height));
	}

	std::map<void*, Window*> Window::s_WindowHandles{};

	Window::Window(LPCWSTR WindowTitle, const WindowData& WindowData)
		: mWindowHandle(nullptr),
		  mWindowTitle(WindowTitle),
		  mWindowData(WindowData),
		  bClosed(false)
	{
		mResolutionWidth  = mWindowData.Width;
		mResolutionHeight = mWindowData.Height;

		if (!Initialize())
		{
			CB_CORE_FATAL("윈도우 생성 실패");
			return;
		}

		// TODO: 나머지 기능들 초기화
	}

	Window::~Window()
	{
	}

	Window* Window::GetWindow(void* WindowHandle)
	{
		if (!WindowHandle)
		{
			return s_WindowHandles.begin()->second;
		}

		return s_WindowHandles[WindowHandle];
	}

	void Window::RegisterWindowClass(void* Handle, Window* Window)
	{
		s_WindowHandles[Handle] = Window;
	}

	bool Window::Initialize()
	{
		mInstanceHandle = reinterpret_cast<HINSTANCE>(&__ImageBase);

		WNDCLASS winClass{};
		winClass.hInstance     = mInstanceHandle;
		winClass.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		winClass.lpfnWndProc   = static_cast<WNDPROC>(WndProc);
		winClass.lpszClassName = L"Cobra Engine";
		winClass.hCursor       = LoadCursor(nullptr, IDC_ARROW);
		winClass.hIcon         = LoadIcon(nullptr, IDI_WINLOGO);

		Logger::Initialize();

		if (SUCCEEDED(RegisterClass(&winClass)))
		{
			RECT  size  = {0, 0, mWindowData.Width, mWindowData.Height};
			DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_BORDER;

			AdjustWindowRect(&size, style, false);
			// TODO: 한글 처리 
			mWindowHandle = CreateWindowEx(
				WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
				winClass.lpszClassName,
				mWindowTitle,
				WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
				GetSystemMetrics(SM_CXSCREEN) / 2 - mWindowData.Width / 2,
				GetSystemMetrics(SM_CYSCREEN) / 2 - mWindowData.Height / 2 - 40,
				// TODO: This requires some... attention
				size.right + (-size.left), size.bottom + (-size.top), // 생성되는 윈도우의 폭과 높이
				nullptr,
				nullptr,
				mInstanceHandle,
				nullptr
			);

			if (mWindowHandle)
			{
				RegisterWindowClass(mWindowHandle, this);

				ShowWindow(mWindowHandle, SW_SHOW);
				SetFocus(mWindowHandle);

				SetTitle(mWindowTitle);

				CB_CORE_INFO("Create Window Success");

				InputManager::Initialize();
				mGraphics = new Graphics;
				if (mGraphics->Initialize(mWindowData.Width, mWindowData.Height, mWindowHandle))
				{
					IMGUI_CHECKVERSION();
					ImGui::CreateContext();
					ImGuiIO& io = ImGui::GetIO();
					(void)io;
					ImGui_ImplDX11_Init(mGraphics->GetDirect3D()->GetDevice(),
					                    mGraphics->GetDirect3D()->GetDeviceContext());
					ImGui::StyleColorsDark();

					return true;
				}
			}
		}

		EngineHelper::ShowErrorMessageBox(nullptr, false);
		return false;
	}

	void Window::Update()
	{
		MSG message;

		while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE) > 0)
		{
			if (message.message == WM_QUIT || InputManager::GetKeyDown(EKeyCode::ESC))
			{
				bClosed = true;
				return;
			}

			TranslateMessage(&message);
			DispatchMessage(&message);

			InputManager::Update();

			if (!mGraphics->Render())
			{
				return;
			}
		}
	}

	void Window::Clear()
	{
	}

	void Window::SetTitle(const LPCWSTR InTitle)
	{
		mWindowTitle = InTitle;
	}

	void Window::SetVsync(const bool bEnable)
	{
		mWindowData.bVsync = bEnable;
	}

	void Window::SetEventCallback(const WindowEventCallback& EventCallback)
	{
		mEventCallback = EventCallback;
	}
}

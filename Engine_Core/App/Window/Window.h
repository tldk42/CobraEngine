#pragma once

#include "../Events/Event.h"
#include "../Common/CommonInclude.h"

namespace Cobra
{
	class Graphics;
}

namespace Cobra
{
	class InputManager;

	struct WindowData
	{
		int  Width;
		int  Height;
		bool bFullScreen;
		bool bVsync;
	};

	using WindowEventCallback = std::function<void (Events::Event& Event)>;

	class Window
	{
	public:
		Window() = delete;
		Window(LPCWSTR WindowTitle, const WindowData& WindowData);
		~Window();

	private:
		static void RegisterWindowClass(void* Handle, Window* Window);

	private:
		bool Initialize();

	public:
		void Update();
		void Clear();

	public:
		static Window* GetWindow(void* WindowHandle = nullptr);

#pragma region Getter
		FORCEINLINE InputManager* GetInputManager() const { return mInputManager; }
		FORCEINLINE HWND          GetHandle() const { return mWindowHandle; }
		FORCEINLINE int           GetWidth() const { return mWindowData.Width; }
		FORCEINLINE int           GetHeight() const { return mWindowData.Height; }
		FORCEINLINE int           GetResolutionWidth() const { return mResolutionWidth; }
		FORCEINLINE int           GetResolutionHeight() const { return mResolutionHeight; }
		FORCEINLINE bool          IsFullScreen() const { return mWindowData.bFullScreen; }
		FORCEINLINE bool          VsyncEnabled() const { return mWindowData.bVsync; }
		FORCEINLINE bool          IsClosed() const { return bClosed; }
#pragma endregion

#pragma region Setter
		void SetTitle(LPCTSTR InTitle);
		void SetVsync(const bool bEnable);
		void SetEventCallback(const WindowEventCallback& EventCallback);
#pragma endregion

	private:
		HINSTANCE  mInstanceHandle;
		HWND       mWindowHandle;
		LPCWSTR    mWindowTitle;
		WindowData mWindowData;
		bool       bClosed;

		WindowEventCallback mEventCallback;

		int mResolutionWidth;
		int mResolutionHeight;

		InputManager* mInputManager;
		Graphics*     mGraphics;

	private:
		static std::map<void*, Window*> s_WindowHandles;

		friend LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
		friend void             ResizeCallback(Window* Window, int Width, int Height);
	};
}

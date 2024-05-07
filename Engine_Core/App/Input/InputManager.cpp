#include "InputManager.h"

#include "../Window/Window.h"

namespace Cobra
{
	std::vector<FKey> InputManager::Keys          = {};
	FVector2D         InputManager::MousePosition = {};

	int ASCII[static_cast<UINT>(EKeyCode::End)] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',
		VK_LEFT, VK_RIGHT, VK_DOWN, VK_UP,
		VK_LBUTTON, VK_MBUTTON, VK_RBUTTON,
		VK_ESCAPE
	};

	void InputManager::Initialize()
	{
		CreateKeys();
	}

	void InputManager::Update()
	{
		UpdateKeys();
	}

	void InputManager::CreateKeys()
	{
		for (size_t i = 0; i < static_cast<UINT>(EKeyCode::End); i++)
		{
			FKey key = {static_cast<EKeyCode>(i), EKeyState::None, false};

			Keys.push_back(key);
		}
	}

	void InputManager::UpdateKeys()
	{
		std::ranges::for_each(Keys, [](FKey& InKey)
		{
			UpdateKey(InKey);
		});
	}

	void InputManager::ClearKeys()
	{
		for (FKey& key : Keys)
		{
			switch (key.KeyState)
			{
			case EKeyState::None:
				break;
			case EKeyState::Down:
			case EKeyState::Pressed:
				key.KeyState = EKeyState::Up;
				break;
			case EKeyState::Up:
				key.KeyState = EKeyState::None;
				break;
			}

			key.bPressed = false;
		}
	}

	void InputManager::UpdateKey(FKey& InKey)
	{
		if (GetFocus())
		{
			IsKeyDown(InKey.KeyCode) ? UpdateKeyDown(InKey) : UpdateKeyUp(InKey);

			GetMousePositionWindow();
		}
		else
		{
			ClearKeys();
		}
	}

	bool InputManager::IsKeyDown(EKeyCode InKey)
	{
		return GetAsyncKeyState(ASCII[static_cast<UINT>(InKey)]) & 0x8000;
	}

	void InputManager::UpdateKeyDown(FKey& InKey)
	{
		InKey.KeyState = InKey.bPressed ? EKeyState::Pressed : EKeyState::Down;

		InKey.bPressed = true;
	}

	void InputManager::UpdateKeyUp(FKey& InKey)
	{
		InKey.KeyState = InKey.bPressed ? EKeyState::Up : EKeyState::None;

		InKey.bPressed = false;
	}

	void InputManager::GetMousePositionWindow()
	{
		POINT mousePos;

		// 마우스 포인터위치 저장
		GetCursorPos(&mousePos);

		// 저장된 포인터 위치를 클라이언트 영역 좌표로 변환
		ScreenToClient(Window::GetWindow(nullptr)->GetHandle(), &mousePos);

		MousePosition.X = mousePos.x;
		MousePosition.Y = mousePos.y;
	}

	void KeyCallback(InputManager* InputManger, int Flags, int Key, unsigned int Message)
	{
	}

	void MouseButtonCallback(InputManager* InputManager, int Button, int X, int Y)
	{
	}
}

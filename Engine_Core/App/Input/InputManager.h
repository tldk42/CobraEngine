#pragma once
#include "../App/Events/Event.h"
#include "../Math/Vector2D.h"

namespace Cobra
{
	enum class EKeyState
	{
		None,
		Down,
		Pressed,
		Up
	};

	enum class EKeyCode
	{
		Q,
		W,
		E,
		R,
		T,
		Y,
		U,
		I,
		O,
		P,
		A,
		S,
		D,
		F,
		G,
		H,
		J,
		K,
		L,
		Z,
		X,
		C,
		V,
		B,
		N,
		M,
		Left,
		Right,
		Down,
		Up,
		LButton,
		MButton,
		RButton,
		ESC,
		End
	};

	struct FKey
	{
		EKeyCode  KeyCode;
		EKeyState KeyState;
		bool      bPressed;
	};

	using WindowEventCallback = std::function<void (Events::Event& Event)>;

	class InputManager
	{
	public:
		InputManager() = delete;

		static void Initialize();
		static void Update();

		FORCEINLINE static bool GetKeyDown(EKeyCode Key)
		{
			return Keys[static_cast<UINT>(Key)].KeyState == EKeyState::Down;
		}

		FORCEINLINE static bool GetKeyUp(EKeyCode Key)
		{
			return Keys[static_cast<UINT>(Key)].KeyState == EKeyState::Up;
		}

		FORCEINLINE static bool GetKey(EKeyCode Key)
		{
			return Keys[static_cast<UINT>(Key)].KeyState == EKeyState::Pressed;
		}

		FORCEINLINE static FVector2D GetMousePosition()
		{
			return MousePosition;
		}

	private:
		static void CreateKeys();
		static void UpdateKeys();
		static void ClearKeys();
		static void UpdateKey(FKey& InKey);
		static bool IsKeyDown(EKeyCode InKey);

		static void UpdateKeyDown(FKey& InKey);
		static void UpdateKeyUp(FKey& InKey);

		static void GetMousePositionWindow();

	private:
		static std::vector<FKey> Keys;
		static FVector2D         MousePosition;

	private:
		friend void KeyCallback(InputManager* InputManger, int Flags, int Key, unsigned int Message);
		friend void MouseButtonCallback(InputManager* InputManager, int Button, int X, int Y);
	};
}

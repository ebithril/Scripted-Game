#pragma once

#pragma comment (lib,"dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "XINPUT9_1_0.lib")

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>
#include "InputEnums.h"
#include "Vector2.h"
#include <XInput.h>

namespace CommonUtilities
{
	typedef CommonUtilities::Vector::Vector2<float> Xbox360ThumbStick;
	typedef float Xbox360Trigger;

	class InputWrapper
	{
	public:
		static InputWrapper* GetInstance();

		void Init(HWND aWindowHandle, HINSTANCE aHInstance, DWORD aKeyboardCooperativeFlags = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE, DWORD aMouseCooperativeFlags = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		void Release();
		void PollInput();


		const bool KeyDown(const eKeyboardKeys aKey) const;
		const bool KeyUp(const eKeyboardKeys aKey) const;
		const bool KeyPress(const eKeyboardKeys aKey) const;

		const bool MouseButtonDown(const eMouseKeys aButton) const;
		const bool MouseButtonUp(const eMouseKeys aButton) const;
		const bool MouseButtonPress(const eMouseKeys aButton) const;

		const bool Xbox360KeyDown(const eXbox360Buttons aButton) const;
		const bool Xbox360KeyUp(const eXbox360Buttons aButton) const;
		const bool Xbox360KeyPress(const eXbox360Buttons aButton) const;

		const Vector::Vector2<float>& GetXbox360LeftStickPosition() const;
		const Vector::Vector2<float>& GetXbox360RightStickPosition() const;

		const float GetXbox360LeftTrigger() const;
		const float GetXbox360RightTrigger() const;

		void RumbleXbox360Controller(float aLeftRumble, float aRightRumble);


		const float GetMouseDeltaX() const;
		const float GetMouseDeltaY() const;
		const float GetMouseWheelDelta() const;

		Vector::Vector2<float> GetSaturatedMouseDelta();

		const float GetCurrentMouseX() const;
		const float GetCurrentMouseY() const;

		void LockCursor(Vector::Vector2<float>& aCursorPosition);
		void UnlockCursor();

		void HideWindowsCursor();
		void ShowWindowsCursor();

		void ToggleXboxController(const bool aState);


	private:
		InputWrapper();
		~InputWrapper();

		static InputWrapper* ourInstance;

		void CaptureXboxThumbs();

		void CapturePreviousState();
		void RestrictCursorToWindow();

		bool myIsInitialized;

		bool myLockCursor;
		Vector::Vector2<float> myCursorLockPosition;

		IDirectInput8* myDInput;

		IDirectInputDevice8* myKeyboard;
		UCHAR myCurrentKeyState[256];
		UCHAR myPrevKeyState[256];

		IDirectInputDevice8* myMouse;
		DIMOUSESTATE2 myCurrentMouseState;
		DIMOUSESTATE2 myPrevMouseState;

		bool myUseXbox360Controller;

		XINPUT_GAMEPAD myCurrentXbox360Controller;
		XINPUT_GAMEPAD myPrevXbox360Controller;

		Xbox360ThumbStick myLeftStick;
		Xbox360ThumbStick myRightStick;
		Xbox360Trigger myLeftTrigger;
		Xbox360Trigger myRightTrigger;

		Vector::Vector2<float> myMousePosition;

		HWND myWindowHandle;

		bool myCursorIsClipped;
	};
}

namespace CU = CommonUtilities;
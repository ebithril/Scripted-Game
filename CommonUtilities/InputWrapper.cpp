#include "stdafx.h"
#include "InputWrapper.h"
#include <WinUser.h>
#include <assert.h>
#include "Macros.h"

#define XBOX_STICK_MAX_MAGNITUDE  (32767)
#define XBOX_STICK_MAX_MAGNITUDESQUARED  (XBOX_STICK_MAX_MAGNITUDE*XBOX_STICK_MAX_MAGNITUDE)


namespace CommonUtilities
{
	InputWrapper* InputWrapper::ourInstance = nullptr;
	
	InputWrapper::InputWrapper()
	{
		myIsInitialized = false;
		myLockCursor = false;
		myCursorLockPosition = { 0.f, 0.f };
		myCursorIsClipped = false;
		myUseXbox360Controller = false;
	}

	InputWrapper* InputWrapper::GetInstance()
	{
		if (ourInstance == nullptr)
		{
			ourInstance = new InputWrapper();
		}

		return ourInstance;
	}

	void InputWrapper::Init(HWND aWindowHandle, HINSTANCE aHInstance, DWORD aKeyboardCooperativeFlags, DWORD aMouseCooperativeFlags)
	{
		HRESULT theStatus = (DirectInput8Create(aHInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, reinterpret_cast<void**>(&myDInput), 0));
		assert(theStatus == DI_OK && "Error InputWrapper:  Failed to initialize DirectInput");

		theStatus = (myDInput->CreateDevice(GUID_SysKeyboard, &myKeyboard, 0));
		assert(theStatus == DI_OK &&  "Error InputWrapper : Failed to create device [Keyboard]");
		theStatus = (myDInput->CreateDevice(GUID_SysMouse, &myMouse, 0));
		assert(theStatus == DI_OK &&  "Error InputWrapper : Failed to create device [Mouse]");


		theStatus = myKeyboard->SetDataFormat(&c_dfDIKeyboard);
		assert(theStatus == DI_OK && "Error InputWrapper: Failed to set data format [Keyboard]");
		theStatus = myMouse->SetDataFormat(&c_dfDIMouse2);
		assert(theStatus == DI_OK && "Error InputWrapper: Failed to set data format [Mouse]");


		theStatus = myKeyboard->SetCooperativeLevel(aWindowHandle, aKeyboardCooperativeFlags);
		assert(theStatus == DI_OK && "Error InputWrapper: Failed to set cooperative level [Keyboard]");
		theStatus = myMouse->SetCooperativeLevel(aWindowHandle, aMouseCooperativeFlags);
		assert(theStatus == DI_OK && "Error InputWrapper: Failed to set cooperative level [Mouse]");

		theStatus = myKeyboard->Acquire();
		assert(theStatus == DI_OK && "Error InputWrapper: Failed to acquire device [Keyboard](INIT)");
		theStatus = myMouse->Acquire();
		assert(theStatus == DI_OK && "Error InputWrapper: Failed to acquire device [Mouse](INIT)");

		myWindowHandle = aWindowHandle;

		myMousePosition.myX = 0;
		myMousePosition.myY = 0;

		myIsInitialized = true;
	}

	InputWrapper::~InputWrapper()
	{

	}

	void InputWrapper::Release()
	{
		myKeyboard->Unacquire();
		myKeyboard->Release();

		myMouse->Unacquire();
		myMouse->Release();

		myDInput->Release();
	}

	void InputWrapper::PollInput()
	{
		CapturePreviousState();

		HRESULT hr = myKeyboard->GetDeviceState(sizeof(myCurrentKeyState), reinterpret_cast<void**>(&myCurrentKeyState));
		if (FAILED(hr))
		{
			ZeroMemory(myCurrentKeyState, sizeof(myCurrentKeyState));

			myKeyboard->Acquire();
		}

		hr = myMouse->GetDeviceState(sizeof(myCurrentMouseState), reinterpret_cast<void**>(&myCurrentMouseState));
		if (FAILED(hr))
		{
			ZeroMemory(&myCurrentMouseState, sizeof(myCurrentMouseState));

			hr = myMouse->Acquire();
		}

		if (myUseXbox360Controller == true)
		{
			//Xbox controls
			DWORD dwResult;
			for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
			{
				XINPUT_STATE state;
				ZeroMemory(&state, sizeof(XINPUT_STATE));

				// Simply get the state of the controller from XInput.
				dwResult = XInputGetState(i, &state);

				if (dwResult == ERROR_SUCCESS)
				{
					// Controller is connected 
					myCurrentXbox360Controller = state.Gamepad;
					CaptureXboxThumbs();

					myLeftTrigger = static_cast<float>(myCurrentXbox360Controller.bLeftTrigger) / 255.f;
					myRightTrigger = static_cast<float>(myCurrentXbox360Controller.bRightTrigger) / 255.f;
				}
				else
				{
					// Controller is not connected 
				}
			}
		}


		myMousePosition.myX += GetMouseDeltaX();
		myMousePosition.myY += GetMouseDeltaY();

		RestrictCursorToWindow();

	}

	void InputWrapper::CaptureXboxThumbs()
	{
		Vector::Vector2<float> vL(static_cast<float>(myCurrentXbox360Controller.sThumbLX), static_cast<float>(myCurrentXbox360Controller.sThumbLY));
		float lMagnitude = CU::Vector::Length(vL);

		Vector::Vector2<float> lsNormal = vL / lMagnitude;

		if (lMagnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			lMagnitude = CU_MIN(lMagnitude, XBOX_STICK_MAX_MAGNITUDE);

			lMagnitude -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

			float normalizedMagnitude = lMagnitude / (XBOX_STICK_MAX_MAGNITUDE - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);

			float lXOut = normalizedMagnitude*lsNormal.x;
			float lYOut = normalizedMagnitude*lsNormal.y;

			myLeftStick.x = CU_RANGE(lXOut, -1.f, 1.f);
			myLeftStick.y = CU_RANGE(lYOut, -1.f, 1.f);
		}
		else
		{
			myLeftStick.x = 0.f;
			myLeftStick.y = 0.f;
		}




		Vector::Vector2<float> vR(static_cast<float>(myCurrentXbox360Controller.sThumbRX), static_cast<float>(myCurrentXbox360Controller.sThumbRY));
		float rMagnitude = CU::Vector::Length(vR);

		Vector::Vector2<float> rsNormal = vR / rMagnitude;

		if (rMagnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			rMagnitude = CU_MIN(rMagnitude, XBOX_STICK_MAX_MAGNITUDE);

			rMagnitude -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

			float normalizedMagnitude = rMagnitude / (XBOX_STICK_MAX_MAGNITUDE - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);

			float rXOut = normalizedMagnitude*rsNormal.x;
			float rYOut = normalizedMagnitude*rsNormal.y;

			myRightStick.x = CU_RANGE(rXOut, -1.f, 1.f);
			myRightStick.y = CU_RANGE(rYOut, -1.f, 1.f);
		}
		else
		{
			myRightStick.x = 0.f;
			myRightStick.y = 0.f;
		}

	}

	void InputWrapper::CapturePreviousState()
	{
		memcpy_s(myPrevKeyState, sizeof(myPrevKeyState), myCurrentKeyState, sizeof(myCurrentKeyState));
		memcpy_s(&myPrevMouseState, sizeof(myPrevMouseState), &myCurrentMouseState, sizeof(myCurrentMouseState));
		memcpy_s(&myPrevXbox360Controller, sizeof(myPrevXbox360Controller), &myCurrentXbox360Controller, sizeof(myCurrentXbox360Controller));
	}

	void InputWrapper::LockCursor(Vector::Vector2<float>& aCursorPosition)
	{
		myCursorLockPosition = aCursorPosition;
		myLockCursor = true;
	}
	void InputWrapper::UnlockCursor()
	{
		myLockCursor = false;
	}

	void InputWrapper::RestrictCursorToWindow()
	{
		RECT theRealRect;
		GetWindowRect(myWindowHandle, &theRealRect);
		RECT theLockRect = theRealRect;
		theLockRect.right -= 100;
		theLockRect.left += 100;
		theLockRect.bottom -= 100;
		theLockRect.top += 100;




		float windowWidth = static_cast<float>(theRealRect.right - theRealRect.left);
		float windowHeight = static_cast<float>(theRealRect.bottom - theRealRect.top);

		myMousePosition.myX = max(myMousePosition.x, -windowWidth / 2);
		myMousePosition.myX = min(myMousePosition.x, windowWidth / 2);

		myMousePosition.myY = max(myMousePosition.y, -windowHeight / 2);
		myMousePosition.myY = min(myMousePosition.y, windowHeight / 2);

		if (GetForegroundWindow() == myWindowHandle && myLockCursor == true)
		{
			if (myCursorIsClipped == false)
			{
				if (ClipCursor(&theLockRect) == TRUE)
				{
					myCursorIsClipped = true;
				}
			}
		}
		else
		{
			if (myCursorIsClipped == true)
			{
				if (ClipCursor(nullptr) == TRUE)
				{
					myCursorIsClipped = false;
				}
			}
		}
	}

	void InputWrapper::HideWindowsCursor()
	{
		ShowCursor(FALSE);
	}
	void InputWrapper::ShowWindowsCursor()
	{
		ShowCursor(TRUE);
	}

	void InputWrapper::ToggleXboxController(const bool aState)
	{
		myUseXbox360Controller = aState;
	}


	const bool InputWrapper::KeyDown(const eKeyboardKeys aKey) const
	{
		return (myCurrentKeyState[static_cast<unsigned char>(aKey)] & 0x80) != 0;
	}

	const bool InputWrapper::KeyUp(const eKeyboardKeys aKey) const
	{
		return ((myCurrentKeyState[static_cast<unsigned char>(aKey)] & 0x80) == 0 && (myPrevKeyState[static_cast<unsigned char>(aKey)] & 0x80) != 0);
	}

	const bool InputWrapper::KeyPress(const eKeyboardKeys aKey) const
	{
		return ((myCurrentKeyState[static_cast<unsigned char>(aKey)] & 0x80) != 0 && (myPrevKeyState[static_cast<unsigned char>(aKey)] & 0x80) == 0);
	}


	const bool InputWrapper::MouseButtonDown(const eMouseKeys aButton) const
	{
		return (myCurrentMouseState.rgbButtons[static_cast<int>(aButton)] & 0x80) != 0;
	}

	const bool InputWrapper::MouseButtonUp(const eMouseKeys aButton) const
	{
		return ((myCurrentMouseState.rgbButtons[static_cast<int>(aButton)] & 0x80) == 0 && (myPrevMouseState.rgbButtons[static_cast<int>(aButton)] & 0x80) != 0);
	}

	const bool InputWrapper::MouseButtonPress(const eMouseKeys aButton) const
	{
		return ((myCurrentMouseState.rgbButtons[static_cast<int>(aButton)] & 0x80) != 0 && (myPrevMouseState.rgbButtons[static_cast<int>(aButton)] & 0x80) == 0);
	}


	const bool InputWrapper::Xbox360KeyDown(const eXbox360Buttons aButton) const
	{
		unsigned short buttonAsShort = static_cast<unsigned short>(aButton);
		unsigned short comparison = (myCurrentXbox360Controller.wButtons & buttonAsShort);
		bool status = (comparison == buttonAsShort);
		return status;
	}

	const bool InputWrapper::Xbox360KeyUp(const eXbox360Buttons aButton) const
	{
		unsigned short buttonAsShort = static_cast<unsigned short>(aButton);
		unsigned short comparison = (myCurrentXbox360Controller.wButtons & buttonAsShort);
		unsigned short prev = (myPrevXbox360Controller.wButtons & buttonAsShort);

		bool status = ((comparison != buttonAsShort) && (prev == buttonAsShort));
		return status;
	}

	const bool InputWrapper::Xbox360KeyPress(const eXbox360Buttons aButton) const
	{
		unsigned short buttonAsShort = static_cast<unsigned short>(aButton);
		unsigned short comparison = (myCurrentXbox360Controller.wButtons & buttonAsShort);
		unsigned short prev = (myPrevXbox360Controller.wButtons & buttonAsShort);

		bool status = ((comparison == buttonAsShort) && (prev != buttonAsShort));
		return status;
	}

	const Vector::Vector2<float>& InputWrapper::GetXbox360LeftStickPosition() const
	{
		return myLeftStick;
	}
	const Vector::Vector2<float>& InputWrapper::GetXbox360RightStickPosition() const
	{
		return myRightStick;
	}

	const float InputWrapper::GetXbox360LeftTrigger() const
	{
		return myLeftTrigger;
	}
	const float InputWrapper::GetXbox360RightTrigger() const
	{
		return myRightTrigger;
	}

	void InputWrapper::RumbleXbox360Controller(float aLeftRumble, float aRightRumble)
	{
		aLeftRumble = CU_RANGE(aLeftRumble, 0.f, 1.f);
		aRightRumble = CU_RANGE(aRightRumble, 0.f, 1.f);
		unsigned short left = static_cast<unsigned short>(aLeftRumble * 65535);
		unsigned short right = static_cast<unsigned short>(aRightRumble * 65535);


		XINPUT_VIBRATION vibration;
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
		vibration.wLeftMotorSpeed = left; // use any value between 0-65535 here
		vibration.wRightMotorSpeed = right; // use any value between 0-65535 here
		XInputSetState(0, &vibration);
	}



	const float InputWrapper::GetMouseDeltaX() const
	{
		return static_cast<float>(myCurrentMouseState.lX);
	}

	const float InputWrapper::GetMouseDeltaY() const
	{
		return static_cast<float>(myCurrentMouseState.lY);
	}

	const float InputWrapper::GetMouseWheelDelta() const
	{
		return static_cast<float>(myCurrentMouseState.lZ);
	}

	Vector::Vector2<float> InputWrapper::GetSaturatedMouseDelta()
	{
		RECT wRect;
		GetWindowRect(myWindowHandle, &wRect);
		float windowWidth = static_cast<float>(wRect.right - wRect.left);
		float windowHeight = static_cast<float>(wRect.bottom - wRect.top);
		Vector::Vector2<float> out;

		out.x = GetMouseDeltaX() / windowWidth;
		out.y = GetMouseDeltaY() / windowHeight;

		return out;
	}

	const float InputWrapper::GetCurrentMouseX() const
	{
		return myMousePosition.myX;
	}

	const float InputWrapper::GetCurrentMouseY() const
	{
		return myMousePosition.myY;
	}
}
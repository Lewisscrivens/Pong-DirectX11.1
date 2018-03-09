#include "pch.h"
#include "GameController.h"
#define XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  7849
#define XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE 8689
#define XINPUT_GAMEPAD_TRIGGER_THRESHOLD    30

GameController::GameController()
{
}


GameController::~GameController()
{
}

void GameController::Update()
{
	//Store the previous state of the gamepad for edge detection algorithm
	this->gamepadStatePrevious = this->gamepadState;

	//Poll the Xbox gamepad to get its current state
	ZeroMemory(&this->gamepadState, sizeof(XINPUT_STATE));

	DWORD dwResult = XInputGetState(0, &this->gamepadState);
	if (dwResult == ERROR_SUCCESS)
	{
		this->gamepadConnected = true;
		this->UpdateAnalogMagnitude();
		this->UpdateRightTriggerNormalised();
		this->UpdateLeftTriggerNormalised();
		this->UpdateLeftNormalised();
	}
	else
	{
		this->gamepadConnected = false;
		normlalisedLX = 0;
		normalisedLY = 0;
		rightTrigNorm = 0;
		leftTrigNorm = 0;

	}

}

void GameController::UpdateAnalogMagnitude()
{
	float LX = gamepadState.Gamepad.sThumbLX;
	float LY = gamepadState.Gamepad.sThumbLY;

	// determine the magnitude (sum of squares)
	// c^2 = a^2 + b^2
	float magnitude = sqrt(LX*LX + LY*LY);

	// what direction we are pointing in...
	float normalizedLX = LX / magnitude;
	float normalizedLY = LY / magnitude;

	normalizedMagnitude = 0;

	//check if the controller is outside a circular dead zone
	if (magnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		//clip the magnitude at its expected maximum value
		if (magnitude > 32767)
		{
			magnitude = 32767;
		}

		// adjust magnitude relative to the end of the dead zone
		magnitude -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

		// normalized between 0 and 1
		normalizedMagnitude = magnitude / (32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);

	}
	else //if the controller is in the deadzone zero out the magnitude
	{
		magnitude = 0.0;
		normalizedMagnitude = 0.0;
	}
}

void GameController::UpdateRightTriggerNormalised()
{
	// The maximum value of a trigger press is 255. So if we want to normalise the value 0 (not pressed) and 1 (fully pressed)
	// we should divide by 255... 255 / 255 = 0; 0 / 255 = 0;
	float value = gamepadState.Gamepad.bRightTrigger;
	rightTrigNorm = value / 255.0f;
}

void GameController::UpdateLeftTriggerNormalised()
{
	// The maximum value of a trigger press is 255. So if we want to normalise the value 0 (not pressed) and 1 (fully pressed)
	// we should divide by 255... 255 / 255 = 0; 0 / 255 = 0;
	float value = gamepadState.Gamepad.bLeftTrigger;
	leftTrigNorm = value / 255.0f;
}

bool GameController::IsButtonDown(unsigned short int button)
{
	if ((this->gamepadState.Gamepad.wButtons & button) == button)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GameController::WasButtonPressDetected(unsigned short int button)
{
	if (!(this->gamepadStatePrevious.Gamepad.wButtons & button) && (this->gamepadState.Gamepad.wButtons & button))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GameController::WasButtonReleaseDetected(unsigned short int button)
{
	if ((this->gamepadStatePrevious.Gamepad.wButtons & button)
		&& !(this->gamepadState.Gamepad.wButtons & button))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void GameController::SetVibration(int leftVal, int rightVal)
{
	// Create a Vibraton State
	XINPUT_VIBRATION vibration;

	// Zeroise the Vibration
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

	// Set the Vibration Values
	vibration.wLeftMotorSpeed = leftVal;
	vibration.wRightMotorSpeed = rightVal;

	// Vibrate the controller
	XInputSetState(0, &vibration);
}

float GameController::getLeftNormalizedMagnitude()
{
	return this->normalizedMagnitude;
}

float GameController::getRightTrifNormalised()
{
	return rightTrigNorm;
}

float GameController::getLeftTrigNormalised()
{
	return leftTrigNorm;
}

void GameController::UpdateLeftNormalised()
{
	// first of all, make sure the magnitude is outside of the deadzone
	float LX = gamepadState.Gamepad.sThumbLX;
	float LY = gamepadState.Gamepad.sThumbLY;

	// determine the magnitude (sum of squares)
	// c^2 = a^2 + b^2
	float magnitude = sqrt(LX*LX + LY*LY);

	//check if the controller is outside a circular dead zone
	if (magnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		// lets see what our X value is
		float xValue = gamepadState.Gamepad.sThumbLX;
		normlalisedLX = xValue / (32767);

		float yValue = gamepadState.Gamepad.sThumbLY;
		normalisedLY = yValue / (32767);
	}
	else
	{
		normlalisedLX = 0;
		normalisedLY = 0;
	}
}

float GameController::getLeftXNormalised()
{
	return normlalisedLX;
}

float GameController::getLeftYNormalised()
{
	return normalisedLY;
}

float GameController::getLeftNormalised()
{
	return normalizedMagnitude;
}

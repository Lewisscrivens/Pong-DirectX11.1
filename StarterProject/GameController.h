#pragma once
#include <Xinput.h>
class GameController
{
public:
	GameController();
	~GameController();

	void Update();
	bool IsButtonDown(unsigned short int button);
	bool WasButtonPressDetected(unsigned short int button);
	bool WasButtonReleaseDetected(unsigned short int button);
	float getLeftNormalised();
	float getLeftXNormalised();
	float getLeftYNormalised();
	float getLeftNormalizedMagnitude();
	float getRightTrifNormalised();
	float getLeftTrigNormalised();

private:
	void UpdateRightTriggerNormalised();
	void UpdateLeftTriggerNormalised();
	void UpdateAnalogMagnitude();
	void UpdateLeftNormalised();

public:


public:
	void SetVibration(int left = 0, int right = 0);

private:
	XINPUT_STATE gamepadState;
	XINPUT_STATE gamepadStatePrevious;
	XINPUT_VIBRATION vibration;
	bool gamepadConnected;
	float normalizedMagnitude;
	float rightTrigNorm;
	float leftTrigNorm;

	float normlalisedLX;
	float normalisedLY;
};

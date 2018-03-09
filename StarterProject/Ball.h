#pragma once
#include <SimpleMath.h>
#include <string>
#include "DeviceResources.h"
#include "SpriteResources.h"
#include "CollisionBox.h"
#include <vector>
#include "States.h"
#include "DifficultyMenu.h"

class Ball
{
public:
	Ball(std::wstring textureID, std::shared_ptr<DX::DeviceResources> deviceResources, float gbwidth, float gbheight);
	~Ball();

	bool leftScore;
	bool rightScore;
	int difficulty;

private:
	std::wstring textureID;
	DirectX::SimpleMath::Vector2 m_ballPosition;
	DirectX::SimpleMath::Vector2 m_ballVelocity;
	CollisionBox collisionBox;
	DirectX::SimpleMath::Vector2 BallSize;

	float gameboardWidth;
	float gameboardHeight;
	float maximumXVelocity;
	float directionalVelocity;

public:
	GameStates Update(double totalTime, double timeDelta, std::shared_ptr<DifficultyMenu> diff);
	void Render(std::shared_ptr<SpriteResources> spriteResources);
	void ReverseVelocity(DirectX::SimpleMath::Vector2 puckCentre, int puckWidth);
	const CollisionBox& getAABB() const;
	bool getLeftScore();
	bool getRightScore();
	void resetBallRight();
	void resetBallLeft();
};



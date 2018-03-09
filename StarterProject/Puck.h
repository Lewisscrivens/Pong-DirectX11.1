#pragma once
#include "SpriteResources.h"
#include <SimpleMath.h>
#include "DeviceResources.h"
#include "GameController.h"
#include "CollisionBox.h"
#include "States.h"
#include "Ball.h"

class Puck
{
public:
	Puck(std::wstring textureID,std::shared_ptr<DX::DeviceResources> resources, bool right, float gbheight, float gbwidth);
	~Puck();
	float yVel;
	float xVel;
	float paddleSpeed;
	int m_puckWidth;
	int m_puckHeight;
	float height;
	float width;
	int difficulty;

private:
	DirectX::SimpleMath::Vector2 m_puckPosition;
	DirectX::SimpleMath::Vector2 m_puckVelocity;
	DirectX::SimpleMath::Vector2 m_puckSize;
	std::shared_ptr<DX::DeviceResources> m_deviceResources;
	CollisionBox collisionBox;

private:
	bool m_right;
	std::wstring m_textureID;
	RECT m_rect;

public:
	void Update(double timeDelta, std::shared_ptr<GameController> controller, std::shared_ptr<Ball> ball, std::shared_ptr<DifficultyMenu> diff);
	void Render(std::shared_ptr<SpriteResources> spriteResouces);
};


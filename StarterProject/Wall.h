#pragma once
#include "SpriteResources.h"
#include <SimpleMath.h>
#include "DeviceResources.h"
#include "CollisionBox.h"
#include "States.h"
#include "Ball.h"

class Wall
{
public:
	Wall(std::wstring textureID, std::shared_ptr<DX::DeviceResources> resources, float gbheight, float gbwidth);
	~Wall();
	float yVel;
	float xVel;
	float wallSpeed;
	int m_WallWidth;
	int m_WallHeight;
	float height;
	float width;
	int difficulty;

private:
	DirectX::SimpleMath::Vector2 m_WallPosition;
	DirectX::SimpleMath::Vector2 m_WallVelocity;
	DirectX::SimpleMath::Vector2 m_WallSize;
	std::shared_ptr<DX::DeviceResources> m_deviceResources;
	CollisionBox collisionBox;

private:
	std::wstring m_textureID;
	RECT m_rect;

public:
	void Update(double timeDelta, std::shared_ptr<Ball> ball, std::shared_ptr<DifficultyMenu> diff);
	void Render(std::shared_ptr<SpriteResources> spriteResouces);
};


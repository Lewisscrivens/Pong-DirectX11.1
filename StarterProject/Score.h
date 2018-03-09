#pragma once
#include "States.h"
#include "TextWriter.h"
#include "SpriteResources.h"
#include "Ball.h"
#include <vector>
#include <string>

class Score
{
public:
	Score(bool right, float gbheight, float gbwidth);
	int m_currentScore;
	int scoreIncrease;
	std::wstring m_displayScore;
	float height;
	float width;
	DirectX::SimpleMath::Vector2 scorePos;

public:
	void Render(std::shared_ptr<SpriteResources> resources);
	void Update(double timeDelta, std::shared_ptr<Ball> ball);
	int getCurrentScore();

private:
	bool m_right;


};

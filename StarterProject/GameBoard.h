#pragma once
#include <string>
#include <SimpleMath.h>
#include <vector>
#include "States.h"
#include "GameController.h"
#include "SpriteResources.h"
#include "DeviceResources.h"
#include "Ball.h"
#include "Puck.h"
#include "Score.h"
#include "Wall.h"
#include "dottedLine.h"
#include "DifficultyMenu.h"

class GameBoard
{
public:
	GameBoard(std::shared_ptr<DX::DeviceResources> deviceResources, std::shared_ptr<SpriteResources> spriteResources);
	~GameBoard();
	float height;
	float width;
	int rightScore;
	int leftScore;
	std::wstring winner;
	bool endGame;

private:

	std::shared_ptr<Ball> m_ball;
	std::shared_ptr<Puck> m_left_puck;
	std::shared_ptr<Puck> m_right_puck;
	std::shared_ptr<Score> m_left_score;
	std::shared_ptr<Score> m_right_score;
	std::shared_ptr<dottedLine> m_midLine;
	std::shared_ptr<Wall> m_wall;																
	float gameboardHeight;
	float gameboardWidth;


private:
	void BuildLevel(int level);

public:
	GameStates Update(double totalTime, double timeDelta, std::shared_ptr<GameController> controller, std::shared_ptr<DifficultyMenu> diff);
	void Render(std::shared_ptr<SpriteResources> spriteResources);
	std::wstring getWinner();
};


#include "pch.h"
#include "GameBoard.h"


GameBoard::GameBoard(std::shared_ptr<DX::DeviceResources> deviceResources, std::shared_ptr<SpriteResources> spriteResources)
{
	endGame = false;
	rightScore = 0;
	leftScore = 0;
	winner = L"";

	//Create variables for screen height and width
	height = deviceResources->GetScreenViewport().Height;
	width = deviceResources->GetScreenViewport().Width;

	//Instantiate gameobjects to the gameboard when the playing state is active
	m_ball = std::shared_ptr<Ball>(new Ball(L"Assets/Disc.png", deviceResources, height, width));
	m_midLine = std::shared_ptr<dottedLine>(new dottedLine(L"Assets/DottedLine.png", deviceResources, height, width));
	m_wall = std::shared_ptr<Wall>(new Wall(L"Assets/Blocks.png", deviceResources, height, width));
	m_left_puck = std::make_shared<Puck>(L"Assets/Blocks.png", deviceResources, false, height, width);
	m_right_puck = std::make_shared<Puck>(L"Assets/Blocks.png", deviceResources, true, height, width);
	m_left_score = std::make_shared<Score>(false, height, width);
	m_right_score = std::make_shared<Score>(true, height, width);
}


GameBoard::~GameBoard()
{
}


void GameBoard::BuildLevel(int levelNumber)
{

}


GameStates GameBoard::Update(double totalTime, double timeDelta, std::shared_ptr<GameController> controller, std::shared_ptr<DifficultyMenu> diff)
{
	GameStates state = GameStates::sPlay;
	leftScore = m_left_score->getCurrentScore();
	rightScore = m_right_score->getCurrentScore();

	//If the current state is play then call the update function for all instatiated classes
	if (state == GameStates::sPlay)
	{
		state = m_ball->Update(totalTime, timeDelta, diff);
		m_left_puck->Update(timeDelta, controller, m_ball, diff);
		m_right_puck->Update(timeDelta, controller, m_ball, diff);
		m_wall->Update(timeDelta, m_ball, diff);
		m_left_score->Update(timeDelta, m_ball);
		m_right_score->Update(timeDelta, m_ball);
	}

	//If the left score is 11 then the winner is set to player 1
	if (leftScore == 11)
	{
		endGame = true;
		winner = L"Player 1";
	}//If the right score is 11 then the winner is set to player 2
	if (rightScore == 11)
	{
		endGame = true;
		winner = L"Player 2";
	}

	//When someone reaches 11 points the game is ended and the endgame state is loaded
	if (endGame == true)
	{
		state = GameStates::sEndGame;
	}
	return state;
}

//Run the render function for all instatiated classes
void GameBoard::Render(std::shared_ptr<SpriteResources> spriteResources)
{
	m_midLine->Render(spriteResources);
	m_left_puck->Render(spriteResources);
	m_right_puck->Render(spriteResources);
	m_left_score->Render(spriteResources);
	m_right_score->Render(spriteResources);
	m_wall->Render(spriteResources);
	m_ball->Render(spriteResources);
}

//method that returns the winner when called
std::wstring GameBoard::getWinner()
{
	return winner;
}
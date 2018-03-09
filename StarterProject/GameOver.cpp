#include "pch.h"
#include "GameOver.h"


GameOver::GameOver(std::shared_ptr<DX::DeviceResources> deviceResources)
{
	m_displayWinner = L"";
	winner = L"";

	screenHeight = deviceResources->GetScreenViewport().Height;
	screenWidth = deviceResources->GetScreenViewport().Width;

	//Text position on screen
	winTextPos.x = (screenWidth / 2) - 150;
	winTextPos.y = (screenHeight/ 2) - 20;

	//Initialize text
	winText = std::shared_ptr<TextWriter> (new TextWriter(std::wstring(m_displayWinner), DirectX::SimpleMath::Vector2(winTextPos)));
}


GameOver::~GameOver()
{
}


GameStates GameOver::Update(std::shared_ptr<GameController> gamepad, std::shared_ptr<GameBoard> game)
{
	winner = game->getWinner();//Get the correct player to draw the win text
	m_displayWinner = winner + L" " + L"has won!!";//Build the display text

	//Update and draw winner text
	winText = std::shared_ptr<TextWriter> (new TextWriter(std::wstring(m_displayWinner), DirectX::SimpleMath::Vector2(winTextPos)));

	GameStates state = GameStates::sEndGame;

	//If A is pressed on the gamepad in endGame state then exit the application
	if (gamepad->WasButtonReleaseDetected(XINPUT_GAMEPAD_A))
	{
		exit(0);
	}

	return state;
}

//Render the winText object
void GameOver::Render(std::shared_ptr<SpriteResources> spriteResources)
{
	winText->Render(spriteResources);
}
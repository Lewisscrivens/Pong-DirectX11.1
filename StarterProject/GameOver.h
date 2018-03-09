#pragma once
#include "DeviceResources.h"
#include "SpriteResources.h"
#include "TextWriter.h"
#include <vector>
#include "States.h"
#include "GameController.h"
#include "GameBoard.h"

class GameOver
{
public:
	GameOver(std::shared_ptr<DX::DeviceResources> deviceResources);
	~GameOver();

	std::wstring m_displayWinner;
	std::wstring winner;
	DirectX::SimpleMath::Vector2 winTextPos;
	std::shared_ptr<TextWriter> winText;
	float screenHeight;
	float screenWidth;

public:
	void Render(std::shared_ptr<SpriteResources> resources);
	GameStates Update(std::shared_ptr<GameController> controller, std::shared_ptr<GameBoard> game);

private:
	int m_selectedIndex;
};


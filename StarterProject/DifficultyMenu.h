#pragma once
#include "DeviceResources.h"
#include "SpriteResources.h"
#include "TextWriter.h"
#include <vector>
#include "States.h"
#include "GameController.h"

class DifficultyMenu
{
public:
	DifficultyMenu(std::shared_ptr<DX::DeviceResources> deviceResources);
	~DifficultyMenu();

	int difficulty;

public:
	void Render(std::shared_ptr<SpriteResources> resources);
	GameStates Update(std::shared_ptr<GameController> controller);
	int getDifficulty();

private:
	std::vector<std::shared_ptr<TextWriter>> m_difficultyMenuItems;
	int m_selectedIndex;
};


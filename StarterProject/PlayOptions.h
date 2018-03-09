#pragma once
#include "DeviceResources.h"
#include "SpriteResources.h"
#include "TextWriter.h"
#include <vector>
#include "States.h"
#include "GameController.h"

class PlayOptions
{
public:
	PlayOptions(std::shared_ptr<DX::DeviceResources> deviceResources);
	~PlayOptions();
	int selectedOption;

public:
	void Render(std::shared_ptr<SpriteResources> resources);
	GameStates Update(std::shared_ptr<GameController> controller);
	int getSelectedOption();

private:
	std::vector<std::shared_ptr<TextWriter>> m_PlayOptionsItems;
	int m_selectedIndex;
};


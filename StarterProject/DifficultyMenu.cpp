#include "pch.h"
#include "DifficultyMenu.h"


DifficultyMenu::DifficultyMenu(std::shared_ptr<DX::DeviceResources> deviceResources)
{
	difficulty = 0;

	std::shared_ptr<TextWriter> one = std::shared_ptr<TextWriter>
		(new TextWriter(std::wstring(L"Easy"), DirectX::SimpleMath::Vector2(100.0f, 100.0f)));
	std::shared_ptr<TextWriter> two = std::shared_ptr<TextWriter>
		(new TextWriter(std::wstring(L"Normal"), DirectX::SimpleMath::Vector2(100.0f, 200.0f)));
	std::shared_ptr<TextWriter> three = std::shared_ptr<TextWriter>
		(new TextWriter(std::wstring(L"Hard"), DirectX::SimpleMath::Vector2(100.0f, 300.0f)));

	m_difficultyMenuItems.push_back(one); // index = 0
	m_difficultyMenuItems.push_back(two); // index = 1
	m_difficultyMenuItems.push_back(three); // index = 2

	// set the selected index to item 1
	m_selectedIndex = 0;

	//Set the correct colours for the menu
	m_difficultyMenuItems[m_selectedIndex]->SetTintColour(DirectX::Colors::Red.v);
}


DifficultyMenu::~DifficultyMenu()
{
}


GameStates DifficultyMenu::Update(std::shared_ptr<GameController> gamepad)
{
	GameStates state = GameStates::sDiffMenu;

	//If B is pressed on the gamepad then load the menu state
	if (gamepad->WasButtonReleaseDetected(XINPUT_GAMEPAD_B))
	{
		state = GameStates::sMenu;
	}

	switch (m_selectedIndex)
	{
	case 0:
	{
		if (gamepad->WasButtonReleaseDetected(XINPUT_GAMEPAD_A))//If A is pressed while on index 0 then load play state and set difficulty to easy
		{
			difficulty = 0;//Easy
			state = GameStates::sPlay;
		}
		else if (gamepad->WasButtonReleaseDetected(XINPUT_GAMEPAD_DPAD_UP))//If Dpad up is pressed on the gamepad then go to index 2
		{
			m_difficultyMenuItems[m_selectedIndex]->SetTintColour(DirectX::Colors::Black.v);
			m_selectedIndex = 2;
			m_difficultyMenuItems[m_selectedIndex]->SetTintColour(DirectX::Colors::Red.v);
		}
		else if (gamepad->WasButtonReleaseDetected(XINPUT_GAMEPAD_DPAD_DOWN))//If Dpad down is pressed on the gamepad then go to index 1
		{
			m_difficultyMenuItems[m_selectedIndex]->SetTintColour(DirectX::Colors::Black.v);
			m_selectedIndex = 1;
			m_difficultyMenuItems[m_selectedIndex]->SetTintColour(DirectX::Colors::Red.v);
		}
	}
	break;
	case 1:
	{
		if (gamepad->WasButtonReleaseDetected(XINPUT_GAMEPAD_A))//If A is pressed while on index 1 then load play state and set difficulty to normal
		{
			difficulty = 1;//Normal
			state = GameStates::sPlay;
		}
		else if (gamepad->WasButtonReleaseDetected(XINPUT_GAMEPAD_DPAD_UP))//If Dpad up is pressed on the gamepad then go to index 0
		{
			m_difficultyMenuItems[m_selectedIndex]->SetTintColour(DirectX::Colors::Black.v);
			m_selectedIndex = 0;
			m_difficultyMenuItems[m_selectedIndex]->SetTintColour(DirectX::Colors::Red.v);
		}
		else if (gamepad->WasButtonReleaseDetected(XINPUT_GAMEPAD_DPAD_DOWN))//If Dpad down is pressed on the gamepad then go to index 2
		{
			m_difficultyMenuItems[m_selectedIndex]->SetTintColour(DirectX::Colors::Black.v);
			m_selectedIndex = 2;
			m_difficultyMenuItems[m_selectedIndex]->SetTintColour(DirectX::Colors::Red.v);
		}
	}
	break;
	case 2:
	{
		if (gamepad->WasButtonReleaseDetected(XINPUT_GAMEPAD_A))//If A is pressed while on index 2 then load play state and set difficulty to hard
		{
			difficulty = 2;//Hard
			state = GameStates::sPlay;
		}
		else if (gamepad->WasButtonReleaseDetected(XINPUT_GAMEPAD_DPAD_UP))//If Dpad up is pressed on the gamepad then go to index 1
		{
			m_difficultyMenuItems[m_selectedIndex]->SetTintColour(DirectX::Colors::Black.v);
			m_selectedIndex = 1;
			m_difficultyMenuItems[m_selectedIndex]->SetTintColour(DirectX::Colors::Red.v);
		}
		else if (gamepad->WasButtonReleaseDetected(XINPUT_GAMEPAD_DPAD_DOWN))//If Dpad down is pressed on the gamepad then go to index 0
		{
			m_difficultyMenuItems[m_selectedIndex]->SetTintColour(DirectX::Colors::Black.v);
			m_selectedIndex = 0;
			m_difficultyMenuItems[m_selectedIndex]->SetTintColour(DirectX::Colors::Red.v);
		}
	}
	break;
	default:
		break;
	}
	return state;
}

//Use for loop to render text to the screen
void DifficultyMenu::Render(std::shared_ptr<SpriteResources> spriteResources)
{
	for (int i = 0; i < m_difficultyMenuItems.size(); i++)
	{
		m_difficultyMenuItems[i]->Render(spriteResources);
	}
}

//Method to return difficulty to any class once called
int DifficultyMenu::getDifficulty()
{
	return difficulty;
}
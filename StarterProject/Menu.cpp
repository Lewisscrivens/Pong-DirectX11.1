#include "pch.h"
#include "Menu.h"


Menu::Menu(std::shared_ptr<DX::DeviceResources> deviceResources)
{
	std::shared_ptr<TextWriter> one = std::shared_ptr<TextWriter>
		(new TextWriter(std::wstring(L"Start new game"), DirectX::SimpleMath::Vector2(100.0f, 100.0f)));
	std::shared_ptr<TextWriter> two = std::shared_ptr<TextWriter>
		(new TextWriter(std::wstring(L"Exit Game"), DirectX::SimpleMath::Vector2(100.0f, 200.0f)));

	m_menuItems.push_back(one); // index = 0
	m_menuItems.push_back(two); // index = 1

	// set the selected index to item 1
	m_selectedIndex = 0;
	m_menuItems[m_selectedIndex]->SetTintColour(DirectX::Colors::Black.v);
}


Menu::~Menu()
{
}

//Index's are backwards but still works so didnt see a reason to change it
GameStates Menu::Update(std::shared_ptr<GameController> gamepad)
{
	GameStates state = GameStates::sMenu;
	switch (m_selectedIndex)
	{
	case 0:
	{
		if (gamepad->WasButtonReleaseDetected(XINPUT_GAMEPAD_A))//If A is pressed on the gamepad when on index 0 exit the application
		{
			exit(0);
		}
		else if (gamepad->WasButtonReleaseDetected(XINPUT_GAMEPAD_DPAD_UP))//If the Dpad up button is released on the gamepad then select index 1
		{
			m_menuItems[m_selectedIndex]->SetTintColour(DirectX::Colors::Red.v);
			m_selectedIndex = 1;
			m_menuItems[m_selectedIndex]->SetTintColour(DirectX::Colors::Black.v);
		}
		else if (gamepad->WasButtonReleaseDetected(XINPUT_GAMEPAD_DPAD_DOWN))//If the Dpad down button is released on the gamepad then select index 1
		{
			m_menuItems[m_selectedIndex]->SetTintColour(DirectX::Colors::Red.v);
			m_selectedIndex = 1;
			m_menuItems[m_selectedIndex]->SetTintColour(DirectX::Colors::Black.v);
		}
	}
	break;
	case 1:
	{
		if (gamepad->WasButtonReleaseDetected(XINPUT_GAMEPAD_A))//If A is pressed on the gamepad when on index 1 then open the Diffmenu state
		{
			state = GameStates::sDiffMenu;
		}
		else if (gamepad->WasButtonReleaseDetected(XINPUT_GAMEPAD_DPAD_UP))//If the Dpad up button is released on the gamepad then select index 0
		{
			m_menuItems[m_selectedIndex]->SetTintColour(DirectX::Colors::Red.v);
			m_selectedIndex = 0;
			m_menuItems[m_selectedIndex]->SetTintColour(DirectX::Colors::Black.v);
		}
		else if (gamepad->WasButtonReleaseDetected(XINPUT_GAMEPAD_DPAD_DOWN))//If the Dpad down button is released on the gamepad then select index 0
		{
			m_menuItems[m_selectedIndex]->SetTintColour(DirectX::Colors::Red.v);
			m_selectedIndex = 0;
			m_menuItems[m_selectedIndex]->SetTintColour(DirectX::Colors::Black.v);
		}
	}
	break;
	default:
		break;
	}
	return state;
}

//Render the text using a for loop
void Menu::Render(std::shared_ptr<SpriteResources> spriteResources)
{
	for (int i = 0; i < m_menuItems.size(); i++)
	{
		m_menuItems[i]->Render(spriteResources);
	}
}
#include "pch.h"
#include "PlayOptions.h"


PlayOptions::PlayOptions(std::shared_ptr<DX::DeviceResources> deviceResources)
{
	std::shared_ptr<TextWriter> one = std::shared_ptr<TextWriter>
		(new TextWriter(std::wstring(L"Player VS Player"), DirectX::SimpleMath::Vector2(100.0f, 100.0f)));
	std::shared_ptr<TextWriter> two = std::shared_ptr<TextWriter>
		(new TextWriter(std::wstring(L"Player VS Computer"), DirectX::SimpleMath::Vector2(100.0f, 200.0f)));

	selectedOption = 0;

	m_PlayOptionsItems.push_back(one); // index = 0
	m_PlayOptionsItems.push_back(two); // index = 1

								// set the selected index to item 1
	m_selectedIndex = 0;
	m_PlayOptionsItems[m_selectedIndex]->SetTintColour(DirectX::Colors::Red.v);
	m_PlayOptionsItems[1]->SetTintColour(DirectX::Colors::Black.v);
}


PlayOptions::~PlayOptions()
{
}


GameStates PlayOptions::Update(std::shared_ptr<GameController> gamepad)
{
	GameStates state = GameStates::sPlayOptionsMenu;

	if (gamepad->WasButtonReleaseDetected(XINPUT_GAMEPAD_B))
	{
		state = GameStates::sMenu;
	}

	switch (m_selectedIndex)
	{
	case 0:
	{
		if (gamepad->WasButtonReleaseDetected(XINPUT_GAMEPAD_A))
		{
			selectedOption = 1;
			state = GameStates::sDiffMenu;
		}
		else if (gamepad->WasButtonReleaseDetected(XINPUT_GAMEPAD_DPAD_UP))
		{
			m_PlayOptionsItems[m_selectedIndex]->SetTintColour(DirectX::Colors::Black.v);
			m_selectedIndex = 1;
			m_PlayOptionsItems[m_selectedIndex]->SetTintColour(DirectX::Colors::Red.v);
		}
		else if (gamepad->WasButtonReleaseDetected(XINPUT_GAMEPAD_DPAD_DOWN))
		{
			m_PlayOptionsItems[m_selectedIndex]->SetTintColour(DirectX::Colors::Black.v);
			m_selectedIndex = 1;
			m_PlayOptionsItems[m_selectedIndex]->SetTintColour(DirectX::Colors::Red.v);
		}
	}
	break;
	case 1:
	{
		if (gamepad->WasButtonReleaseDetected(XINPUT_GAMEPAD_A))
		{
			selectedOption = 2;
			state = GameStates::sDiffMenu;
		}
		else if (gamepad->WasButtonReleaseDetected(XINPUT_GAMEPAD_DPAD_UP))
		{
			m_PlayOptionsItems[m_selectedIndex]->SetTintColour(DirectX::Colors::Black.v);
			m_selectedIndex = 0;
			m_PlayOptionsItems[m_selectedIndex]->SetTintColour(DirectX::Colors::Red.v);
		}
		else if (gamepad->WasButtonReleaseDetected(XINPUT_GAMEPAD_DPAD_DOWN))
		{
			m_PlayOptionsItems[m_selectedIndex]->SetTintColour(DirectX::Colors::Black.v);
			m_selectedIndex = 0;
			m_PlayOptionsItems[m_selectedIndex]->SetTintColour(DirectX::Colors::Red.v);
		}
	}
	break;
	default:
		break;
	}
	return state;
}


void PlayOptions::Render(std::shared_ptr<SpriteResources> spriteResources)
{
	for (int i = 0; i < m_PlayOptionsItems.size(); i++)
	{
		m_PlayOptionsItems[i]->Render(spriteResources);
	}
}

int PlayOptions::getSelectedOption()
{
	return selectedOption;
}
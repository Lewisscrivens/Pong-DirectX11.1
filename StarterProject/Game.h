//
// Game.h
//

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include "SpriteResources.h"
#include "GameBoard.h"
#include "GameController.h"
#include "States.h"
#include "Menu.h"
#include "DifficultyMenu.h"
#include "GameOver.h"


// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game : public DX::IDeviceNotify
{
public:

    Game();

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();
    void Render();

    // Rendering helpers
    void Clear();

    // IDeviceNotify
    virtual void OnDeviceLost() override;
    virtual void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

private:

    void Update(DX::StepTimer const& timer);

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // Device resources.
    std::shared_ptr<DX::DeviceResources>    m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;

private:
	// TODO: Replace with your own content renderers.
	std::shared_ptr<SpriteResources> m_spriteResources;

	std::shared_ptr<GameBoard> m_gameBoard;
	std::shared_ptr<GameController> m_gamepad;
	std::shared_ptr<Menu> m_menu;
	std::shared_ptr<DifficultyMenu> m_diffMenu;
	std::shared_ptr<GameOver> m_gameOver;
	GameStates m_state;
};
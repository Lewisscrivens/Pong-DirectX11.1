//
// Game.cpp
//

#include "pch.h"
#include "Game.h"
#include <iostream>

using namespace DirectX;

using Microsoft::WRL::ComPtr;

Game::Game()
{
	m_deviceResources = std::make_shared<DX::DeviceResources>();
    m_deviceResources->RegisterDeviceNotify(this);
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
    m_deviceResources->SetWindow(window, width, height);

    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */

	m_spriteResources = std::make_shared<SpriteResources>(m_deviceResources);
	m_spriteResources->LoadTexture(L"Assets/Disc.png");
	m_spriteResources->LoadTexture(L"Assets/Blocks.png");
	m_spriteResources->LoadTexture(L"Assets/DottedLine.png");
	m_state = GameStates::sMenu;
	m_menu = std::make_shared<Menu>(m_deviceResources);
	m_diffMenu = std::make_shared<DifficultyMenu>(m_deviceResources);
	m_gameOver = std::make_shared<GameOver>(m_deviceResources);
	m_gameBoard = std::make_shared<GameBoard>(m_deviceResources, m_spriteResources);
	m_gamepad = std::make_shared<GameController>();
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
	float elapsedTime = float(timer.GetElapsedSeconds());
	float totalSeconds = float(timer.GetTotalSeconds());

    // TODO: Add your game logic here.
    elapsedTime;
	m_gamepad->Update();

	//Used to test playing state without controller
	//m_state = GameStates::sPlay;

	if (m_state == GameStates::sMenu)
	{
		m_state = m_menu->Update(m_gamepad);
	}
	else if (m_state == GameStates::sDiffMenu)
	{
		m_state = m_diffMenu->Update(m_gamepad);
	}
	else if (m_state == GameStates::sPlay)
	{
		if (m_gamepad->WasButtonReleaseDetected(XINPUT_GAMEPAD_B))
		{
			m_state = GameStates::sMenu;
		}
		else
		{
			m_state = m_gameBoard->Update(m_timer.GetTotalSeconds(), m_timer.GetElapsedSeconds(), m_gamepad, m_diffMenu);
		}
	}
	else if (m_state == GameStates::sEndGame)
	{
		m_state = m_gameOver->Update(m_gamepad, m_gameBoard);
	}
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    m_deviceResources->PIXBeginEvent(L"Render");
    auto context = m_deviceResources->GetD3DDeviceContext();

    // TODO: Add your rendering code here.
	m_spriteResources->GetSpriteBatch()->Begin(DirectX::SpriteSortMode_Deferred, m_spriteResources->GetCommonStates()->NonPremultiplied());

	if (m_state == GameStates::sPlay)
	{
		m_gameBoard->Render(m_spriteResources);
	}
	else if (m_state == GameStates::sMenu)
	{
		m_menu->Render(m_spriteResources);
	}
	else if (m_state == GameStates::sDiffMenu)
	{
		m_diffMenu->Render(m_spriteResources);
	}
	else if (m_state == GameStates::sEndGame)
	{
		m_gameOver->Render(m_spriteResources);
	}


	m_spriteResources->GetSpriteBatch()->End();

    m_deviceResources->PIXEndEvent();

    // Show the new frame.
    m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::White);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 800;
    height = 600;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    auto device = m_deviceResources->GetD3DDevice();

    // TODO: Initialize device dependent objects here (independent of window size).
    device;
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion

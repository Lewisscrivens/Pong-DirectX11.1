#pragma once
#include "DeviceResources.h"
#include "SpriteResources.h"
#include "States.h"
#include <SimpleMath.h>


class dottedLine
{
public:
	dottedLine(std::wstring textureID, std::shared_ptr<DX::DeviceResources> deviceResources, float gbheight, float gbwidth);
	~dottedLine();

	float screenHeight;
	float screenWidth;
	DirectX::SimpleMath::Vector2 m_linePosition;

private:
	std::wstring m_textureID;

public:
	void Render(std::shared_ptr<SpriteResources> spriteResources);
};


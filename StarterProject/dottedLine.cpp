#include "pch.h"
#include "dottedLine.h"


dottedLine::dottedLine(std::wstring textureID, std::shared_ptr<DX::DeviceResources> deviceResources, float gbheight, float gbwidth)
{
	m_textureID = textureID;
	screenHeight = gbheight;
	screenWidth = gbwidth;

	m_linePosition.x = (screenWidth / 2) - 5;
	m_linePosition.y = 0;
}

dottedLine::~dottedLine()
{
}

void dottedLine::Render(std::shared_ptr<SpriteResources> spriteResources)
{
	//Get the DirectX::SpriteBatch from the SpriteResources object
	spriteResources->GetSpriteBatch()->Draw(
		spriteResources->GetTexture(m_textureID).Get(),
		m_linePosition,
		nullptr,  //Need the raw C++ pointer
		DirectX::Colors::White.v,
		0,  //Angle of rotation in radians
		DirectX::SimpleMath::Vector2(0, 0), //Origin for the rotation
		2.2f, //Scale factor
		DirectX::SpriteEffects::SpriteEffects_None, //Reflections about the horizontal and verticle axes
		0.0f  //Layer depth; not required as we use DirectX::SpriteSortMode_Deferred
	);
}

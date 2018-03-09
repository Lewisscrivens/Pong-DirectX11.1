#include "pch.h"
#include "Wall.h"


Wall::Wall(std::wstring textureID, std::shared_ptr<DX::DeviceResources> resources, float gbheight, float gbwidth)
	: collisionBox{ DirectX::SimpleMath::Vector2(0,0), DirectX::SimpleMath::Vector2(23 / 2, 159 / 2) }
{
	m_deviceResources = resources;
	m_textureID = textureID;
	height = gbheight;
	width = gbwidth;

	difficulty = 0;
	wallSpeed = 300.0f;
	
	//Movement Variables for velocity vector
	xVel = 0.0f;
	yVel = wallSpeed;
	m_WallVelocity = DirectX::SimpleMath::Vector2(xVel, yVel);

	//Variables for placement on the screen
	m_WallWidth = 23;
	m_WallHeight = 159;
	m_WallPosition.x = (width / 2) + 18;
	m_WallPosition.y = 80;

	//Wall Image dimensions initialisation
	m_rect.left = 0;
	m_rect.top = 112;
	m_rect.right = 159;
	m_rect.bottom = 136;

	//Collision box offset fix
	collisionBox.SetAABB(this->m_WallPosition - DirectX::SimpleMath::Vector2(18, 0));
}


Wall::~Wall()
{
}

void Wall::Update(double timeDelta, std::shared_ptr<Ball> ball, std::shared_ptr<DifficultyMenu> diff)
{
	//Getting difficulty from DifficultyMenu class
	difficulty = diff->getDifficulty();

	//Dependant on which difficulty the game is set to change variables to increase difficulty
	if (difficulty == 0)//Easy
	{
		m_rect.left = 184;
		m_rect.top = 112;
		m_rect.right = 280;
		m_rect.bottom = 136;

		wallSpeed = 300.0f;
	}
	else if (difficulty == 1)//Normal
	{
		m_rect.left = 152;
		m_rect.top = 80;
		m_rect.right = 280;
		m_rect.bottom = 104;

		wallSpeed = 400.0f;
	}
	else if (difficulty == 2)//Hard
	{
		m_rect.left = 0;
		m_rect.top = 112;
		m_rect.right = 159;
		m_rect.bottom = 136;

		wallSpeed = 500.0f;
	}

	DirectX::SimpleMath::Vector2 toMove = timeDelta * this->m_WallVelocity;//Creating a vector direction to move in at the speed initialized
	m_WallPosition += toMove;//Adding the destination to the walls position in order to move it

	//Collision box offset fix while the wall is moving
	this->collisionBox.SetAABB(this->m_WallPosition - DirectX::SimpleMath::Vector2(18, 0));

	//If the wall position touches the top screen boundry then reverse the wall speed else reverse again
	if (m_WallPosition.y < 80)
	{
		yVel = wallSpeed;
	}
	else if (m_WallPosition.y > height - m_WallHeight)
	{
		yVel = -wallSpeed;
	}

	//If the wall colides with the ball the balls veolicty is reversed
	if (collisionBox.DoesIntersect(ball->getAABB()))
	{
		//calculate point of contact.
		DirectX::SimpleMath::Vector2 WallCentre = this->collisionBox.getCentre();
		ball->ReverseVelocity(WallCentre, m_WallHeight);
	}

	//Velocity controller
	m_WallVelocity = DirectX::SimpleMath::Vector2(xVel, yVel);
}

//Render the wall to the screen using the TextureID from gameBoard
void Wall::Render(std::shared_ptr<SpriteResources> spriteResources)
{
	float rotation = 3.14159265359 / 2;
	//Get the DirectX::SpriteBatch from the SpriteResources object
	spriteResources->GetSpriteBatch()->Draw(
		spriteResources->GetTexture(this->m_textureID).Get(),
		this->m_WallPosition,
		&m_rect,  //Need the raw C++ pointer
		DirectX::Colors::Red.v,
		rotation,  //Angle of rotation in radians
		DirectX::SimpleMath::Vector2(0, 0), //Origin for the rotation
		1.0f, //Scale factor
		DirectX::SpriteEffects::SpriteEffects_None, //Reflections about the horizontal and verticle axes
		0.0f  //Layer depth; not required as we use DirectX::SpriteSortMode_Deferred
	);
}
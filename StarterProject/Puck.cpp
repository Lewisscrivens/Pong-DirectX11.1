#include "pch.h"
#include "Puck.h"


Puck::Puck(std::wstring textureID, std::shared_ptr<DX::DeviceResources> resources, bool right, float gbheight, float gbwidth)
	: collisionBox{ DirectX::SimpleMath::Vector2(0,0), DirectX::SimpleMath::Vector2(23 / 2, 159 / 2) }
{
	m_deviceResources = resources;
	m_textureID = textureID;
	m_right = right;
	height = gbheight;
	width = gbwidth;
	difficulty = 0;

	//Movement Variables for velocity vector
	xVel = 0.0f;
	yVel = 0.0f;
	paddleSpeed = 0.0f;
	m_puckPosition = DirectX::SimpleMath::Vector2(0.0f, 0.0f);
	m_puckVelocity = DirectX::SimpleMath::Vector2(xVel, yVel);
	m_puckWidth = 23;
	m_puckHeight = 159;

	//Puck Image dimensions initialisation
	m_rect.left = 0;
	m_rect.top = 0;
	m_rect.right = 0;
	m_rect.bottom = 0;
	
	//If right is true when the class is instatiated then set the position accordingly
	if (m_right == true)
	{
		m_puckPosition.x = width - 32.0f;
	}
	else
	{
		m_puckPosition.x = 50.0f;
	}

	//the pucks position in the y-axis is always the same
	m_puckPosition.y = height / 2 - (m_puckHeight / 2);

	//Collisiojn box offset fix
	collisionBox.SetAABB(this->m_puckPosition - DirectX::SimpleMath::Vector2 (18, 0));
}


Puck::~Puck()
{
}

void Puck::Update(double timeDelta, std::shared_ptr<GameController> controller, std::shared_ptr<Ball> ball, std::shared_ptr<DifficultyMenu> diff)
{
	//Getting difficulty variable from DifficultyMenu class
	difficulty = diff->getDifficulty();

	//Dependant on difficulty change some of the variables of the class to make the game harder
	if (difficulty == 0)//Easy
	{
		m_rect.left = 0;
		m_rect.top = 112;
		m_rect.right = 159;
		m_rect.bottom = 136;

		paddleSpeed = 400.0f;
	}
	else if (difficulty == 1)//Normal
	{
		m_rect.left = 152;
		m_rect.top = 80;
		m_rect.right = 280;
		m_rect.bottom = 104;

		paddleSpeed = 400.0f;
	}
	else if (difficulty == 2)//Hard
	{
		m_rect.left = 184;
		m_rect.top = 112;
		m_rect.right = 280;
		m_rect.bottom = 136;

		paddleSpeed = 500.0f;
	}


	DirectX::SimpleMath::Vector2 toMove = timeDelta * this->m_puckVelocity;//Creating a vector direction to move in at the speed initialized
	m_puckPosition += toMove;//Adding the destination to the puck position in order to move it

	//Variables to indicate weather the puck is touching the top or bottom of the screen
	bool hitBottom = false;
	bool hitTop = false;

	//Collision box offset fix
	this->collisionBox.SetAABB(this->m_puckPosition - DirectX::SimpleMath::Vector2(18, 0));

	//If the ball intersects with the puck reverse the velocity of the ball in the ball class
	if (collisionBox.DoesIntersect(ball->getAABB()))
	{
		// calculate point of contact.
		DirectX::SimpleMath::Vector2 puckCentre = this->collisionBox.getCentre();
		ball->ReverseVelocity(puckCentre, m_puckHeight);
	}

	//If the buck position goes to the bottom of the screen then hitBottom is true
	if (m_puckPosition.y > height - m_puckHeight)
	{
		hitBottom = true;
	}//If the buck position goes to the top of the screen then hitTop is true
	if (m_puckPosition.y < 80)
	{
		hitTop = true;
	}

	//player 1 movement controls
	if (m_right == true && hitBottom == false && hitTop == false)
	{
		if (controller->WasButtonPressDetected(XINPUT_GAMEPAD_Y))
		{
			yVel = -paddleSpeed;
		}
		if (controller->WasButtonReleaseDetected(XINPUT_GAMEPAD_Y))
		{
			yVel = 0.0;
		}
		if (controller->WasButtonPressDetected(XINPUT_GAMEPAD_A))
		{
			yVel = paddleSpeed;
		}
		if (controller->WasButtonReleaseDetected(XINPUT_GAMEPAD_A))
		{
			yVel = 0.0f;
		}
	}
	//Player 2 movement controls
	else if (m_right == false && hitBottom == false && hitTop == false)
	{
		if (controller->WasButtonPressDetected(XINPUT_GAMEPAD_DPAD_UP))
		{
			yVel = -paddleSpeed;
		}
		if (controller->WasButtonReleaseDetected(XINPUT_GAMEPAD_DPAD_UP))
		{
			yVel = 0.0f;
		}
		if (controller->WasButtonPressDetected(XINPUT_GAMEPAD_DPAD_DOWN))
		{
			yVel = paddleSpeed;
		}
		if (controller->WasButtonReleaseDetected(XINPUT_GAMEPAD_DPAD_DOWN))
		{
			yVel = 0.0f;
		}
	}
	//Controls to stop paddle from exiting the visibile area
	else if (m_right == true && hitBottom == true)
	{
		yVel = 0.0f;

		if (controller->WasButtonPressDetected(XINPUT_GAMEPAD_Y))
		{
			yVel = -paddleSpeed;
		}
	}
	else if (m_right == true && hitTop == true)
	{
		yVel = 0.0f;

		if (controller->WasButtonPressDetected(XINPUT_GAMEPAD_A))
		{
			yVel = paddleSpeed;
		}
	}
	else if (m_right == false && hitBottom == true)
	{
		yVel = 0.0f;

		if (controller->WasButtonPressDetected(XINPUT_GAMEPAD_DPAD_UP))
		{
			yVel = -paddleSpeed;
		}
	}
	else if (m_right == false && hitTop == true)
	{
		yVel = 0.0f;

		if (controller->WasButtonPressDetected(XINPUT_GAMEPAD_DPAD_DOWN))
		{
			yVel = paddleSpeed;
		}
	}
	//Sets the velocity to the correct parameters to suit any buttons pressed
	m_puckVelocity = DirectX::SimpleMath::Vector2(xVel, yVel);
}

//Renders the puck using the texturID variable from gameBoard
void Puck::Render(std::shared_ptr<SpriteResources> spriteResources)
{
	float rotation = 3.14159265359 / 2;
	//Get the DirectX::SpriteBatch from the SpriteResources object
	spriteResources->GetSpriteBatch()->Draw(
		spriteResources->GetTexture(this->m_textureID).Get(),
		this->m_puckPosition,
		&m_rect,  //Need the raw C++ pointer
		DirectX::Colors::Black.v,
		rotation,  //Angle of rotation in radians
		DirectX::SimpleMath::Vector2(0, 0), //Origin for the rotation
		1.0f, //Scale factor
		DirectX::SpriteEffects::SpriteEffects_None, //Reflections about the horizontal and verticle axes
		0.0f  //Layer depth; not required as we use DirectX::SpriteSortMode_Deferred
	);
}
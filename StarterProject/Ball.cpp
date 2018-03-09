#include "pch.h"
#include "Ball.h"


Ball::Ball(std::wstring textureID, std::shared_ptr<DX::DeviceResources> deviceResources, float gbheight, float gbwidth)
	: collisionBox{ DirectX::SimpleMath::Vector2(m_ballPosition.x + BallSize.x / 2, m_ballPosition.y + BallSize.y / 2), DirectX::SimpleMath::Vector2(30.0f / 2, 30.0f / 2) }
{
	this->textureID = textureID;

	BallSize = DirectX::SimpleMath::Vector2(32.0f, 32.0f);

	difficulty = 0;
	leftScore = false;
	rightScore = false;

	//Initialising variables
	maximumXVelocity = 500.0f;
	directionalVelocity = maximumXVelocity;

	gameboardWidth = gbwidth;
	gameboardHeight = gbheight;

	//moves ball back to starting position
	resetBallLeft();
	collisionBox.SetAABB(m_ballPosition);
}


Ball::~Ball()
{
}

GameStates Ball::Update(double totalTime, double timeDelta, std::shared_ptr<DifficultyMenu> diff)
{
	//Updating the difficulty to match users choice from diffMenu
	difficulty = diff->getDifficulty();

	if (difficulty == 0)
	{
		maximumXVelocity = 500.0f;
		directionalVelocity = maximumXVelocity;
	}
	else if (difficulty == 1)
	{
		maximumXVelocity = 700.0f;
		directionalVelocity = maximumXVelocity;
	}
	else if (difficulty == 2)
	{
		maximumXVelocity = 900.0f;
		directionalVelocity = maximumXVelocity;
	}

	GameStates state = GameStates::sPlay;
	DirectX::SimpleMath::Vector2 toMove = timeDelta * this->m_ballVelocity;//Creating a vector direction to move in at the speed initialized
	m_ballPosition += toMove; //Adding the destination to the ball position in order to move it
	this->collisionBox.SetAABB(m_ballPosition);//Setting the collisionbox to the balls position

	//If the ball position on the x-axis exits the left of the screen then reset the ball and increase right players score
	if (this->m_ballPosition.x < 0)
	{
		leftScore = true;
		directionalVelocity = maximumXVelocity;
		resetBallRight();
	}
	else {
		leftScore = false;
	}//If the ball position on the x-axis exits the right of the screen then reset the ball and increase left players score
	if (this->m_ballPosition.x + BallSize.x > gameboardWidth)
	{
		rightScore = true;
		directionalVelocity = -1 * maximumXVelocity;
		resetBallLeft();
	}
	else {
		rightScore = false;
	}

	//When the ball hits the top or bottom of the screen mod the velocity in the y-axis
	if ((this->m_ballPosition.y < 80) || (this->m_ballPosition.y + BallSize.y > gameboardHeight))
	{
		this->m_ballVelocity.y *= -1;
	}
	return state;
}

void Ball::ReverseVelocity(DirectX::SimpleMath::Vector2 puckCentre, int puckWidth)
{
	DirectX::SimpleMath::Vector2 ballCentre = this->collisionBox.getCentre();
	DirectX::SimpleMath::Vector2 diff = ballCentre - puckCentre;

	//Calculate the angle the ball hit the paddle
	float angle = atan2(diff.y, diff.x);

	//Calculate the velocity dependant on the angle of collision
	float xVel = cos(angle)*maximumXVelocity;
	float yVel = sin(angle)*maximumXVelocity;

	//Set ball's velocity according to previous calculations
	this->m_ballVelocity = DirectX::SimpleMath::Vector2(xVel, yVel);
}

//Getting the collision box measurments
const CollisionBox& Ball::getAABB() const
{
	return this->collisionBox;
}

//Method for other classes to get the leftScore bool
bool Ball::getLeftScore()
{
	return leftScore;
}

//Method for other classes to get the rightScore bool
bool Ball::getRightScore()
{
	return rightScore;
}

//Resets the balls position and velocity to serve the left player when scored
void Ball::resetBallRight()
{
	m_ballPosition.x = (gameboardWidth / 2) - (BallSize.x / 2) + 50;
	m_ballPosition.y = (gameboardHeight / 2) - (BallSize.y / 2);
	m_ballVelocity = DirectX::SimpleMath::Vector2(directionalVelocity, 0.0f);
}

//Resets the balls position and velocity to serve the right player when scored
void Ball::resetBallLeft()
{
	m_ballPosition.x = (gameboardWidth / 2) - (BallSize.x / 2) - 50;
	m_ballPosition.y = (gameboardHeight / 2) - (BallSize.y / 2);
	m_ballVelocity = DirectX::SimpleMath::Vector2(directionalVelocity, 0.0f);
}

//Renders the puck using the texturID variable from gameBoard
void Ball::Render(std::shared_ptr<SpriteResources> spriteResources)
{
	//Get the DirectX::SpriteBatch from the SpriteResources object
	spriteResources->GetSpriteBatch()->Draw(
		spriteResources->GetTexture(this->textureID).Get(),
		this->m_ballPosition,
		nullptr,  //Need the raw C++ pointer
		DirectX::Colors::Black.v,
		0,  //Angle of rotation in radians
		DirectX::SimpleMath::Vector2(0, 0), //Origin for the rotation
		1.0f, //Scale factor
		DirectX::SpriteEffects::SpriteEffects_None, //Reflections about the horizontal and verticle axes
		0.0f  //Layer depth; not required as we use DirectX::SpriteSortMode_Deferred
	);
}




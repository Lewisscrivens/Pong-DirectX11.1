#include "pch.h"
#include "Score.h"


Score::Score(bool right, float gbheight, float gbwidth)
{
	height = gbheight;
	width = gbwidth;
	m_right = right;

	m_currentScore = 0;
	scoreIncrease = 1;
	m_displayScore = L"";

	//If right is true when instantiated then position accordingly
	if (right == true)
	{
		scorePos = DirectX::SimpleMath::Vector2((width / 2) + 50, 0);
	}
	else {
		scorePos = DirectX::SimpleMath::Vector2((width / 2) - 75, 0);
	}
}

void Score::Update(double timeDelta, std::shared_ptr<Ball> ball)
{
	//If the ball collides with the left wall then increment the score on the right
	if (ball->getLeftScore() == true)
	{
		if (m_right == true)
		{
			m_currentScore += 1;
		}
	}//If the ball collides with the right wall then increment the score on the left
	if (ball->getRightScore() == true)
	{
		if (m_right == false)
		{
			m_currentScore += 1;
		}
	}

	//Update the current score
	this->m_displayScore = std::to_wstring(m_currentScore);
}

//Render the score text to the screen using spriteResources
void Score::Render(std::shared_ptr<SpriteResources> resources)
{
	const wchar_t *output = m_displayScore.c_str();
	resources->GetSpriteFont()->DrawString(
		resources->GetSpriteBatch().get(),
		output,
		scorePos,//Position vector
		DirectX::Colors::Black,
		0.f,
		DirectX::SimpleMath::Vector2(0, 0));
}

//Method which returns the current score
int Score::getCurrentScore()
{
	return m_currentScore;
}
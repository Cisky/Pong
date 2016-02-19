#include "Paddle.h"

//CONSTRUCTOR
Paddle::Paddle()
{
	paddleSize.x = 20.0f;
	paddleSize.y = 100.0f;
	
	paddleSpeed = 15.0f;

	setSize(paddleSize);
	setFillColor(Color::White);
}

//MEMBER FUNCTION
void Paddle::update(Vector2f &courtSize, Keyboard::Key up, Keyboard::Key down, Vector2f &screenSize)
{
	if (Keyboard::isKeyPressed(up))
	{
		if (this->getPosition().y > courtSize.y)
			this->move(0.0f, -paddleSpeed);
		else
			this->setPosition(this->getPosition().x, courtSize.y);
	}
	else if (Keyboard::isKeyPressed(down))
	{
		if (this->getPosition().y + paddleSize.y < screenSize.y - courtSize.y)
			this->move(0.0f, paddleSpeed);
		else
			this->setPosition(this->getPosition().x, screenSize.y - courtSize.y - paddleSize.y);
	}
}

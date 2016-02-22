#include "Paddle.h"

//CONSTRUCTOR
Paddle::Paddle()
{
	paddleSize.x = PADDLESIZEX;
	paddleSize.y = PADDLESIZEY;
	
	paddleSpeed = PADDLESPEED;
	isKeyPressed = false;

	setSize(paddleSize);
	setFillColor(PADDLECOLOR);
}

//MEMBER FUNCTION
bool Paddle::isMoving() const
{
	return isKeyPressed;
}

void Paddle::update(Keyboard::Key up, Keyboard::Key down)
{
	if (Keyboard::isKeyPressed(up))
	{
		if (this->getPosition().y > COURTSIZEY)
		{
			this->move(0.0f, -PADDLESPEED);
			isKeyPressed = true;
		}
		else
		{
			this->setPosition(this->getPosition().x, COURTSIZEY);
			isKeyPressed = false;
		}
	}
	else if (Keyboard::isKeyPressed(down))
	{
		if (this->getPosition().y + paddleSize.y < HEIGHT - COURTSIZEY)
		{
			this->move(0.0f, PADDLESPEED);
			isKeyPressed = true;
		}
		else
		{
			this->setPosition(this->getPosition().x, HEIGHT - COURTSIZEY - paddleSize.y);
			isKeyPressed = false;
		}
	}
	else
	{
		isKeyPressed = false;
	}
}

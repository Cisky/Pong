#define _USE_MATH_DEFINES

#include "Ball.h"
#include <cmath>

//CONSTRUCTOR
Ball::Ball(unsigned int screenWidth, unsigned int screenHeight)
{
	ballSize.x = 20.0f;
	ballSize.y = 20.0f;

	ballMoveVector.x = 0.0f;
	ballMoveVector.y = 0.0f;

	ballSpeed = 10.0f;
	ballAngle = 0.0f;

	this->setSize(ballSize);
	this->setFillColor(Color::White);
	this->setPosition((screenWidth - ballSize.x) / 2.0f, (screenHeight - ballSize.y) / 2.0f);
}

//MEMBER FUNCTION
void Ball::leftPaddleCollision(Paddle &leftPaddle)
{
	//CHECK THE COLLISIONS BETWEEN BALL AND LEFT PADDLE
	if (this->getPosition().x <= leftPaddle.getPosition().x + leftPaddle.getSize().x &&
		this->getPosition().x >= leftPaddle.getPosition().x + leftPaddle.getSize().x / 2.0f &&
		this->getPosition().y + ballSize.y >= leftPaddle.getPosition().y &&
		this->getPosition().y <= leftPaddle.getPosition().y + leftPaddle.getSize().y)
	{
		ballAngle = M_PI - ballAngle;
		this->setPosition(leftPaddle.getPosition().x + leftPaddle.getSize().x + 0.1f, this->getPosition().y);
	}
}

void Ball::rightPaddleCollision(Paddle &rightPaddle)
{
	//CHECK THE COLLISIONS BETWEEN BALL AND RIGHT PADDLE
	if (this->getPosition().x + ballSize.x >= rightPaddle.getPosition().x &&
		this->getPosition().x + ballSize.x <= rightPaddle.getPosition().x + rightPaddle.getSize().x / 2.0f &&
		this->getPosition().y + ballSize.y >= rightPaddle.getPosition().y &&
		this->getPosition().y <= rightPaddle.getPosition().y + rightPaddle.getSize().y)
	{
		ballAngle = M_PI - ballAngle;
		this->setPosition(rightPaddle.getPosition().x - ballSize.x - 0.1f, this->getPosition().y);
	}
}

void Ball::courtCollision(unsigned short &scoreLeft, unsigned short &scoreRight, Vector2f &courtSize, Vector2f &screenSize, bool &startGame)
{
	//CHECK COLLISIONS BETWEEN BALL AND TOP-SCREEN
	if (this->getPosition().y + ballMoveVector.y <= courtSize.y)
	{
		ballAngle = -ballAngle;
		this->setPosition(this->getPosition().x, courtSize.y);
	}
	//CHECK COLLISIONS BETWEEN BALL AND BOTTOM-SCREEN
	else if (this->getPosition().y + ballSize.y + ballMoveVector.y >= screenSize.y - courtSize.y)
	{
		ballAngle = -ballAngle;
		this->setPosition(this->getPosition().x, screenSize.y - courtSize.y - ballSize.y);
	}
	//CHECK COLLISIONS BETWEEN BALL AND LEFT-SCREEN
	else if (this->getPosition().x + ballSize.x <= 0.0f)
	{
		ballAngle += (180 * M_PI / 180);
		this->setPosition((screenSize.x - this->ballSize.x) / 2.0f, (screenSize.y - this->ballSize.y) / 2.0f);

		scoreRight++;
		if (scoreRight == 10)
			startGame = false;
	}
	//CHECK COLLISIONS BETWEEN BALL AND RIGHT-SCREEN
	else if (this->getPosition().x > screenSize.x)
	{
		ballAngle += (180 * M_PI / 180);
		this->setPosition((screenSize.x - this->ballSize.x) / 2.0f, (screenSize.y - this->ballSize.y) / 2.0f);

		scoreLeft++;
		if (scoreLeft == 10)
			startGame = false;
	}
}

void Ball::update()
{
	//MOVE BALL
	ballMoveVector.x = cos(ballAngle) * ballSpeed;
	ballMoveVector.y = sin(ballAngle) * ballSpeed;
	this->move(ballMoveVector.x, ballMoveVector.y);
}
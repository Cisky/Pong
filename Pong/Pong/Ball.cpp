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
	
}

void Ball::rightPaddleCollision(Paddle &rightPaddle)
{
	//CHECK THE COLLISIONS BETWEEN BALL AND RIGHT PADDLE

}

void Ball::courtCollision(unsigned short &scoreLeft, unsigned short &scoreRight)
{
	//CHECK COLLISIONS BETWEEN BALL AND TOP-SCREEN, BOTTOM-SCREEN, LEFT-SCREEN, RIGHT-SCREEN 

}

void Ball::update()
{
	//MOVE BALL
}
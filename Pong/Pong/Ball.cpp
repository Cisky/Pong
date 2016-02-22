#define _USE_MATH_DEFINES

#include "Ball.h"

//CONSTRUCTOR
Ball::Ball()
{
	ballSize.x = BALLSIZEX;
	ballSize.y = BALLSIZEY;

	ballMoveVector = Vector2f(0.0f, 0.0f);

	initSpeed = BALLSPEED;
	ballSpeed = BALLSPEED;
	ballAngle = (rand() % 90 - 45) * M_PI / 180;

	this->setSize(ballSize);
	this->setFillColor(BALLCOLOR);
	this->setPosition((WIDTH - BALLSIZEX) / 2.0f, (HEIGHT - BALLSIZEY) / 2.0f);

	if (ballBorderSoundBuffer.loadFromFile(BALLBORDERSOUND))
		ballBorderSound.setBuffer(ballBorderSoundBuffer);

	if (ballPaddleSoundBuffer.loadFromFile(BALLPADDLESOUND))
		ballPaddleSound.setBuffer(ballPaddleSoundBuffer);

	if (PointSoundBuffer.loadFromFile(POINTSOUND))
		pointSound.setBuffer(PointSoundBuffer);
}

//MEMBER FUNCTION
void Ball::leftPaddleCollision(Paddle &leftPaddle)
{
	//CHECK THE COLLISIONS BETWEEN BALL AND LEFT PADDLE
	if (this->getPosition().x <= leftPaddle.getPosition().x + PADDLESIZEX &&
		this->getPosition().x >= leftPaddle.getPosition().x + PADDLESIZEX / 2.0f &&
		this->getPosition().y + ballSize.y >= leftPaddle.getPosition().y &&
		this->getPosition().y <= leftPaddle.getPosition().y + PADDLESIZEY)
	{
		ballPaddleSound.play();

		if (ballSpeed != initSpeed)
			ballSpeed = initSpeed;

		if (this->getPosition().y <= leftPaddle.getPosition().y + PADDLESIZEY / 7.0f && leftPaddle.isMoving())
		{
			ballSpeed += 2.5f;
			ballAngle = M_PI - ballAngle + 20 * M_PI / 180;
		}
		else if (this->getPosition().y <= leftPaddle.getPosition().y + PADDLESIZEY / 2.0f)
			ballAngle = M_PI - ballAngle + 10 * M_PI / 180;
		else if (this->getPosition().y >= leftPaddle.getPosition().y + (6.0f * PADDLESIZEY / 7.0f) && leftPaddle.isMoving())
		{
			ballSpeed += 2.5f;
			ballAngle = M_PI - ballAngle - 20 * M_PI / 180;
		}
		else if (this->getPosition().y > leftPaddle.getPosition().y + PADDLESIZEY / 2.0f)
			ballAngle = M_PI - ballAngle - 10 * M_PI / 180;

		//[-30; 30]
		if ((ballAngle * 180 / M_PI) - (300 * ((int)(ballAngle * 180 / M_PI) / 360)) < -30)
			ballAngle = -30 * M_PI / 180;
		else if ((ballAngle * 180 / M_PI) - (300 * ((int)(ballAngle * 180 / M_PI) / 360)) > 30)
			ballAngle = 30 * M_PI / 180;

		this->setPosition(leftPaddle.getPosition().x + PADDLESIZEX + 0.1f, this->getPosition().y);
	}
}

void Ball::rightPaddleCollision(Paddle &rightPaddle)
{
	//CHECK THE COLLISIONS BETWEEN BALL AND RIGHT PADDLE
	if (this->getPosition().x + ballSize.x >= rightPaddle.getPosition().x &&
		this->getPosition().x + ballSize.x <= rightPaddle.getPosition().x + PADDLESIZEX / 2.0f &&
		this->getPosition().y + ballSize.y >= rightPaddle.getPosition().y &&
		this->getPosition().y <= rightPaddle.getPosition().y + PADDLESIZEY)
	{
		ballPaddleSound.play();

		if (ballSpeed != initSpeed)
			ballSpeed = initSpeed;

		if (this->getPosition().y <= rightPaddle.getPosition().y + PADDLESIZEY / 7.0f && rightPaddle.isMoving())
		{
			ballSpeed += 2.5f;
			ballAngle = M_PI - ballAngle + 20 * M_PI / 180;
		}
		else if (this->getPosition().y <= rightPaddle.getPosition().y + PADDLESIZEY / 2.0f)
			ballAngle = M_PI - ballAngle + 10 * M_PI / 180;
		else if (this->getPosition().y >= rightPaddle.getPosition().y + (6.0f * PADDLESIZEY / 7.0f) && rightPaddle.isMoving())
		{
			ballSpeed += 2.5f;
			ballAngle = M_PI - ballAngle - 20 * M_PI / 180;
		}
		else if (this->getPosition().y > rightPaddle.getPosition().y + PADDLESIZEY / 2.0f)
			ballAngle = M_PI - ballAngle - 10 * M_PI / 180;

		//[160; 200]
		if ((ballAngle * 180 / M_PI) - (360 * ((int)(ballAngle * 180 / M_PI) / 360)) < 160)
			ballAngle = 160 * M_PI / 180;
		else if ((ballAngle * 180 / M_PI) - (360 * ((int)(ballAngle * 180 / M_PI) / 360)) > 200)
			ballAngle = 200 * M_PI / 180;

		this->setPosition(rightPaddle.getPosition().x - ballSize.x - 0.1f, this->getPosition().y);
	}
}

void Ball::courtCollision(unsigned short &scoreLeft, unsigned short &scoreRight, bool &startGame)
{
	//CHECK COLLISIONS BETWEEN BALL AND TOP-SCREEN
	if (this->getPosition().y + ballMoveVector.y <= COURTSIZEY)
	{
		ballBorderSound.play();

		ballAngle = -ballAngle;
		this->setPosition(this->getPosition().x, COURTSIZEY);
	}
	//CHECK COLLISIONS BETWEEN BALL AND BOTTOM-SCREEN
	else if (this->getPosition().y + ballSize.y + ballMoveVector.y >= HEIGHT - COURTSIZEY)
	{
		ballBorderSound.play();

		ballAngle = -ballAngle;
		this->setPosition(this->getPosition().x, HEIGHT - COURTSIZEY - ballSize.y);
	}
	//CHECK COLLISIONS BETWEEN BALL AND LEFT-SCREEN
	else if (this->getPosition().x + ballSize.x <= 0.0f)
	{
		pointSound.play();

		float ballPositionX = (WIDTH - ballSize.x) / 2.0f;
		float ballPositionY = rand() % (int)(WIDTH - ballSize.x - COURTSIZEY) + COURTSIZEY;
		this->setPosition(ballPositionX, ballPositionY);

		//BALL FOR RIGHT PADDLE [-45; 45]
		ballAngle = (rand() % 90 - 45) * M_PI / 180;
		ballSpeed = initSpeed;

		scoreRight++;
		if (scoreRight == POINTS)
			startGame = false;
	}
	//CHECK COLLISIONS BETWEEN BALL AND RIGHT-SCREEN
	else if (this->getPosition().x > WIDTH)
	{
		pointSound.play();

		float ballPositionX = (WIDTH - ballSize.x) / 2.0f;
		float ballPositionY = rand() % (int)(WIDTH - ballSize.x - COURTSIZEY) + COURTSIZEY;
		this->setPosition(ballPositionX, ballPositionY);
		
		//BALL FOR LEFT PADDLE [135; 225]
		ballAngle = (rand() % 90 + 135) * M_PI / 180;
		ballSpeed = initSpeed;

		scoreLeft++;
		if (scoreLeft == POINTS)
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
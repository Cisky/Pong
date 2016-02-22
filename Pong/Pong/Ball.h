#pragma once

#include "Paddle.h"
#include "Utils.h"

class Ball : public RectangleShape
{
	private:
		//MEMBER
		Vector2f ballSize;
		Vector2f ballMoveVector;
		float initSpeed;
		float ballSpeed;
		float ballAngle;

	public:
		//CONSTRUCTOR
		Ball();

		//MEMBER FUNCTION
		void leftPaddleCollision(Paddle &leftPaddle);
		void rightPaddleCollision(Paddle &rightPaddle);
		void courtCollision(unsigned short &scoreLeft, unsigned short &scoreRight, bool &startGame);
		
		void update();
};
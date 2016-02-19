#pragma once

#include "Paddle.h"
#include <SFML\Graphics.hpp>

using namespace sf;

class Ball : public RectangleShape
{
	private:
		//MEMBER
		Vector2f ballSize;
		Vector2f ballMoveVector;
		float ballSpeed;
		float ballAngle;

	public:
		//CONSTRUCTOR
		Ball(unsigned int screenWidth, unsigned int screenHeight);

		//MEMBER FUNCTION
		//CHECK COLLISIONS
		void leftPaddleCollision(Paddle &leftPaddle);
		void rightPaddleCollision(Paddle &rightPaddle);
		void courtCollision(unsigned short &scoreLeft, unsigned short &scoreRight, Vector2f &courtSize, Vector2f &screenSize, bool &startGame);
		
		//MOVE BALL
		void update();
};
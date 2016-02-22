#pragma once

#include "Utils.h"

class Paddle : public RectangleShape
{
	private:
		//MEMBER
		Vector2f paddleSize;
		float paddleSpeed;
		bool isKeyPressed;

	public:
		//CONSTRUCTOR
		Paddle();

		//MEMBER FUNCTION
		bool isMoving() const;

		void update(Keyboard::Key up, Keyboard::Key down);
};
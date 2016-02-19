#pragma once

#include <SFML\Graphics.hpp>

using namespace sf;

class Paddle : public RectangleShape
{
	private:
		//MEMBER
		Vector2f paddleSize;
		float paddleSpeed;

	public:
		//CONSTRUCTOR
		Paddle();

		//MEMBER FUNCTION
		//MOVE PADDLE WITH SPECIFIED KEY
		void update(Vector2f &courtSize, Keyboard::Key up, Keyboard::Key down, Vector2f &screenSize);
};
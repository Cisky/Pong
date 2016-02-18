#pragma once

#include <SFML\Graphics.hpp>

using namespace sf;

class Paddle : public RectangleShape
{
	private:
		//MEMBER
		Vector2f paddleSize;

	public:
		//CONSTRUCTOR
		Paddle();

		//MEMBER FUNCTION
		void update(Vector2f &courtSize);
};
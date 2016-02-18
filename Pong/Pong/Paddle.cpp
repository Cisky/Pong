#include "Paddle.h"

//CONSTRUCTOR
Paddle::Paddle()
{
	paddleSize.x = 20.0f;
	paddleSize.y = 100.0f;

	setSize(paddleSize);
	setFillColor(Color::White);
}

//MEMBER FUNCTION
void Paddle::update(Vector2f &courtSize)
{
}

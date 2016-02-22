#pragma once

#include "Ball.h"
#include "Paddle.h"
#include "Utils.h"

class Pong
{
private:
	//MEMBER
	RenderWindow window;

	Vector2f netSize;
	Vector2f courtSize;

	Font gameFont;

	Text scoreMessage;
	Text playerMessage;

	RectangleShape courtBound;
	RectangleShape net;

	Ball ball;
	Paddle leftPaddle;
	Paddle rightPaddle;

	unsigned short scoreLeft;
	unsigned short scoreRight;

	bool startGame;

	//MEMBER FUNCTION
	void draw();

public:
	//CONSTRUCTOR
	Pong();

	//MEMBER FUNCTION
	void playGame();
};
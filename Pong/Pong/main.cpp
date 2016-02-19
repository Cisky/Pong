#define _USE_MATH_DEFINES

#include "Ball.h"
#include "Paddle.h"
#include <iostream>

using namespace std;

int main()
{
	RenderWindow window;
	VideoMode videoMode(1000, 600);
	window.create(videoMode, "Pong", Style::Close);
	window.setVerticalSyncEnabled(true);

	//FONT
	Font gameFont;
	if (!gameFont.loadFromFile("Font/GameFont.ttf"))
		return EXIT_FAILURE;

	//SCORE
	Text scoreMessage;
	scoreMessage.setFont(gameFont);
	scoreMessage.setCharacterSize(80);
	scoreMessage.setColor(Color::White);

	//PLAYER MESSAGE
	Text playerMessage;
	playerMessage.setFont(gameFont);
	playerMessage.setCharacterSize(40);
	playerMessage.setColor(Color::White);

	Ball ball(videoMode.width, videoMode.height);
	Paddle leftPaddle;
	Paddle rightPaddle;

	//COURT BOUND
	Vector2f courtSize(videoMode.width - 10.0f, 7.0f);
	RectangleShape bound;
	bound.setSize(courtSize);
	bound.setFillColor(Color::White);

	//NET
	Vector2f netSize(5.0f, 15.0f);
	RectangleShape net;
	net.setSize(netSize);
	net.setFillColor(Color::White);
	net.setOutlineThickness(5);
	net.setOutlineColor(Color::Black);

	float ballAngle = 0.0f;

	unsigned short scoreLeft = 0;
	unsigned short scoreRight = 0;

	bool startGame = false;

	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			else if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape)
					window.close();
				else if (event.key.code == Keyboard::Space && !startGame)
				{
					startGame = true;
					scoreLeft = 0;
					scoreRight = 0;

					leftPaddle.setPosition(60 - leftPaddle.getSize().x, (videoMode.height - leftPaddle.getSize().y) / 2.0f);
					rightPaddle.setPosition(videoMode.width - 60, (videoMode.height - rightPaddle.getSize().y) / 2.0f);

					scoreLeft = 0;
					scoreRight = 0;

					ballAngle = (rand() % 90 - 45) * M_PI / 180;
				}
			}
		}

		if (startGame)
		{
			Vector2f screenSize(videoMode.width, videoMode.height);
			
			leftPaddle.update(courtSize, Keyboard::W, Keyboard::S, screenSize);
			rightPaddle.update(courtSize, Keyboard::Up, Keyboard::Down, screenSize);
			
			ball.update();
			ball.courtCollision(scoreLeft, scoreRight, courtSize, screenSize, startGame);
			ball.leftPaddleCollision(leftPaddle);
			ball.rightPaddleCollision(rightPaddle);
		}
		window.clear();

		//DRAW
		float pixelCount = 0;
		while (pixelCount <= videoMode.height)
		{
			net.setPosition((videoMode.width - netSize.x) / 2.0f, pixelCount);
			window.draw(net);

			pixelCount += netSize.y;
		}

		bound.setPosition(5.0f, 0.0f);
		window.draw(bound);
		bound.setPosition(5.0f, videoMode.height - courtSize.y);
		window.draw(bound);

		scoreMessage.setPosition((videoMode.width / 2.0f) - 100, 0.0f);
		scoreMessage.setString(to_string(scoreLeft));
		window.draw(scoreMessage);

		scoreMessage.setPosition((videoMode.width / 2.0f) + 60, 0.0f);
		scoreMessage.setString(to_string(scoreRight));
		window.draw(scoreMessage);

		if (startGame)
		{
			window.draw(leftPaddle);
			window.draw(rightPaddle);
			window.draw(ball);
		}
		else
		{
			playerMessage.setColor(Color::White);

			playerMessage.setString("Press [SPACE] to Start the Game");
			playerMessage.setPosition((videoMode.width - playerMessage.getLocalBounds().width) / 2.0f, (videoMode.height / 2.0f) + 20);
			window.draw(playerMessage);

			if (scoreLeft == 10)
			{
				playerMessage.setString("You Win");
				playerMessage.setPosition(videoMode.width / 4.0f - playerMessage.getLocalBounds().width / 2.0f, videoMode.height / 2.0f - playerMessage.getLocalBounds().height);
				playerMessage.setColor(Color::Yellow);
				window.draw(playerMessage);

				playerMessage.setString("You Lose");
				playerMessage.setPosition(3.0f * videoMode.width / 4.0f - playerMessage.getLocalBounds().width / 2.0f, videoMode.height / 2.0f - playerMessage.getLocalBounds().height);
				playerMessage.setColor(Color::Blue);
				window.draw(playerMessage);
			}
			else if (scoreRight == 10)
			{
				playerMessage.setString("You Lose");
				playerMessage.setPosition(videoMode.width / 4.0f - playerMessage.getLocalBounds().width / 2.0f, videoMode.height / 2.0f - playerMessage.getLocalBounds().height);
				playerMessage.setColor(Color::Yellow);
				window.draw(playerMessage);

				playerMessage.setString("You Win");
				playerMessage.setPosition(3.0f * videoMode.width / 4.0f - playerMessage.getLocalBounds().width / 2.0f, videoMode.height / 2.0f - playerMessage.getLocalBounds().height);
				playerMessage.setColor(Color::Blue);
				window.draw(playerMessage);
			}
		}

		window.display();
	}
	return 0;
}
#define _USE_MATH_DEFINES

#include "Pong.h"

//CONSTRUCTOR
Pong::Pong()
{
	window.create(VideoMode(WIDTH, HEIGHT), "Pong", Style::Close);
	window.setVerticalSyncEnabled(true);

	//FONT
	if (!gameFont.loadFromFile(FONT))
		cout << "FONT NOT LOAD!" << endl;

	//SCORE
	scoreMessage.setFont(gameFont);
	scoreMessage.setCharacterSize(SCORESIZE);
	scoreMessage.setColor(SCORECOLOR);

	//PLAYER MESSAGE
	playerMessage.setFont(gameFont);
	playerMessage.setCharacterSize(TEXTSIZE);
	playerMessage.setColor(TEXTCOLOR);

	//COURT BOUND
	courtSize.x = COURTSIZEX;
	courtSize.y = COURTSIZEY;
	courtBound.setSize(courtSize);
	courtBound.setFillColor(COURTCOLOR);

	//NET
	netSize.x = NETSIZEX;
	netSize.y = NETSIZEY;
	net.setSize(netSize);
	net.setFillColor(NETCOLOR);
	net.setOutlineThickness(5);
	net.setOutlineColor(BACKGROUNDCOLOR);

	scoreLeft = 0;
	scoreRight = 0;

	startGame = false;
}

//PRIVATE MEMBER FUNCTION
void Pong::draw()
{
	//DRAW
	float pixelCount = 0;
	while (pixelCount <= HEIGHT)
	{
		net.setPosition((WIDTH - netSize.x) / 2.0f, pixelCount);
		window.draw(net);

		pixelCount += netSize.y;
	}

	courtBound.setPosition(5.0f, 0.0f);
	window.draw(courtBound);
	courtBound.setPosition(5.0f, HEIGHT - courtSize.y);
	window.draw(courtBound);

	scoreMessage.setPosition((WIDTH / 2.0f) - 100, 0.0f);
	scoreMessage.setString(to_string(scoreLeft));
	window.draw(scoreMessage);

	scoreMessage.setPosition((WIDTH / 2.0f) + 60, 0.0f);
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
		playerMessage.setColor(TEXTCOLOR);

		playerMessage.setString("Press [SPACE] to Start the Game");
		playerMessage.setPosition((WIDTH - playerMessage.getLocalBounds().width) / 2.0f, (HEIGHT / 2.0f) + 20);
		window.draw(playerMessage);

		if (scoreLeft == POINTS)
		{
			playerMessage.setString("You Win");
			playerMessage.setPosition(WIDTH / 4.0f - playerMessage.getLocalBounds().width / 2.0f, HEIGHT / 2.0f - playerMessage.getLocalBounds().height);
			playerMessage.setColor(WINCOLOR);
			window.draw(playerMessage);

			playerMessage.setString("You Lose");
			playerMessage.setPosition(3.0f * WIDTH / 4.0f - playerMessage.getLocalBounds().width / 2.0f, HEIGHT / 2.0f - playerMessage.getLocalBounds().height);
			playerMessage.setColor(LOSECOLOR);
			window.draw(playerMessage);
		}
		else if (scoreRight == POINTS)
		{
			playerMessage.setString("You Lose");
			playerMessage.setPosition(WIDTH / 4.0f - playerMessage.getLocalBounds().width / 2.0f, HEIGHT / 2.0f - playerMessage.getLocalBounds().height);
			playerMessage.setColor(WINCOLOR);
			window.draw(playerMessage);

			playerMessage.setString("You Win");
			playerMessage.setPosition(3.0f * WIDTH / 4.0f - playerMessage.getLocalBounds().width / 2.0f, HEIGHT / 2.0f - playerMessage.getLocalBounds().height);
			playerMessage.setColor(LOSECOLOR);
			window.draw(playerMessage);
		}
	}
}

//MEMBER FUNCTION
void Pong::playGame()
{
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

					leftPaddle.setPosition(60 - PADDLESIZEX, (HEIGHT - PADDLESIZEY) / 2.0f);
					rightPaddle.setPosition(WIDTH - 60, (HEIGHT - PADDLESIZEY) / 2.0f);

					scoreLeft = 0;
					scoreRight = 0;
				}
			}
		}

		if (startGame)
		{
			leftPaddle.update(Keyboard::W, Keyboard::S);
			rightPaddle.update(Keyboard::Up, Keyboard::Down);

			ball.update();
			ball.courtCollision(scoreLeft, scoreRight, startGame);
			ball.leftPaddleCollision(leftPaddle);
			ball.rightPaddleCollision(rightPaddle);
		}

		window.clear(BACKGROUNDCOLOR);

		draw();

		window.display();
	}
}
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

		SoundBuffer ballBorderSoundBuffer;		//AUDIO BALL-COURT BOUND BOTTOM
		SoundBuffer ballPaddleSoundBuffer;		//AUDIO BALL-PADDLE
		SoundBuffer PointSoundBuffer;			//AUDIO BALL-COURT BOUND RIGHT

		Sound ballBorderSound;
		Sound ballPaddleSound;
		Sound pointSound;

	public:
		//CONSTRUCTOR
		Ball();

		//MEMBER FUNCTION
		void leftPaddleCollision(Paddle &leftPaddle);
		void rightPaddleCollision(Paddle &rightPaddle);
		void courtCollision(unsigned short &scoreLeft, unsigned short &scoreRight, bool &startGame);
		
		void update();
};
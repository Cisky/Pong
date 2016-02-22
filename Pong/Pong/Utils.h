#pragma once

#include <cmath>
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace sf;
using namespace std;

const unsigned int WIDTH = 1000;
const unsigned int HEIGHT = 600;

const int POINTS = 10;

const string BALLBORDERSOUND = "Audio/Border.ogg";
const string BALLPADDLESOUND = "Audio/Paddle.ogg";
const string POINTSOUND = "Audio/Lose.ogg";
const string FONT = "Font/GameFont.ttf";

static const Color BALLCOLOR = Color::White;

const float BALLSIZEX = 20.0f;
const float BALLSIZEY = 20.0f;
const float BALLSPEED = 10.0f;

static const Color PADDLECOLOR = Color::White;

const float PADDLESIZEX = 20.0f;
const float PADDLESIZEY = 100.0f;
const float PADDLESPEED = 15.0f;

static const Color NETCOLOR = Color::White;

const float NETSIZEX = 5.0f;
const float NETSIZEY = 15.0f;

static const Color COURTCOLOR = Color::White;

const float COURTSIZEX = WIDTH - 10.0f;
const float COURTSIZEY = 7.0f;

static const Color SCORECOLOR = Color::White;

const int SCORESIZE = 80;
const int TEXTSIZE = 40;

static const Color TEXTCOLOR = Color(0, 204, 100);
static const Color WINCOLOR = Color::Yellow;
static const Color LOSECOLOR = Color::Blue;

static const Color BACKGROUNDCOLOR = Color::Black;
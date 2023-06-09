#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<vector>
#include<string>
#include<cstring>
#include<fstream>

#include"RenderWindow.h"
#include"Entity.h"
#include"Hole.h"
#include"Tile.h"
#include"Ball.h"
#include"Sand.h"
#include"Water.h"


using namespace std;

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		cout << "SDL_Init HAS FAILED. ERROR: " << SDL_GetError() << endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		cout << "IMG_init has failed. Error: " << SDL_GetError() << endl;

	if ((TTF_Init())<0)
		cout << "TTF init has failes. Error: " << SDL_GetError() << endl<<TTF_Init();
	
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	return true;
}

bool SDLInit = init();

RenderWindow window("Mini Golf", 480, 720);

SDL_Texture* holeTexture = window.loadTexture("gfx/hole.png");
SDL_Texture* bgTexture = window.loadTexture("gfx/bg.png");
SDL_Texture* ballTexture = window.loadTexture("gfx/ball.png");
SDL_Texture* pointTexture = window.loadTexture("gfx/point.png");
SDL_Texture* powerFg = window.loadTexture("gfx/powermeter_fg.png");
SDL_Texture* powerBg = window.loadTexture("gfx/powermeter_bg.png");
SDL_Texture* powermeter = window.loadTexture("gfx/powermeter_overlay.png");
SDL_Texture* tileTexture96 = window.loadTexture("gfx/tile96.png");
SDL_Texture* tileTexture48 = window.loadTexture("gfx/tile48.png");
SDL_Texture* sandTexture96 = window.loadTexture("gfx/sand.png");
SDL_Texture* waterTexture96 = window.loadTexture("gfx/water.png");
SDL_Texture* logoTexure = window.loadTexture("gfx/logo.png");

SDL_Color black = { 0, 0, 0 };

Mix_Chunk* swingSound = Mix_LoadWAV("sound/swing.mp3");
Mix_Chunk* holeSound = Mix_LoadWAV("sound/hole.mp3");
Mix_Chunk* chargeSound = Mix_LoadWAV("sound/charge.mp3");

TTF_Font* font32 = TTF_OpenFont("font/font.ttf", 32);
TTF_Font* font48 = TTF_OpenFont("font/font.ttf", 48);
TTF_Font* font42 = TTF_OpenFont("font/font.ttf", 42);

Ball ball = Ball(Vector2f(0, 0), ballTexture, pointTexture, powerFg, powerBg);
Hole hole = Hole(Vector2f(0, 0), holeTexture);

vector<Sand> loadSand(int level)
{
	vector<Sand> tmpS = {};
	switch (level)
	{
	case 3:
		tmpS.push_back(Sand(Vector2f(96, 48*5), sandTexture96));
		tmpS.push_back(Sand(Vector2f(96 * 2, 48 * 5), sandTexture96));
		tmpS.push_back(Sand(Vector2f(96 * 3, 48 * 5), sandTexture96));
		tmpS.push_back(Sand(Vector2f(96, 48 * 7), sandTexture96));
		tmpS.push_back(Sand(Vector2f(96 * 2, 48 * 7), sandTexture96));
		tmpS.push_back(Sand(Vector2f(96 * 3, 48 * 7), sandTexture96));
	
		break;
	case 5:
		tmpS.push_back(Sand(Vector2f(96*2, 96 * 2), sandTexture96));
		tmpS.push_back(Sand(Vector2f(96 * 2, 96 * 3), sandTexture96));
		break;
	}

	return tmpS;
}

vector<Water> loadWater(int level)
{
	vector<Water> tmpW = {};
	switch (level)
	{
	case 4:
		tmpW.push_back(Water(Vector2f(96+48, 48 * 5), waterTexture96));
		tmpW.push_back(Water(Vector2f(96 * 2 + 48, 48 * 5), waterTexture96));
		break;
	}
	return tmpW;
}

vector<Tile> loadTiles(int level)
{
	vector<Tile> tmp = {};
	switch (level)
	{
	case 0:
		tmp.push_back(Tile(Vector2f(384, 288), tileTexture96));

		break;
	case 1:
		tmp.push_back(Tile(Vector2f(240-96/2, 360-96/2), tileTexture96));
		break;
	case 2:
		tmp.push_back(Tile(Vector2f(384, 288), tileTexture96));
		tmp.push_back(Tile(Vector2f(0, 288), tileTexture96));
		tmp.push_back(Tile(Vector2f(96, 288), tileTexture96));
		tmp.push_back(Tile(Vector2f(288, 288), tileTexture96));
		break;
	case 4:
		tmp.push_back(Tile(Vector2f(96 , 48 * 5), tileTexture48));
		tmp.push_back(Tile(Vector2f(96 , 48 * 6), tileTexture48));
		tmp.push_back(Tile(Vector2f(96+48 , 48 * 4), tileTexture48));
		tmp.push_back(Tile(Vector2f(96 + 48*2, 48 * 4), tileTexture48));
		tmp.push_back(Tile(Vector2f(96 + 48*3, 48 * 4), tileTexture48));
		tmp.push_back(Tile(Vector2f(96 + 48 *4, 48 * 4), tileTexture48));
		tmp.push_back(Tile(Vector2f(48 * 7, 48 * 5), tileTexture48));
		tmp.push_back(Tile(Vector2f(48 * 7, 48 * 6), tileTexture48));
		break;

	case 5:
		tmp.push_back(Tile(Vector2f(96, 96 * 2), tileTexture96));
		tmp.push_back(Tile(Vector2f(96, 96 * 3), tileTexture96));
		tmp.push_back(Tile(Vector2f(0, 96 * 3), tileTexture96));
		tmp.push_back(Tile(Vector2f(96*3, 96 * 2), tileTexture96));
		tmp.push_back(Tile(Vector2f(96*4, 96 * 3), tileTexture96));
		tmp.push_back(Tile(Vector2f(96*3, 96 * 3), tileTexture96));

		break;
	case 6:
		tmp.push_back(Tile(Vector2f(48,48*4), tileTexture48));
		tmp.push_back(Tile(Vector2f(480-48*2, 48 * 4), tileTexture48));

		tmp.push_back(Tile(Vector2f(0, 48 * 6), tileTexture96));
		tmp.push_back(Tile(Vector2f(48*2, 48 * 8), tileTexture96));
		tmp.push_back(Tile(Vector2f(48*4, 48 * 4), tileTexture96));
		tmp.push_back(Tile(Vector2f(480-48*2,48*6), tileTexture96));
		tmp.push_back(Tile(Vector2f(480-48*4, 48 * 8), tileTexture96));
		break;
	case 7:
		tmp.push_back(Tile(Vector2f(192, 48), tileTexture48));
		tmp.push_back(Tile(Vector2f(192+48, 48), tileTexture48));
		tmp.push_back(Tile(Vector2f(48*6, 48*2), tileTexture48));
		tmp.push_back(Tile(Vector2f(48 * 7, 48 * 3), tileTexture48));
		tmp.push_back(Tile(Vector2f(48 * 8, 48 * 4), tileTexture48));
		tmp.push_back(Tile(Vector2f(48 * 6, 48 * 6), tileTexture48));
		tmp.push_back(Tile(Vector2f(48 * 7, 48 * 7), tileTexture48));
		tmp.push_back(Tile(Vector2f(48 * 6, 48 * 8), tileTexture48));
		tmp.push_back(Tile(Vector2f(48 * 5, 48 * 9), tileTexture48));
		tmp.push_back(Tile(Vector2f(48 * 4, 48 * 10), tileTexture48));
		tmp.push_back(Tile(Vector2f(48 * 9, 48 * 9), tileTexture48));
		tmp.push_back(Tile(Vector2f(48 * 8, 48 * 10), tileTexture48));
		tmp.push_back(Tile(Vector2f(48 * 9, 48 * 5), tileTexture48));

		tmp.push_back(Tile(Vector2f(96, 96), tileTexture96));
		tmp.push_back(Tile(Vector2f(96*2, 96*2), tileTexture96));
		break;
	case 8:

		tmp.push_back(Tile(Vector2f(96, 720 - 96 * 2), tileTexture96));
		tmp.push_back(Tile(Vector2f(48 * 3, 720 - 96 * 3), tileTexture96));
		tmp.push_back(Tile(Vector2f(48, 720 - 96 * 4), tileTexture96));
		tmp.push_back(Tile(Vector2f(480-96*2, 720 - 96 * 2), tileTexture96));
		tmp.push_back(Tile(Vector2f(480 - 96, 48 * 5), tileTexture96));
		tmp.push_back(Tile(Vector2f(96, 96 * 2), tileTexture96));
		tmp.push_back(Tile(Vector2f(480-48*3,720-96*3), tileTexture96));
		tmp.push_back(Tile(Vector2f(96 * 3, 96*2), tileTexture96));
		
		tmp.push_back(Tile(Vector2f(96*2, 48), tileTexture48));
		tmp.push_back(Tile(Vector2f(48*5, 48), tileTexture48));
		tmp.push_back(Tile(Vector2f(48 * 3, 48 * 2), tileTexture48));
		tmp.push_back(Tile(Vector2f(48 * 2, 48 * 3), tileTexture48));
		tmp.push_back(Tile(Vector2f(48 * 6, 48 * 2), tileTexture48));
		tmp.push_back(Tile(Vector2f(48 * 7, 48 * 3), tileTexture48));
		tmp.push_back(Tile(Vector2f(48 * 5, 48 * 4), tileTexture48));
		tmp.push_back(Tile(Vector2f(48 * 4, 48 * 7), tileTexture48));
		tmp.push_back(Tile(Vector2f(48 * 5, 48 * 7), tileTexture48));
		tmp.push_back(Tile(Vector2f(48 * 6, 48 * 8), tileTexture48));
		break;

	}
	return tmp;
}

int Stroke;
int level = 0;

int score;
int bestScore;

vector<Tile> tiles = loadTiles(level);
vector<Sand> sands = loadSand(level);
vector<Water> water = loadWater(level);

int state = 0;// 0 title, 1 game,2 end

Uint64 currentTick = SDL_GetPerformanceCounter();
Uint64 lastTick = 0;
double deltaTime = 0;

SDL_Event event;
bool running = true;
bool mouseDown = false;
bool mousePressed = false;
bool swingPlayed = false;
bool secondSwingPlayed = false;


void loadLevel(int level)
{
	if (level > 8)
	{
		state = 2;
		return;
	}
	ball.setVelocity(0, 0);
	ball.setScale(1, 1);
	ball.setWin(false);

	tiles = loadTiles(level);
	sands = loadSand(level);
	water = loadWater(level);

	switch (level)
	{
	case 0:
		hole.setPos(220, 129);
		ball.setPos(228, 560);
		break;

	case 1:
		hole.setPos(220, 129);
		ball.setPos(228, 560);
		break;
	case 2:
		hole.setPos(220, 129);
		ball.setPos(228, 560);
		break;
	case 3:
		hole.setPos(220, 129);
		ball.setPos(228, 560);
		break;
	case 4:
		hole.setPos(220, 129);
		ball.setPos(228, 560);
		break;
	case 5:
		hole.setPos(220, 129);
		ball.setPos(228, 560);
	break;
	case 6:
		hole.setPos(220, 129);
		ball.setPos(228, 560);
		break;
	case 7:
		hole.setPos(220, 129);
		ball.setPos(228, 560);
		break;
	case 8:
		hole.setPos(220, 129);
		ball.setPos(228, 560);
		break;
	}

}

void update()
{
	lastTick = currentTick;
	currentTick = SDL_GetPerformanceCounter();
	deltaTime = (double)((currentTick - lastTick) * 1000 / (double)SDL_GetPerformanceFrequency());
	mousePressed = false;
	while (SDL_PollEvent( & event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			score = bestScore;
			running = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				mouseDown = true;
				mousePressed = true;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				mouseDown = false;
			}
			break;
		
		}
	}
	if (state == 1)
	{
		ball.update(deltaTime, mouseDown, mousePressed,sands ,tiles,water ,hole, chargeSound, swingSound, holeSound);
		
		Stroke = ball.getStrokes();
		if (ball.getScale().x == 0)
		{
			level++;
			loadLevel(level);
			loadSand(level);
			loadWater(level);
		}
	}
}

void graphics()
{
	window.clear();
	window.render(0, 0, bgTexture);
	
	for (Sand& s : sands)
	{
		window.render(s);
	}
	for (Water& w : water)
	{
		window.render(w);
	}
	for (Entity& e : ball.getPoints())
	{
		window.render(e);
	}
	window.render(hole);
	window.render(ball);
	
	for (Tile& t : tiles)
	{
		window.render(t);
	}
	for (Entity& e : ball.getPowerBar())
	{
		window.render(e);
	}
	
	window.render(ball.getPowerBar().at(0).getPos().x, ball.getPowerBar().at(0).getPos().y, powermeter);

	if (state != 2)
	{
		window.render(200, 10, "Hole :", font32, black);
		window.render(280, 10, to_string(level+1).c_str(), font32, black);

		window.render(180, 630, "Stroke :", font32, black);
		window.render(280, 630, to_string(Stroke).c_str(), font32, black);

		window.render(136, 680, "High Score :", font32, black);
		window.render(280, 680, to_string(bestScore).c_str(), font32, black);
	}
	else
	{
		window.clear();
		window.render(0, 0, bgTexture);
		window.render(40, 50, "YOU COMPLETED THE GAME!", font42, black);
		if (Stroke > bestScore)
		{
			window.render(110, 360, "YOUR STROKE :", font42, black);
			window.render(350, 360, to_string(Stroke).c_str(), font42, black);
			score = Stroke;
		}
		else
		{
			window.render(55, 240, "Congratulation,you beat", font42, black);
			window.render(90, 290, "the highest score", font42, black);
			window.render(110, 380, "YOUR STROKE :", font42, black);
			window.render(350, 380, to_string(Stroke).c_str(), font42, black);
			score = Stroke;
		}
	}

	window.display();

}

void titleScreen()
{
	if (SDL_GetTicks() < 2000)
	{
		if (!swingPlayed)
		{
			Mix_PlayChannel(-1,swingSound,0);
			swingPlayed = true;
		}
		while (SDL_PollEvent(&event))
		{

			switch (event.type)
			{
			case SDL_QUIT:
				score = bestScore;
				running = false;
				break;
			}
		}
		window.clear();
		window.render(0, 0, bgTexture);
		window.render(150, 340, "Let's Play", font48, black);
		window.display();
	}
	else
	{
		if (!swingPlayed)
		{
			Mix_PlayChannel(-1, swingSound, 0);
			secondSwingPlayed = true;
		}
		lastTick = currentTick;
		currentTick = SDL_GetPerformanceCounter();
		deltaTime = (double)((currentTick - lastTick) * 1000 / (double)SDL_GetPerformanceFrequency());
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					Mix_PlayChannel(-1, holeSound, 0);
					state = 1;
				}
				break;
			}
		}
		window.clear();
		window.render(0, 0, bgTexture);
		window.render(50, 250, logoTexure);
		window.render(125, 575, "LEFT CLICK TO START", font32, black);
		window.display();
	}

}

void saveHighScore()
{
	ofstream output("High_Score.txt");
	if (score < bestScore)
	{
		output << score;
	}
	else {
		output << bestScore;
	}
}

int main(int argc, char* agrv[])
{
	loadLevel(level);

	ifstream input("High_Score.txt");
	input >> bestScore;

	while (running)
	{
		if (state == 0)
		{
			titleScreen();
		}
		else
		{
			update();
			graphics();
		}
	}
	saveHighScore();
	window.cleanup();
	TTF_CloseFont(font32);
	TTF_CloseFont(font42);
	TTF_CloseFont(font48);
	SDL_Quit();
	TTF_Quit();
	return 0;
}
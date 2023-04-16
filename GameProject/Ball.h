#pragma once
#include<SDL.h>
#include<SDL_mixer.h>
#include<SDL_image.h>
#include<vector>

#include "Hole.h"
#include "Tile.h"
#include "Sand.h"
#include "Entity.h"
#include "Math.h"
class Ball : public Entity
{
public:
	Ball(Vector2f p_pos, SDL_Texture* p_tex, SDL_Texture* p_pointTex, SDL_Texture* p_powerFG, SDL_Texture* p_powerBG);
	Vector2f& getVelocity()
	{
		return velocity;
	}
	Vector2f& getInitialMousePos()
	{
		return initialMousePos;
	}
	std::vector<Entity> getPowerBar()
	{
		return powerBar;
	}
	std::vector<Entity> getPoints()
	{
		return points;
	}
	int getStrokes()
	{
		return strokes;
	}
	bool isWin()
	{
		return win;
	}
	void setWin(bool p_win);
	void setInitialMousePos(float x, float y);
	void setVelocity(float x, float y);
	void setLaunchedVelocity(float x, float y);
	void update(double deltaTime, bool mouseDown, bool mousePressed, std::vector<Sand> sands,std::vector<Tile> tiles, Hole hole, Mix_Chunk* chargeSfx, Mix_Chunk* swingSfx, Mix_Chunk* holeSfx);
private:
	Vector2f velocity;
	Vector2f initialMousePos;
	Vector2f launchedVelocity;
	float velocity1D;
	float launchedVelocity1D;
	std::vector<Entity> points;
	std::vector<Entity> powerBar;
	int strokes = 0;
	int dirX = 1;
	int dirY = 1;
	bool playedSwingFx = true;
	bool win = false;
};


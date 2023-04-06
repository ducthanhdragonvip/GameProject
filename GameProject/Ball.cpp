#include "Ball.h"
#include "Entity.h"
#include "Math.h"
#include "Tile.h"
#include "Hole.h"
#include<iostream>
#include<SDL_mixer.h>
#include<SDL_ttf.h>

Ball::Ball(Vector2f p_pos, SDL_Texture* p_tex, SDL_Texture* p_pointTex, SDL_Texture* p_powerFG, SDL_Texture* p_powerBG)
:Entity(p_pos, p_tex)
{
	
	points.push_back(Entity(Vector2f(-64, -64), p_pointTex));
	powerBar.push_back(Entity(Vector2f(-64, -64), p_powerBG));
	powerBar.push_back(Entity(Vector2f(-64, -64), p_powerFG));
}

void Ball::setVelocity(float x, float y)
{
	velocity.x = x;
	velocity.y = y;
}

void Ball::setLaunchedVelocity(float x, float y)
{
	launchedVelocity.x = x;
	launchedVelocity.y = y;
}

void Ball::setInitialMousePos(float x, float y)
{
	initialMousePos.x = x;
	initialMousePos.y = y;
}

void Ball::setWin(bool p_win)
{
	win = p_win;
}

void Ball::update(double deltaTime, bool mouseDown, bool mousePressed, std::vector<Tile> tiles, Hole hole, Mix_Chunk* chargeSound, Mix_Chunk* swingSound, Mix_Chunk* holeSound)
{
	if (win)
	{
		setScale(0,0 );
		return;
	}
	
	if (getPos().x  > hole.getPos().x && getPos().x< hole.getPos().x +16 && getPos().y  > hole.getPos().y && getPos().y < hole.getPos().y + 16)
	{
		Mix_PlayChannel(-1, holeSound, 0);
		setWin(true);
	}
	
	if (mousePressed )
	{
		Mix_PlayChannel(-1, chargeSound, 0);
		playedSwingFx = false;
		int mouseX = 0;
		int mouseY = 0;
		SDL_GetMouseState(&mouseX, &mouseY);
		setInitialMousePos(mouseX, mouseY);
	}
	if (mouseDown )
	{
		int mouseX = 0;
		int mouseY = 0;
		SDL_GetMouseState(&mouseX, &mouseY);
		setVelocity((mouseX - getInitialMousePos().x) / -150, (mouseY - getInitialMousePos().y) / -150);
		setLaunchedVelocity((mouseX - getInitialMousePos().x) / -150, (mouseY - getInitialMousePos().y) / -150);
		velocity1D = SDL_sqrt(SDL_pow(abs(getVelocity().x), 2) + SDL_pow(abs(getVelocity().y), 2));
		launchedVelocity1D = velocity1D;

		points.at(0).setPos(getPos().x, getPos().y - 36);
		points.at(0).setAngle(SDL_atan2(velocity.y, velocity.x) * (180 / 3.1415) + 90);

		dirX = velocity.x / abs(velocity.x);
		dirY = velocity.y / abs(velocity.y);

		powerBar.at(0).setPos(getPos().x + 60, getPos().y - 48);
		powerBar.at(1).setPos(getPos().x + 66, getPos().y +6 - 48 * powerBar.at(1).getScale().y);

		if (velocity1D > 1)
		{
			velocity1D = 1;
			launchedVelocity1D = 1;
		}
		powerBar.at(1).setScale(1, velocity1D);
		
	}
	else 
	{
		if (!playedSwingFx)
		{
			Mix_PlayChannel(-1, swingSound, 0);
			playedSwingFx = true;
			strokes++;
		}
		points.at(0).setPos(-64, -64);
		powerBar.at(0).setPos(-64, -64);
		powerBar.at(1).setPos(-64, -64);
		setPos(getPos().x + getVelocity().x * deltaTime, getPos().y + getVelocity().y * deltaTime);
		if (getVelocity().x > 0.001 || getVelocity().x < -0.001 || getVelocity().y > 0.001 || getVelocity().y < -0.001)
		{

			if (velocity1D > 0)
			{
				velocity1D -= 0.001 *deltaTime;
			}
			else
			{
				velocity1D = 0;
			}
			velocity.x = (velocity1D / launchedVelocity1D) * abs(launchedVelocity.x) * dirX;
			velocity.y = (velocity1D / launchedVelocity1D) * abs(launchedVelocity.y) * dirY;
		}

		else
		{
			setVelocity(0, 0);
			int mouseX = 0;
			int mouseY = 0;
			SDL_GetMouseState(&mouseX, &mouseY);
			setInitialMousePos(mouseX, mouseY);
		
		}

		if (getPos().x + getCurrentFrame().w >480)
		{
			setVelocity(-abs(getVelocity().x), getVelocity().y);
			dirX = -1;
		}
		else if (getPos().x < 0 )
		{
			setVelocity(abs(getVelocity().x), getVelocity().y);
			dirX = 1;
		}
		else if (getPos().y + getCurrentFrame().h > 720)
		{
			setVelocity(getVelocity().x, -abs(getVelocity().y));
			dirY = -1;
		}
		else if (getPos().y < 0)
		{
			setVelocity(getVelocity().x, abs(getVelocity().y));
			dirY = 1;
		}
		for (Tile& t : tiles)
		{
			float newX = getPos().x + getVelocity().x * deltaTime;
			float newY = getPos().y;
			if (newX + 16 > t.getPos().x && newX < t.getPos().x + t.getCurrentFrame().w && newY + 16 > t.getPos().y && newY < t.getPos().y + t.getCurrentFrame().h )
			{
				setVelocity(getVelocity().x * -1, getVelocity().y);
				dirX *= -1;
			}

			newX = getPos().x;
			newY = getPos().y + getVelocity().y * deltaTime;
			if (newX + 16 > t.getPos().x && newX < t.getPos().x + t.getCurrentFrame().w && newY + 16 > t.getPos().y && newY < t.getPos().y + t.getCurrentFrame().h )
			{
				setVelocity(getVelocity().x, getVelocity().y * -1);
				dirY *= -1;
			}
		}
	}

}
#include "Entity.h"

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex)
:pos(p_pos), tex(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 48;
	currentFrame.h = 48;
	SDL_QueryTexture(p_tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
}

SDL_Texture* Entity::getTex()
{
	return tex;
}

void Entity::setPos(float x, float y)
{
	pos.x = x;
	pos.y = y;
}

void Entity::setAngle(float p_angle)
{
	angle = p_angle;
}

void Entity::setScale(float w, float h)
{
	scale.x = w;
	scale.y = h;
}

SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}

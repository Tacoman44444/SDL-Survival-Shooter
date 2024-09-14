#pragma once

#include <SDL.h>
struct UpdateContext;

class Entity {
public:

	virtual ~Entity();
	virtual void Update(UpdateContext& context, double timestep) = 0;
	virtual void Render(UpdateContext& context) = 0;
	virtual bool IsDead() = 0;

	virtual SDL_Rect GetCollider() = 0;
	virtual void OnCollide(Entity& entity) = 0;

};
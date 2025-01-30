#pragma once

#include "pch.hpp"

class Config
{
  public:
	Config(std::string configPath);

	struct screen
	{
		unsigned int width, height;
		unsigned int maxFps;
	} screen;

	struct player
	{
		float radius;
		float speed;
		float cooldown;
		float health;
		float maxHealth;
		float healthRegen;
	} player;

	struct enemy
	{
		float startX, startY;
		float radius;
		float speed;
		float cooldown;
		float health;
		float maxHealth;
		float healthRegen;
	} enemy;

	struct hitbox
	{
		float radius;
	} hitbox;
};
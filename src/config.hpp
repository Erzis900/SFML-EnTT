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
	} player;

	struct enemy
	{
		float startX, startY;
		float radius;
	} enemy;

	struct hitbox
	{
		float radius;
	} hitbox;
};
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

	struct hitbox
	{
		float radius;
	} hitbox;

  private:
	nlohmann::json data;
};
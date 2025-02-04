#include "config.hpp"

Config::Config(std::string configPath)
{
	std::ifstream configFile(configPath);
	nlohmann::json data = nlohmann::json::parse(configFile);

	// screen
	screen.width = data["screen"]["width"];
	screen.height = data["screen"]["height"];
	screen.maxFps = data["screen"]["maxFps"];

	// player
	player.startX = data["player"]["startX"];
	player.startY = data["player"]["startY"];
	player.radius = data["player"]["radius"];

	// enemy
	enemy.radius = data["enemy"]["radius"];

	// hitbox
	hitbox.radius = data["hitbox"]["radius"];
}
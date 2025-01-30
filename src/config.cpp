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
	player.radius = data["player"]["radius"];
	player.speed = data["player"]["speed"];
	player.cooldown = data["player"]["cooldown"];
	player.health = data["player"]["health"];
	player.maxHealth = data["player"]["maxHealth"];
	player.healthRegen = data["player"]["healthRegen"];

	// enemy
	enemy.radius = data["enemy"]["radius"];
	enemy.speed = data["enemy"]["speed"];
	enemy.health = data["enemy"]["health"];
	enemy.maxHealth = data["enemy"]["maxHealth"];
	enemy.healthRegen = data["enemy"]["healthRegen"];

	// hitbox
	hitbox.radius = data["hitbox"]["radius"];
}
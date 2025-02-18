#include "config.hpp"

Config::Config(std::string configPath)
{
	std::ifstream configFile(configPath);
	if (!configFile.is_open())
	{
		spdlog::error("Failed to load {}", configPath);
		std::exit(EXIT_FAILURE);
	}
	spdlog::info("Loaded {}", configPath);

	try
	{
		data = nlohmann::json::parse(configFile);
		spdlog::info("Parsed {}", configPath);
	}
	catch (const nlohmann::json::parse_error &e)
	{
		spdlog::error("Failed to parse {}. Error: {}", configPath, e.what());
		std::exit(EXIT_FAILURE);
	}

	// screen
	screen.width = data["screen"]["width"];
	screen.height = data["screen"]["height"];
	screen.maxFps = data["screen"]["maxFps"];

	// hitbox
	hitbox.radius = data["hitbox"]["radius"];
}
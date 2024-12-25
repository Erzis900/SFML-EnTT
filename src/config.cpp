#include "config.hpp"
#include <fstream>

Config::Config(std::string configPath)
{
    std::ifstream configFile(configPath);
    nlohmann::json data = nlohmann::json::parse(configFile);

    screenWidth = data["screen"]["width"];
    screenHeight = data["screen"]["height"];
    maxFps = data["screen"]["maxFps"];

    startX = data["player"]["startX"];
    startY = data["player"]["startY"];
    radius = data["player"]["radius"];
    speed = data["player"]["speed"];
    cooldown = data["player"]["cooldown"];
}
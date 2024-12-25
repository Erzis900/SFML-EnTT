#include "external/json.hpp"
#include <iostream>

class Config {
public:
    Config(std::string configPath);

    unsigned int screenWidth, screenHeight;
    unsigned int maxFps;

    float startX, startY;
    float radius;
    float speed;
    float cooldown;
};
#pragma once
#include "pch.hpp"

namespace utils
{
	sf::Vector2f normalize(const sf::Vector2f &vec);
	float getDistance(const sf::Vector2f &a, const sf::Vector2f &b);
	float lerp(float start, float end, float t);
}  // namespace utils
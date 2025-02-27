#pragma once
#include "pch.hpp"

namespace utils
{
	sf::Vector2f normalize(const sf::Vector2f &vec);
	float lerp(float start, float end, float t);
}  // namespace utils
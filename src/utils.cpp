#include "utils.hpp"

namespace utils
{
	sf::Vector2f normalize(const sf::Vector2f &vec)
	{
		float magnitude = std::sqrt(vec.x * vec.x + vec.y * vec.y);
		if (magnitude > 0)
		{
			return {vec.x / magnitude, vec.y / magnitude};
		}
		return vec;
	}

	float lerp(float start, float end, float t) { return start + t * (end - start); }
}  // namespace utils
#include "animationLoader.hpp"

namespace features::animation
{
	AnimationLoader::AnimationLoader()
	{
		frameSize = 64;
		frameTime = 0.05f;
		noEffects = 8;

		if (!texture.loadFromFile("../../public/effects/effect1.png"))
		{
			std::cerr << "Failed to load effect1.png";
			return;
		}

		noFrames = texture.getSize().x / frameSize;
		totalTime = frameTime * noFrames;
	}

	sf::Sprite AnimationLoader::getSprite(float time, components::Color color)
	{
		int index = (1 - time) * noFrames;

		sf::Sprite sprite(texture);

		if (color == components::Color::Rainbow)
		{
			int yIndex = index > noEffects ? (index - noEffects - 1) % noEffects : index;
			sprite.setTextureRect(sf::IntRect({index * frameSize, yIndex * frameSize}, {frameSize, frameSize}));
		}
		else
		{
			sprite.setTextureRect(sf::IntRect({index * frameSize, color * frameSize}, {frameSize, frameSize}));
		}

		sprite.setOrigin({static_cast<float>(frameSize / 2), static_cast<float>(frameSize / 2)});

		return sprite;
	}
}  // namespace features::animation
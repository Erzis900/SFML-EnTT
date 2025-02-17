#include "animationLoader.hpp"

namespace features::animation
{
	AnimationLoader::AnimationLoader()
	{
		frameSize = 64;
		scalingFactor = 5.f;
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

	sf::Sprite AnimationLoader::getSprite(float time, features::animation::components::Color color)
	{
		int index = time * noFrames;

		sf::Sprite sprite(texture);

		if (color == features::animation::components::Color::Rainbow)
		{
			int yIndex = index > noEffects ? (index - noEffects - 1) % noEffects : index;
			sprite.setTextureRect(sf::IntRect({index * frameSize, yIndex * frameSize}, {frameSize, frameSize}));
		}
		else
		{
			sprite.setTextureRect(sf::IntRect({index * frameSize, color * frameSize}, {frameSize, frameSize}));
		}

		sprite.setOrigin({frameSize / 2, frameSize / 2});

		sprite.setScale({scalingFactor, scalingFactor});
		return sprite;
	}
}  // namespace features::animation
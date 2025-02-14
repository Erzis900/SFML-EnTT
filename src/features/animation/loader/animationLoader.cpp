#include "animationLoader.hpp"

namespace features::animation
{
	AnimationLoader::AnimationLoader()
	{
		frameSize = 64;
		scalingFactor = 5.f;
		frameTime = 0.05f;

		if (!texture.loadFromFile("../../assets/effects/effect1.png"))
		{
			std::cerr << "Failed to load effect1.png";
			return;
		}

		noFrames = texture.getSize().x / frameSize;
		totalTime = frameTime * noFrames;
	}

	sf::Sprite AnimationLoader::getSprite(float time)
	{
		int index = time * noFrames;

		sf::Sprite sprite(texture);
		sprite.setTextureRect(sf::IntRect({index * frameSize, 0}, {frameSize, frameSize}));
		sprite.setScale({scalingFactor, scalingFactor});
		return sprite;
	}
}  // namespace features::animation
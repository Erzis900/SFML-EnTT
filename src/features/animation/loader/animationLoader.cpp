#include "animationLoader.hpp"

namespace features::animation
{
	AnimationLoader::AnimationLoader()
	{
		noFrames = 11;
		frameSize = 64;
		scalingFactor = 5.f;

		texture = sf::Texture("../../assets/effects/effect1.png", false, sf::IntRect({0, 0}, {noFrames * frameSize, frameSize}));
	}

	sf::Sprite AnimationLoader::getFrame(int index)
	{
		sf::Sprite sprite(texture);
		sprite.setTextureRect(sf::IntRect({index * frameSize, 0}, {frameSize, frameSize}));
		sprite.setScale({scalingFactor, scalingFactor});
		return sprite;
	}
}  // namespace features::animation
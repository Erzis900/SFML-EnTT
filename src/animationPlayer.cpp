#include "animationPlayer.hpp"

AnimationPlayer::AnimationPlayer()
	: animationSprite(animationTexture)
{
	frameSize = 64;
	noFrames = 11;
	frameTime = 0.05f;

	if (!animationTexture.loadFromFile("../../assets/effects/effect1.png"))
	{
		std::cerr << "Failed to load effect1.png" << std::endl;
		return;
	}
	animationSprite.setScale({5, 5});
	// animationTexture = sf::Texture("../../assets/effects/effect1.png", false, sf::IntRect({0, 0}, {noFrames * frameSize, frameSize}));
	// animationSprite.setTextureRect(sf::IntRect({0, 0}, {noFrames * frameSize, frameSize}));
}

void AnimationPlayer::updateFrame(float deltaTime)
{
	elapsedTime += deltaTime;

	if (elapsedTime >= frameTime)
	{
		elapsedTime = 0;
		currentFrame = (currentFrame + 1) % noFrames;

		int left = currentFrame * frameSize;
		animationSprite.setTextureRect(sf::IntRect({left, 0}, {frameSize, frameSize}));
	}
}

void AnimationPlayer::draw(sf::RenderWindow &window)
{
	// sf::Sprite animationSprite(animationTexture);
	window.draw(animationSprite);
}
#pragma once

#include "pch.hpp"

namespace features::animation
{
	class AnimationLoader
	{
	  public:
		AnimationLoader();

		sf::Sprite getFrame(int index);
		sf::Sprite getSprite(float time);

		float getTotalTime() { return totalTime; }

	  private:
		sf::Texture texture;
		int noFrames;
		int frameSize;
		float scalingFactor;

		float totalTime;
		float frameTime;
	};
}  // namespace features::animation
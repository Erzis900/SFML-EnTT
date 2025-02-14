#pragma once

#include "../components/color.hpp"
#include "pch.hpp"

namespace features::animation
{
	class AnimationLoader
	{
	  public:
		AnimationLoader();

		sf::Sprite getSprite(float time, features::animation::components::Color color);

		float getTotalTime() { return totalTime; }

	  private:
		sf::Texture texture;
		int noFrames;
		int frameSize;
		float scalingFactor;
		int noEffects;

		float totalTime;
		float frameTime;
	};
}  // namespace features::animation
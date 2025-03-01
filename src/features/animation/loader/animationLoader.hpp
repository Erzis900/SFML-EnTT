#pragma once

#include "../components/color.hpp"
#include "pch.hpp"

namespace features::animation
{
	class AnimationLoader
	{
	  public:
		AnimationLoader();

		sf::Sprite getSprite(float time, components::Color color);

		float getTotalTime() { return totalTime; }
		int getFrameSize() { return frameSize; }

	  private:
		sf::Texture texture;
		int noFrames;
		int frameSize;
		int noEffects;

		float totalTime;
		float frameTime;
	};
}  // namespace features::animation
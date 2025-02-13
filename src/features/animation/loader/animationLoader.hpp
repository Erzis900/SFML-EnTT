#pragma once

#include "pch.hpp"

namespace features::animation
{
	class AnimationLoader
	{
	  public:
		AnimationLoader();

		sf::Sprite getFrame(int index);

	  private:
		sf::Texture texture;
		int noFrames;
		int frameSize;
		float scalingFactor;
	};
}  // namespace features::animation
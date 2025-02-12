#pragma once
#include "pch.hpp"

class AnimationPlayer
{
  public:
	AnimationPlayer();

	void updateFrame(float deltaTime);
	void draw(sf::RenderWindow &window);

  private:
	int frameSize;
	int noFrames;
	sf::Texture animationTexture;
	sf::Sprite animationSprite;

	float elapsedTime;
	float frameTime;
	int currentFrame;
};
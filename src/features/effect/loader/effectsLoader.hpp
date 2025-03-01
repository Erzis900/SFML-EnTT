#pragma once

#include "pch.hpp"

#include "components/modifiers.hpp"
#include "entities/attribute.hpp"

#include "../models/effects.hpp"

namespace features::effect
{

	struct Effect
	{
		std::string name;
		std::vector<common::entities::Modifier> modifiers;
		float duration;
		float stacks;
		bool refresh;
		Effects id;
		int x;
		int y;
		int width;
		int height;
	};

	class EffectsLoader
	{
	  public:
		EffectsLoader();
		Effect getEffect(Effects id) { return effectsData[id]; }
		sf::Sprite getSprite(int id);

	  private:
		nlohmann::json data;
		std::map<Effects, Effect> effectsData;
		sf::Texture texture;
	};
}  // namespace features::effect
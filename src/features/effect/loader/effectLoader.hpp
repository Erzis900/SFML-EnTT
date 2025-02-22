#pragma once

#include "pch.hpp"

#include "components/modifiers.hpp"
#include "entities/attribute.hpp"

namespace features::effect
{
	enum Effects : int
	{
		NoEffect = 0,
		Bleed = 1,
		Fortify = 2
	};

	struct Effect
	{
		std::string name;
		std::vector<common::entities::Modifier> modifiers;
		float duration;
		float stacks;
		bool refresh;
		int id;
		int x;
		int y;
		int width;
		int height;
	};

	class EffectLoader
	{
	  public:
		EffectLoader();
		Effect getEffect(int id) { return effectsData[id]; }
		sf::Sprite getSprite(int id);

	  private:
		nlohmann::json data;
		std::map<int, Effect> effectsData;
		sf::Texture texture;
	};
}  // namespace features::effect